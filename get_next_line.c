/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pprejith <pprejith@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 13:31:59 by pprejith          #+#    #+#             */
/*   Updated: 2025/05/08 17:51:25 by pprejith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_chunk(int fd, char *storage)
{
	char	buffer[BUFFER_SIZE + 1];
	ssize_t	bytes;
	char	*temp;

	if (!storage)
		storage = ft_strdup("");
	if (!storage)
		return (NULL);
	while (!ft_strchr(storage, '\n'))
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if(bytes <0)
		{
			free(storage);
			return NULL;
		}
		if (bytes == 0)
			break ;
		buffer[bytes] = '\0';
		temp = ft_strjoin(storage, buffer);
		free(storage);
		storage = temp;
	}
	return (storage);
}

static char	*get_line(char *storage)
{
	int		i;
	char	*line;

	i = 0;
	if (!storage || storage[0] == '\0')
		return (NULL);
	while (storage[i] && storage[i] != '\n')
		i++;
	if (storage[i] == '\n')
		i++;
	line = ft_substr(storage, 0, i);
	return (line);
}

static char	*trim_buffer(char *storage)
{
	size_t	i;
	char	*updated_storage;

	i = 0;
	while (storage[i] && storage[i] != '\n')
		i++;
	if (storage[i] == '\n')
		i++;
	if (storage[i] == '\0')
	{
		free(storage);
		return (NULL);
	}
	updated_storage = ft_strdup(storage + i);
	free(storage);
	return (updated_storage);
}

char	*get_next_line(int fd)
{
	static char	*storage;
	char		*line;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	storage = read_chunk(fd, storage);
	if (!storage)
		return (NULL);
	line = get_line(storage);
	if (!line)
		return (free(storage), storage = NULL, NULL);
	storage = trim_buffer(storage);
	if (line[0] == '\0')
	{
		free(line);
		if (storage)
		{
			free(storage);
			storage = NULL;
		}
		return (NULL);
	}
	return (line);
}

// int main(void)
// {
//     int fd = open("test.txt", O_RDONLY);
//     if (fd < 0)
//     {
//         return 1;
//     }

//     char *line;
//     while ((line = get_next_line(fd)) != NULL)
//     {
//         printf("%s", line);
//         free(line); // Make sure your GNL allocates memory
//     }

//     close(fd);
//     return 0;
// }