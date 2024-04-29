/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crebelo- <crebelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 11:50:55 by crebelo-          #+#    #+#             */
/*   Updated: 2023/05/12 11:50:55 by crebelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static char		*stash[1024];
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	ft_read(&stash[fd], fd);
	if (!stash[fd])
		return (NULL);
	ft_createline(&line, stash[fd]);
	ft_clean(&stash[fd]);
	if (line[0] == '\0')
	{
		free(stash[fd]);
		stash[fd] = NULL;
		free(line);
		line = NULL;
	}
	return (line);
}

void	ft_read(char **stash, int fd)
{
	char	*buff;
	ssize_t	n;

	buff = (char *)ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (!buff)
		return ;
	n = 1;
	while (n != 0 && !ft_findnl(*stash))
	{
		n = read(fd, buff, BUFFER_SIZE);
		if (n == -1)
		{
			free(buff);
			free(*stash);
			*stash = NULL;
			return ;
		}
		buff[n] = '\0';
		createstash(stash, buff);
	}
	free(buff);
}

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

void	ft_createline(char **line, char *stash)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (stash[i])
	{
		if (stash[i] == '\n')
		{
			i++;
			break ;
		}
		i++;
	}
	*line = ft_calloc((i + 1), sizeof(char));
	if (!*line)
		return ;
	while (j < i)
	{
		(*line)[j] = stash[j];
		j++;
	}
}

void	ft_clean(char **stash)
{
	size_t		i;
	size_t		j;
	char		*newstash;

	i = 0;
	j = 0;
	while ((*stash)[i])
	{
		if ((*stash)[i] == '\n')
		{
			i++;
			break ;
		}
		i++;
	}
	newstash = ft_calloc(((ft_strlen(*stash) - i) + 1), sizeof(char));
	if (*stash == NULL || newstash == NULL)
		return ;
	while ((*stash)[i])
		newstash[j++] = (*stash)[i++];
	free(*stash);
	*stash = newstash;
}

// #include <fcntl.h>
// #include <unistd.h>
// #include <stdlib.h>
// #include <stdio.h>
// int main(void) {
// 	int fd = open("example.txt", O_RDONLY);
// 	if (fd == -1) {
// 		perror("Failed to open file");
// 		return 1;
// 	}

// 	char *line;
// 	while ((line = get_next_line(fd)) != NULL) {
// 		printf("%s\n", line);
// 		free(line);
// 	}

// 	close(fd);
// 	return 0;
// }