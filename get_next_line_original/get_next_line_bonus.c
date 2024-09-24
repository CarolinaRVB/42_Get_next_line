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

#include "get_next_line.h"
#include <fcntl.h>

int main(void)
{
    int fd1 = open("tests/test1.txt", O_RDONLY);
    int fd2 = open("tests/test4.txt", O_RDONLY);
    int fd3 = open("tests/test8.txt", O_RDONLY);

    if (fd1 < 0 || fd2 < 0 || fd3 < 0)
    {
        perror("Error opening files");
        return (1);
    }

    char *line1 = NULL;
    char *line2 = NULL;
    char *line3 = NULL;
	char *line4 = NULL;

    // Read from all file descriptors simultaneously, one line at a time
    while (1)
    {
        line1 = get_next_line(fd1);
        line2 = get_next_line(fd2);
        line3 = get_next_line(fd3);
		line4 = get_next_line(0);

        if (!line1 && !line2 && !line3 && !line4)
            break;

        if (line1)
        {
            printf("FD1: %s", line1);
            free(line1);
        }

        if (line2)
        {
            printf("FD2: %s", line2);
            free(line2);
        }

        if (line3)
        {
            printf("FD3: %s", line3);
            free(line3);
        }

		if (line4)
		{
			printf("FD4: %s", line4);
			free(line4);
		}

        printf("\n");
    }

    close(fd1);
    close(fd2);
    close(fd3);

    return (0);
}
