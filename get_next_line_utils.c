/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pprejith <pprejith@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 13:31:50 by pprejith          #+#    #+#             */
/*   Updated: 2025/05/08 18:36:26 by pprejith         ###   ########.fr       */
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

char	*ft_strchr(const char *s, int c)
{
	char	x;
	int		i;

	if (!s)
		return (NULL);
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

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;
	size_t	s_len;

	i = 0;
	s_len = 0;
	if (!s)
		return (NULL);
	while (s[s_len])
		s_len++;
	if (start >= s_len)
		len = 0;
	else if (len > s_len - start)
		len = s_len - start;
	sub = malloc(len + 1);
	if (!sub)
		return (NULL);
	while (i < len)
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}

char	*ft_strdup(const char *s1)
{
	char	*str_out;
	int		i;
	int		j;
	int		s1_len;

	i = 0;
	j = 0;
	s1_len = ft_strlen(s1);
	str_out = (char *)malloc(s1_len * sizeof(char) + 1);
	if (!str_out)
		return (NULL);
	while (s1[j])
		str_out[i++] = s1[j++];
	str_out[i] = '\0';
	return (str_out);
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
