/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjamil <mjamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 17:05:33 by mjamil            #+#    #+#             */
/*   Updated: 2024/08/31 17:35:21 by mjamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	check_files(char *infile, char *outfile)
{
	int	infd;
	int	outfd;

	infd = open(infile, O_RDONLY);
	if (infd == -1)
	{
		perror("Error opening input file");
		return (0);
	}
	outfd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfd == -1)
	{
		perror("Error opening output file");
		close(infd);
		return (0);
	}
	close(infd);
	close(outfd);
	return (1);
}

int	init_files(char *infile, char *outfile, int *infd, int *outfd)
{
	*infd = open(infile, O_RDONLY);
	if (*infd == -1)
	{
		perror("Error opening input file");
		return (0);
	}
	*outfd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*outfd == -1)
	{
		perror("Error opening output file");
		close(*infd);
		return (0);
	}
	return (1);
}

int	create_pipe(int *fd)
{
	if (pipe(fd) == -1)
	{
		perror("pipe");
		return (0);
	}
	return (1);
}

void	fork_and_execute(int *fd, int infd, int outfd, char **av)
{
	pid_t	pid1;

	pid1 = fork();
	if (pid1 == -1)
	{
		perror("fork");
		close(fd[0]);
		close(fd[1]);
		close(infd);
		close(outfd);
		exit(EXIT_FAILURE);
	}
	if (pid1 == 0)
	{
		close(fd[0]);
		first_execute(infd, fd, av[2]);
	}
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	second_execute(outfd, fd, av[3]);
	close(fd[0]);
	close(infd);
	close(outfd);
}

int	main(int ac, char **av)
{
	int	infd;
	int	outfd;
	int	fd[2];

	if (ac != 5)
	{
		fprintf(stderr, "Usage: %s infile cmd1 cmd2 outfile\n", av[0]);
		return (EXIT_FAILURE);
	}
	if (!check_files(av[1], av[4]))
		return (EXIT_FAILURE);
	if (!init_files(av[1], av[4], &infd, &outfd))
		return (EXIT_FAILURE);
	if (!create_pipe(fd))
	{
		close(infd);
		close(outfd);
		return (EXIT_FAILURE);
	}
	fork_and_execute(fd, infd, outfd, av);
	return (EXIT_SUCCESS);
}
