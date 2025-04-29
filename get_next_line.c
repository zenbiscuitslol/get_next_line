/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pprejith <pprejith@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 13:31:59 by pprejith          #+#    #+#             */
/*   Updated: 2025/04/29 19:18:09 by pprejith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_file(int fd)
{
	static char storage[BUFFER_SIZE + 1];
	int read_bytes;
	char *file_data;
	char *temp;

	file_data = NULL;
	while ((read_bytes = read(fd, storage, BUFFER_SIZE)) > 0)
	{
		storage[read_bytes] = '\0';
		temp = ft_strjoin(file_data, storage);
		free(file_data);
		file_data = temp;
	}
	return file_data;
}