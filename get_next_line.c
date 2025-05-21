/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pprejith <pprejith@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 13:31:59 by pprejith          #+#    #+#             */
/*   Updated: 2025/05/21 15:37:17 by pprejith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fcntl.h"
#include "get_next_line.h"

int	read_file(int fd, char *storage, char *buffer, char **line)
{
	ssize_t	bytes;
	char	*temp;

	if (!storage || !buffer || !line || !(*line))
		return (-1);
	bytes = 1;
	while (!check_new_line(storage) && bytes > 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == -1)
		{
			storage[0] = '\0';
			return (-1);
		}
		buffer[bytes] = '\0';
		temp = ft_strjoin(*line, storage);
		if (!temp)
			return (-1);
		free(*line);
		*line = temp;
		add_to_storage(storage, buffer, bytes);
	}
	return (bytes);
}

static char	*get_line(char *s)
{
	int		i;
	char	*line;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	line = malloc(i + 2);
	if (!line)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != '\n')
	{
		line[i] = s[i];
		i++;
	}
	if (s[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

void	trim_buffer(char *s)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i] && s[i] != '\n')
		i++;
	if (s[i] == '\n')
		i++;
	while (s[i])
	{
		s[j] = s[i];
		j++;
		i++;
	}
	s[j] = '\0';
}

int	update_line(char **line, char *new_data)
{
	char	*temp;

	if (!line || !*line || !new_data)
		return (0);
	temp = ft_strjoin(*line, new_data);
	if (!temp)
		return (0);
	free(*line);
	*line = temp;
	return (1);
}

char	*get_next_line(int fd)
{
	static char	storage[BUFFER_SIZE + 1];
	char		buffer[BUFFER_SIZE + 1];
	char		*line;
	char		*new_data;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	line = setup_line();
	if (!line)
		return (free(line), NULL);
	if (read_file(fd, storage, buffer, &line) == -1)
		return (free(line), NULL);
	if (line[0] == '\0' && storage[0] == '\0')
		return (free(line), NULL);
	new_data = get_line(storage);
	if (!new_data)
		return (free(line), NULL);
	if (!update_line(&line, new_data))
		return (free(new_data), free(line), NULL);
	free(new_data);
	trim_buffer(storage);
	return (line);
}

// int main(void)
// {
// 	int counter = 0;
// 	int i=0;
// 	char *next_line;
//     int fd = open("test.txt", O_RDONLY);
//     if (fd < 0)
//         return (1);
// 	while(i++ < 3)
// 	{
// 		next_line = get_next_line(fd);
// 		printf("%s",next_line);
// 		free(next_line);
// 	}
//     close(fd);
//     return (0);
// }