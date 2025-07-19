/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uardaozdes <uardaozdes@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 17:28:48 by uardaozdes        #+#    #+#             */
/*   Updated: 2025/07/19 15:09:35 by uardaozdes       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdlib.h>
#include <unistd.h>

static void	*gnl_free_and_return(char *ptr1, char *ptr2, void *return_value)
{
	if (ptr1)
	{
		free(ptr1);
		ptr1 = NULL;
	}
	if (ptr2)
	{
		free(ptr2);
		ptr2 = NULL;
	}
	return (return_value);
}

static char	*gnl_get_line(char *buffer)
{
	size_t	i;
	char	*line;

	i = 0;
	if (!buffer || buffer[0] == '\0')
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	line = gnl_substr(buffer, 0, i);
	if (!line)
		return (NULL);
	return (line);
}

static char	*gnl_new_buffer(char *buffer)
{
	size_t	i;
	char	*remainder;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
		return (gnl_free_and_return(buffer, NULL, NULL));
	remainder = gnl_dup(buffer + i + 1);
	if (!remainder)
		return (gnl_free_and_return(buffer, NULL, NULL));
	return (gnl_free_and_return(buffer, NULL, remainder));
}

static char	*gnl_read_buffer(int fd, char *buffer)
{
	char	*tmp;
	ssize_t	bytes_read;

	tmp = malloc(BUFFER_SIZE + 1);
	if (!tmp)
		return (gnl_free_and_return(buffer, NULL, NULL));
	bytes_read = 1;
	while (bytes_read > 0 && (!buffer || !gnl_strchar(buffer, '\n')))
	{
		bytes_read = read(fd, tmp, BUFFER_SIZE);
		if (bytes_read < 0)
			return (gnl_free_and_return(tmp, buffer, NULL));
		tmp[bytes_read] = '\0';
		if (!buffer)
		{
			buffer = gnl_dup(tmp);
			if (!buffer)
				return (gnl_free_and_return(tmp, NULL, NULL));
		}
		else
			buffer = gnl_join(buffer, tmp);
		if (!buffer)
			return (gnl_free_and_return(tmp, NULL, NULL));
	}
	return (gnl_free_and_return(tmp, NULL, buffer));
}

char	*get_next_line(int fd)
{
	static char	*buffer[FD_MAX];
	char		*line;

	if (fd < 0 || fd >= FD_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	buffer[fd] = gnl_read_buffer(fd, buffer[fd]);
	if (!buffer[fd])
		return (NULL);
	line = gnl_get_line(buffer[fd]);
	if (!line)
	{
		free(buffer[fd]);
		buffer[fd] = NULL;
		return (NULL);
	}
	buffer[fd] = gnl_new_buffer(buffer[fd]);
	if (!buffer[fd] && gnl_strchar(line, '\n'))
	{
		free(line);
		return (NULL);
	}
	return (line);
}
