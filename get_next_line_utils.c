/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pprejith <pprejith@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 13:31:50 by pprejith          #+#    #+#             */
/*   Updated: 2025/04/29 19:14:23 by pprejith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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