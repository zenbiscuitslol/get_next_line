#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char	*get_next_line(int fd);

/* usage: ./gnl file...  ("-" = stdin)
 * reads all files round-robin (one line each per turn), writes each file's
 * lines to "<file>.out". One file = mandatory test, several = bonus test. */
int	main(int ac, char **av)
{
	int		n = ac - 1, fd[64], done[64] = {0}, left = n, i;
	FILE	*out[64];
	char	*l, name[512];

	if (get_next_line(-1) || n < 1 || n > 64)
		return (puts("get_next_line(-1) must be NULL"), 1);
	for (i = 0; i < n; i++)
	{
		fd[i] = strcmp(av[i + 1], "-") ? open(av[i + 1], O_RDONLY) : 0;
		snprintf(name, sizeof name, "%s.out", strcmp(av[i + 1], "-") ? av[i + 1] : "stdin");
		out[i] = fopen(name, "w");
	}
	while (left)
		for (i = 0; i < n; i++)
		{
			if (done[i])
				continue ;
			l = get_next_line(fd[i]);
			if (!l)
			{
				done[i] = 1;
				left--;
				continue ;
			}
			fputs(l, out[i]);
			free(l);
		}
	for (i = 0; i < n; i++)
	{
		fclose(out[i]);
		if (fd[i])
			close(fd[i]);
		if (get_next_line(fd[i]) && fd[i])
			return (puts("read after EOF/close must be NULL"), 1);
	}
	return (0);
}
