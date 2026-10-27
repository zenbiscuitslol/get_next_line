/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pprejith <pprejith@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 13:31:59 by pprejith          #+#    #+#             */
/*   Updated: 2025/05/21 15:37:17 by pprejith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	read_file(int fd, char *buffer, char **line)
{
	ssize_t	bytes;
	char	*temp;

	if (!buffer || !line || !(*line))
		return (-1);
	bytes = 1;
	while (!check_new_line(buffer) && bytes > 0)
	{
		temp = ft_strjoin(*line, buffer);
		if (!temp)
			return (-1);
		free(*line);
		*line = temp;
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == -1)
		{
			buffer[0] = '\0';
			return (-1);
		}
		buffer[bytes] = '\0';
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

static char	*finish_line(char *line, char *buffer)
{
	char	*new_data;
	char	*temp;

	new_data = get_line(buffer);
	if (!new_data)
		return (free(line), NULL);
	temp = ft_strjoin(line, new_data);
	free(new_data);
	free(line);
	if (temp)
		trim_buffer(buffer);
	return (temp);
}

char	*get_next_line(int fd)
{
	static char	buffer[FD_MAX][BUFFER_SIZE + 1];
	char		*line;

	if (BUFFER_SIZE <= 0 || fd < 0 || fd >= FD_MAX)
		return (NULL);
	line = setup_line();
	if (!line)
		return (NULL);
	if (read_file(fd, buffer[fd], &line) == -1)
		return (free(line), NULL);
	if (line[0] == '\0' && buffer[fd][0] == '\0')
		return (free(line), NULL);
	return (finish_line(line, buffer[fd]));
}
