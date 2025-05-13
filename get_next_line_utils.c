/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pprejith <pprejith@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 13:31:50 by pprejith          #+#    #+#             */
/*   Updated: 2025/05/13 09:59:07 by pprejith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *string)
{
	size_t	count;

	count = 0;
	while (string[count] != 0)
		count++;
	return (count);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str_out;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	j = 0;
	str_out = (char *)malloc((ft_strlen(s1) + ft_strlen(s2)) * sizeof(char)
			+ 1);
	if (str_out == NULL)
		return (NULL);
	while (s1[i])
	{
		str_out[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str_out[i + j] = s2[j];
		j++;
	}
	str_out[i + j] = '\0';
	return (str_out);
}

int	check_new_line(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*setup_line(void)
{
	char	*line;

	line = malloc(1);
	if (line)
		line[0] = '\0';
	return (line);
}

void	add_to_storage(char *storage, char *buffer, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		storage[i] = buffer[i];
		i++;
	}
	storage[i] = '\0';
}
