/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pprejith <pprejith@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 13:32:02 by pprejith          #+#    #+#             */
/*   Updated: 2025/05/13 09:58:34 by pprejith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 50
# endif

char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *string);
int		check_new_line(char *s);
char	*setup_line(void);
void	add_to_storage(char *storage, char *buffer, int len);
char	*get_next_line(int fd);

#endif