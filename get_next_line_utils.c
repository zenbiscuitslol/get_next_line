/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pprejith <pprejith@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 13:31:50 by pprejith          #+#    #+#             */
/*   Updated: 2025/05/06 11:47:36 by pprejith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *string)
{
	unsigned int	count;

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

char	*ft_strchr(const char *s, int c)
{
	char	x;
	int		i;

	i = 0;
	x = (char)c;
	while (s[i] != '\0')
	{
		if (s[i] == x)
			return ((char *)(s + i));
		i++;
	}
	if (x == '\0')
		return ((char *)(s + i));
	return (NULL);
}

char	*get_str(const char *src, size_t start, size_t len)
{
	char	*line;
	size_t	i;

	i = 0;
	line = malloc(len + 1);
	if (!line)
		return (NULL);
	while (i++ < len)
		line[i] = src[start + i];
	line[start] = '\0';
	return (line);
}
