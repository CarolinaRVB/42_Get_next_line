/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tester.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crebelo- <crebelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 11:39:55 by crebelo-          #+#    #+#             */
/*   Updated: 2024/06/09 14:34:32 by crebelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
// ANSI color codes
#define BLACK "\x1B[30m"
#define RED "\x1B[31m"
#define GREEN "\x1B[32m"
#define YELLOW "\x1B[33m"
#define BLUE "\x1B[34m"
#define MAGENTA "\x1B[35m"
#define CYAN "\x1B[36m"
#define WHITE "\x1B[37m"
#define RESET "\x1B[0m"


int	get_line(int fd, int flag)
{
	char	*line = NULL;
	FILE	*fd1 = NULL;
	size_t	len = 0;
	size_t	read;

	if (!flag)
	{
		if (fd == 0)
		{
			while (1) 
			{
				read = getline(&line, &len, stdin);
				if ((int)read == -1) {
					free(line);
					line = NULL;
					break;
				}
				printf("%s", line);
				fflush(stdout); // Flush stdout
				free(line);
				line = NULL;
			}
			return (0);
		}
		else
		{
			fd1 = fdopen(fd, "r");
			if (!fd1)
			{
				perror("getline couldn't open file");
				return (1);
			}
		}
	}
	while(1)
	{
		if (flag)
			line = get_next_line(fd);
		else
		{
			read = getline(&line, &len, fd1);
			if ((int)read == -1)
			{
				free(line);
				line = NULL;
				break ;
			}
		}
		if (!line)
			break ;
		printf("%s", line);
		fflush(stdout); // Flush stdout
		free(line);
		line = NULL;
	}
	if (flag)
		close(fd);
	else
		fclose(fd1);
	printf("\n");
	return (0);
}


int main(void)
{
	int	fd1 = open("test1.txt", O_RDONLY);
	int	fd2 = open("test2.txt", O_RDONLY);
	int	fd3 = open("test3.txt", O_RDONLY);
	int	fd4 = open("test4.txt", O_RDONLY);
	int	fd5 = open("test5.txt", O_RDONLY);
	int	fd6 = open("test6.txt", O_RDONLY);
	int	fd7 = open("invalid.txt", O_RDONLY);
	int	fd8 = open("test8.txt", O_RDONLY);
	
	printf(GREEN "\n########## Get Next Line Tester ##########\n" RESET);
	printf(BLUE "\nTest 1: 4 lines made of 1's\n" RESET);
	printf(MAGENTA "Get Next Line:\n" RESET);
	get_line(fd1, 1);
	close(fd1);
	fd1 = open("test1.txt", O_RDONLY);
	printf(YELLOW "\nGetline:\n" RESET);
	get_line(fd1, 0);
	close(fd1);
	printf("\n");
	
	printf(BLUE "\nTest 2: Empty file\n" RESET);
	printf(MAGENTA "Get Next Line:\n" RESET);
	get_line(fd2, 1);
	close(fd2);
	fd2 = open("test2.txt", O_RDONLY);
	printf(YELLOW "\nGetline:\n" RESET);
	get_line(fd2, 0);
	close(fd2);
	printf("\n");

	printf(BLUE "\nTest 3: several newlines\n" RESET);
	printf(MAGENTA "Get Next Line:\n" RESET);
	get_line(fd3, 1);
	close(fd3);
	fd3 = open("test3.txt", O_RDONLY);
	printf(YELLOW "\nGetline:\n" RESET);
	get_line(fd3, 0);
	close(fd3);
	printf("\n");

	printf(BLUE "\nTest 4: big buffer size\n" RESET);
	# ifndef BUFFER_SIZE
	#  define BUFFER_SIZE 1025

	# endif
	printf(MAGENTA "Get Next Line:\n" RESET);
	get_line(fd4, 1);
	close(fd4);
	fd4 = open("test4.txt", O_RDONLY);
	printf(YELLOW "\nGetline:\n" RESET);
	get_line(fd4, 0);
	close(fd4);
	printf("\n");


	printf(BLUE "\nTest 5: buffer size with the size of the read line\n" RESET);
	# ifndef BUFFER_SIZE
	#  define BUFFER_SIZE 11

	# endif
	printf(MAGENTA "Get Next Line:\n" RESET);
	get_line(fd5, 1);
	close(fd5);
	fd5 = open("test5.txt", O_RDONLY);
	printf(YELLOW "\nGetline:\n" RESET);
	get_line(fd5, 0);
	close(fd5);
	printf("\n");

	printf(BLUE "\nTest 6: +1 buffer size from size of the read line\n" RESET);
	# ifndef BUFFER_SIZE
	#  define BUFFER_SIZE 12  

	# endif
	printf(MAGENTA "Get Next Line:\n" RESET);
	get_line(fd6, 1);
	close(fd6);
	fd6 = open("test6.txt", O_RDONLY);
	printf(YELLOW "\nGetline:\n" RESET);
	get_line(fd6, 0);
	close(fd6);
	printf("\n");

	printf(BLUE "\nTest 7: non existant file\n" RESET);
	printf(MAGENTA "Get Next Line:\n" RESET);
	get_line(fd7, 1);
	close(fd7);
	fd7 = open("test7.txt", O_RDONLY);
	printf(YELLOW "\nGetline:\n" RESET);
	get_line(fd7, 0);
	close(fd7);
	printf("\n");

	printf(BLUE "\nTest 8: non existant file\n" RESET);
	printf(MAGENTA "Get Next Line:\n" RESET);
	get_line(fd8, 1);
	close(fd8);
	fd8 = open("test8.txt", O_RDONLY);
	printf(YELLOW "\nGetline:\n" RESET);
	get_line(fd8, 0);
	close(fd8);
	printf("\n");

	printf(BLUE "\nTest 9: from stdin\n" RESET);
	printf(MAGENTA "Get Next Line:\n" RESET);
	get_line(STDIN_FILENO, 1);
	printf(YELLOW "\nGetline:\n" RESET);
	get_line(STDIN_FILENO, 0);
	printf("\n");

	
	return (0);
}