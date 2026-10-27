#!/bin/bash
# usage: tests/run.sh   (from anywhere). Needs cc + valgrind.
ROOT=$(cd "$(dirname "$0")/.." && pwd)
T=$(mktemp -d); trap 'rm -rf "$T"' EXIT
cd "$T" || exit 1
pass=0; fail=0
ok()  { pass=$((pass+1)); }
bad() { fail=$((fail+1)); echo "FAIL: $*"; }

# test files
printf '' > empty
printf 'abc' > nonl
printf '\n' > one_nl
printf '\n\n\n' > nls
printf 'hello\nworld\n' > norm
printf 'a\nb\nlast' > lastnonl
printf '\n\nx\n\n' > mixed
head -c 5000 /dev/zero | tr '\0' 'x' > longline; echo >> longline; echo tail >> longline
seq 1 3000 > many
FILES="empty nonl one_nl nls norm lastnonl mixed longline many"

VG="valgrind --leak-check=full --show-leak-kinds=all --errors-for-leak-kinds=all --error-exitcode=9 -q"

run() { # name binary files...
	local name=$1 bin=$2; shift 2
	$VG ./"$bin" "$@" >/dev/null 2>vg.log
	local rc=$?
	[ $rc -eq 0 ] || { bad "$name rc=$rc $(head -3 vg.log | tr '\n' ' ')"; return; }
	for f in "$@"; do cmp -s "$f" "$f.out" && ok || bad "$name: output differs for $f"; done
}

for B in 1 3 42 9999 10000000; do
	echo "== BUFFER_SIZE=$B"
	cc -Wall -Wextra -Werror -g -D BUFFER_SIZE=$B -I"$ROOT" "$ROOT/tests/main.c" \
		"$ROOT/get_next_line.c" "$ROOT/get_next_line_utils.c" -o gnl || { bad "compile mandatory"; continue; }
	for f in $FILES; do run "mandatory B=$B $f" gnl $f; done
	cat norm | $VG ./gnl - >/dev/null 2>vg.log && cmp -s norm stdin.out && ok || bad "mandatory B=$B stdin"

	# bonus static buffer[FD_MAX][BUFFER_SIZE+1] is ~10GB at 10000000: valgrind can't map it
	[ $B -gt 100000 ] && { echo "(bonus skipped: static array too big for valgrind)"; continue; }
	cc -Wall -Wextra -Werror -g -D BUFFER_SIZE=$B -I"$ROOT" "$ROOT/tests/main.c" \
		"$ROOT/get_next_line_bonus.c" "$ROOT/get_next_line_utils_bonus.c" -o gnlb || { bad "compile bonus"; continue; }
	for f in $FILES; do run "bonus B=$B single $f" gnlb $f; done
	run "bonus B=$B 2 fds" gnlb norm lastnonl
	run "bonus B=$B 3 fds" gnlb many longline nonl
	run "bonus B=$B all fds" gnlb $FILES
done
echo "passed=$pass failed=$fail"
[ $fail -eq 0 ]
