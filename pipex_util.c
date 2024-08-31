/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjamil <mjamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 17:07:05 by mjamil            #+#    #+#             */
/*   Updated: 2024/08/31 17:31:34 by mjamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first_execute(int infd, int *fd, char *cmd1)
{
	char	*cmd1_args[4];

	cmd1_args[0] = "sh";
	cmd1_args[1] = "-c";
	cmd1_args[2] = cmd1;
	cmd1_args[3] = NULL;
	dup2(infd, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	close(infd);
	execve("/bin/sh", cmd1_args, NULL);
	perror("execve failed");
	exit(EXIT_FAILURE);
}

void	second_execute(int outfd, int *fd, char *cmd2)
{
	char	*cmd2_args[4];

	cmd2_args[0] = "sh";
	cmd2_args[1] = "-c";
	cmd2_args[2] = cmd2;
	cmd2_args[3] = NULL;
	dup2(fd[0], STDIN_FILENO);
	dup2(outfd, STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	close(outfd);
	execve("/bin/sh", cmd2_args, NULL);
	perror("execve failed");
	exit(EXIT_FAILURE);
}
