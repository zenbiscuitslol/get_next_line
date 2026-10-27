/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pprejith <pprejith@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 13:32:02 by pprejith          #+#    #+#             */
/*   Updated: 2025/05/13 09:58:34 by pprejith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef FD_MAX
#  define FD_MAX 1024
# endif

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 50
# endif

char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *string);
int		check_new_line(char *s);
char	*setup_line(void);
char	*get_next_line(int fd);

#endif