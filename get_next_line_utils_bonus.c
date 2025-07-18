/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uardaozdes <uardaozdes@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 15:32:38 by uardaozdes        #+#    #+#             */
/*   Updated: 2025/07/18 18:13:25 by uardaozdes       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdlib.h>

size_t	gnl_string_length(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*gnl_find_character(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}

char	*gnl_dup(const char *s1)
{
	size_t	len;
	char	*copy;
	size_t	i;

	if (!s1)
		return (NULL);
	len = 0;
	while (s1[len])
		len++;
	copy = (char *)malloc(len + 1);
	if (!copy)
		return (NULL);
	i = 0;
	while (i < len)
	{
		copy[i] = s1[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

char	*gnl_join(char *s1, char *s2)
{
	size_t	l1;
	size_t	l2;
	char	*j;
	size_t	i;

	l1 = gnl_string_length(s1);
	l2 = gnl_string_length(s2);
	j = (char *)malloc(l1 + l2 + 1);
	if (!j)
		return (free(s1), NULL);
	i = 0;
	while (i < l1)
	{
		j[i] = s1[i];
		i++;
	}
	l2 = 0;
	while (l2 < gnl_string_length(s2))
	{
		j[i] = s2[l2];
		i++;
		l2++;
	}
	j[i] = '\0';
	return (free(s1), j);
}

char	*gnl_extract_substring(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*sub;
	size_t	s_len;

	if (!s)
		return (NULL);
	s_len = gnl_string_length(s);
	if (start >= s_len)
		return (gnl_dup(""));
	if (s_len - start < len)
		len = s_len - start;
	sub = (char *)malloc(len + 1);
	if (!sub)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}
