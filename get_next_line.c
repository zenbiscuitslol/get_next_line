/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pprejith <pprejith@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 13:31:59 by pprejith          #+#    #+#             */
/*   Updated: 2025/05/06 11:30:04 by pprejith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_file(int fd)
{
	char	storage[BUFFER_SIZE + 1];
	int		read_bytes;
	char	*file_data;
	char	*temp;

	file_data = NULL;
	while ((read_bytes = read(fd, storage, BUFFER_SIZE)) > 0)
	{
		storage[read_bytes] = '\0';
		temp = ft_strjoin(file_data, storage);
		free(file_data);
		file_data = temp;
	}
	return (file_data);
}
char	*get_next_line(int fd)
{
	static char *buffer;
	char *new_line;
	char *line;
	size_t len;

	buffer = read_file(fd);

	if (fd < 0 || BUFFER_SIZE < 0)
		return (NULL);
	if (!buffer || !*buffer)
		return (NULL);
	new_line = ft_strchr(buffer, '\n');
	if (new_line)
	{
		len = new_line - buffer + 1;
		line = ft_substr
	}
}