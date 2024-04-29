/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crebelo- <crebelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 11:55:28 by crebelo-          #+#    #+#             */
/*   Updated: 2023/05/12 11:55:28 by crebelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5

# endif

# include <stddef.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

char	*get_next_line(int fd);
void	ft_read(char **stash, int fd);
void	ft_createline(char **line, char *stash);
void	ft_clean(char **stash);

int		ft_findnl(char *stash);
char	*ft_strjoin(char *s1, char *s2);
void	*ft_calloc(size_t nmemb, size_t size);
size_t	ft_strlen(const char *s);
void	createstash(char **stash, char *buff);
void	ft_bzero(void *s, size_t n);

size_t	ft_strlen_nl(const char *s);

#endif
