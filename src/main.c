/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 21:34:02 by maeferre          #+#    #+#             */
/*   Updated: 2024/03/21 15:39:43 by maeferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

#include <stdio.h>

void	check_files_exists(char **argv);

int main(int argc, char **argv, char **env)
{
	t_pipex	pipex;
	int		pipe_fd[2];
	__pid_t	main_pid;
	__pid_t	pid1;
	__pid_t	pid2;

	// Parsing argc, argv
	if (argc != 5)
		quit_error(&pipex, "Invalid number of arguments\n");

	ft_bzero(&pipex, sizeof(t_pipex));
	check_files_exists(argv);
	
	if (pipe(pipe_fd) == -1)
		quit_error(&pipex, "pipe()\n");
	
	pipex.cmd1 = ft_split(argv[2], ' ');
	pipex.cmd2 = ft_split(argv[3], ' ');
	if (!pipex.cmd1 || !pipex.cmd2)
		quit_error(&pipex, "ft_split()\n");
	
	main_pid = getpid();
	

	
	// Creation du premier processus enfant
	pid1 = fork();
	if (pid1 == -1)
		quit_error(&pipex, "fork()\n");
		
	if (pid1 == 0)
	{
		pid1 = getpid();

		// Creation du deuxieme processus enfant
		pid2 = fork();
		if (pid2 == -1)
			quit_error(&pipex, "fork()\n");
		if (pid2 == 0)
			pid2 = getpid();
	}

	char	*args[] = {"ls", "-l", NULL};

	if (pid1 == getpid())
		execve("/bin/ls", args, (char **)NULL);

	quit_error(&pipex, NULL);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}

void	check_files_exists(char **argv)
{
	// Verifie qu'il existe bien un fichier nomme "infile"
	if (access(argv[1], F_OK) == -1)
	{
		write(2, "pipex: no such file or directory: ", 35);
		write(2, argv[1], ft_strlen(argv[1]));
		write(2, "\n", 1);
		exit(EXIT_FAILURE);
	}
	if (access(argv[4], F_OK) == -1)
		execve("/usr/bin/touch", (char *[]){"touch", argv[4], NULL}, (char **)NULL);
}

