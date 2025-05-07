/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pprejith <pprejith@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 13:31:59 by pprejith          #+#    #+#             */
/*   Updated: 2025/05/06 19:38:59 by pprejith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_chunks(int fd, char *data)
{
	char	buffer[BUFFER_SIZE + 1];
	char	*storage;
	ssize_t	read_bytes;
	
	if(!data)
		data=ft_strdup("");
	while (!ft_strchr(data, '\n'))
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes <= 0)
			break ;
		buffer[read_bytes] = '\0';
		storage = ft_strjoin(data, buffer);
		free(data);
		data = storage;
	}
	return (data);
}

static char	*get_line(char *storage)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	j = 0;
	while (storage[i] && storage[i] != '\n')
		i++;
	if (storage[i] == '\n')
		i++;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	while (j < i)
	{
		line[j] = storage[j];
		j++;
	}
	line[i] = '\0';
	return (line);
}

static char	*trim_buffer(char *storage)
{
	size_t	i = 0;
	size_t	j = 0;
	size_t	len;
	char	*updated_storage;

	while (storage[i] && storage[i] != '\n')
		i++;
	if (storage[i] == '\n')
		i++;

	if (!storage[i])
		return (ft_strdup("")); 

	len = ft_strlen(storage + i);
	updated_storage = malloc(len + 1);
	if (!updated_storage)
		return (NULL);
	while (j < len)
	{
		updated_storage[j] = storage[i + j];
		j++;
	}
	updated_storage[len] = '\0';
	return (updated_storage);
}

char	*get_next_line(int fd)
{
	static char	*storage;
	char		*line;
	char		*updated_storage;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	storage = read_chunks(fd, storage);
	if(!storage || storage[0] == '\0')
		return(NULL);
	line = get_line(storage);
	updated_storage = trim_buffer(storage);
	if (updated_storage)
	{
		free(storage);
		storage = updated_storage;
	}
	else
	{
		free(storage);
		storage = NULL;
	}
	return (line);
}
