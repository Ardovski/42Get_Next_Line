/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uardaozdes <uardaozdes@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 15:31:37 by uardaozdes        #+#    #+#             */
/*   Updated: 2025/07/18 18:08:17 by uardaozdes       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 200
# endif

# include <stdlib.h>

# define FD_MAX 4096

size_t	gnl_string_length(const char *s);
char	*get_next_line(int fd);
char	*gnl_join(char *s1, char *s2);
char	*gnl_find_character(const char *s, int c);
char	*gnl_dup(const char *s1);
char	*gnl_extract_substring(char const *s, unsigned int start, size_t len);

#endif