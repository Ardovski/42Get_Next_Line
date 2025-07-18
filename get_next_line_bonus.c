/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uardaozdes <uardaozdes@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 17:28:48 by uardaozdes        #+#    #+#             */
/*   Updated: 2025/07/18 18:23:30 by uardaozdes       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdlib.h>
#include <unistd.h>

static void	*gnl_free_and_return(char *ptr1, char *ptr2, void *return_value)
{
	if (ptr1)
		free(ptr1);
	if (ptr2)
		free(ptr2);
	return (return_value);
}

static char	*gnl_extract_line_with_newline(char *buffer)
{
	size_t	i;
	char	*sub;

	i = 0;
	if (!buffer || buffer[0] == '\0')
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	sub = gnl_extract_substring(buffer, 0, i);
	return (sub);
}

static char	*gnl_save_remaining_text(char *buf)
{
	size_t	i;
	char	*remainder;

	i = 0;
	while (buf[i] && buf[i] != '\n')
		i++;
	if (!buf[i])
	{
		free(buf);
		return (NULL);
	}
	remainder = gnl_dup(buf + i + 1);
	free(buf);
	return (remainder);
}

static char	*gnl_read_and_accumulate(int fd, char *buf)
{
	char	*tmp;
	ssize_t	bytes_read;

	tmp = malloc(BUFFER_SIZE + 1);
	if (!tmp)
		return (gnl_free_and_return(buf, NULL, NULL));
	bytes_read = 1;
	while (bytes_read > 0 && (!buf || !gnl_find_character(buf, '\n')))
	{
		bytes_read = read(fd, tmp, BUFFER_SIZE);
		if (bytes_read < 0)
			return (gnl_free_and_return(tmp, buf, NULL));
		if (bytes_read > 0)
		{
			tmp[bytes_read] = '\0';
			if (!buf)
				buf = gnl_dup(tmp);
			else
				buf = gnl_join(buf, tmp);
			if (!buf)
				return (gnl_free_and_return(tmp, NULL, NULL));
		}
	}
	free(tmp);
	return (buf);
}

char	*get_next_line(int fd)
{
	static char	*buffer[FD_MAX];
	char		*line;

	if (fd < 0 || fd >= FD_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	buffer[fd] = gnl_read_and_accumulate(fd, buffer[fd]);
	if (!buffer[fd])
		return (NULL);
	line = gnl_extract_line_with_newline(buffer[fd]);
	if (!line)
	{
		free(buffer[fd]);
		buffer[fd] = NULL;
		return (NULL);
	}
	buffer[fd] = gnl_save_remaining_text(buffer[fd]);
	return (line);
}
