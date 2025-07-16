/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uardaozdes <uardaozdes@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 13:14:45 by uardaozdes        #+#    #+#             */
/*   Updated: 2025/07/16 14:20:24 by uardaozdes       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 21
# endif

# include <stddef.h>

char	*get_next_line(int fd);
size_t	ft_strlen(const char *s);
int		ft_has_newline(const char *s);
char	*ft_strjoin(char *s1, const char *s2);

#endif
