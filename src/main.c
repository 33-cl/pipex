/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 21:34:02 by maeferre          #+#    #+#             */
/*   Updated: 2024/04/12 17:10:01 by maeferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_n_parse(t_pipex *pipex, int argc, char **argv, char **env);
void	cmd1_process(char **argv, t_pipex *pipex, char **env);
void	cmd2_process(char **argv, t_pipex *pipex, char **env);

int	main(int argc, char **argv, char **env)
{
	t_pipex		pipex;
	pid_t		pid1;
	pid_t		pid2;

	init_n_parse(&pipex, argc, argv, env);
	pid1 = fork();
	if (pid1 == -1)
		quit_n_free(&pipex, NULL, EXIT_FAILURE);
	else if (pid1 == 0)
	{
		if (pipex.error)
			quit_n_free(&pipex, NULL, EXIT_FAILURE);
		cmd1_process(argv, &pipex, env);
	}
	pid2 = fork();
	if (pid2 == -1)
		quit_n_free(&pipex, "fork()\n", EXIT_FAILURE);
	else if (pid2 == 0)
		cmd2_process(argv, &pipex, env);
	close(pipex.fd[0]);
	close(pipex.fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, &pipex.status, 0);
	quit_n_free(&pipex, NULL, pipex.status);
}

void	init_n_parse(t_pipex *pipex, int argc, char **argv, char **env)
{
	ft_bzero(pipex, sizeof(t_pipex));
	if (argc != 5)
		quit_n_free(pipex, "Invalid number of arguments\n", EXIT_FAILURE);
	pipex->error = check_files_exists(argv);
	if (!argv[2][0])
	{
		write(2, "pipex : permission denied:\n", 27);
		if (!argv[3][0])
			exit(EXIT_FAILURE);
	}
	if (pipe(pipex->fd) == -1)
		quit_n_free(pipex, "pipe()\n", EXIT_FAILURE);
	pipex->cmd1_args = ft_split(argv[2], ' ');
	if (!pipex->cmd1_args)
		quit_n_free(pipex, "ft_split()\n", EXIT_FAILURE);
	pipex->cmd2_args = ft_split(argv[3], ' ');
	if (!pipex->cmd2_args)
		quit_n_free(pipex, "ft_split()\n", EXIT_FAILURE);
	pipex->cmd1 = get_command(pipex->cmd1_args[0], pipex, env);
	pipex->cmd2 = get_command(pipex->cmd2_args[0], pipex, env);
}

void	cmd1_process(char **argv, t_pipex *pipex, char **env)
{
	int	infile;

	infile = open(argv[1], O_RDONLY, 0777);
	if (infile == -1)
		quit_n_free(pipex, "open()\n", EXIT_FAILURE);
	dup2(pipex->fd[1], STDOUT_FILENO);
	dup2(infile, STDIN_FILENO);
	close(pipex->fd[0]);
	close(infile);
	if (pipex->cmd1)
		execve(pipex->cmd1, pipex->cmd1_args, env);
	write(2, "pipex: command not found: ", 27);
	write(2, argv[2], ft_strlen(argv[2]));
	write(2, "\n", 1);
	quit_n_free(pipex, NULL, EXIT_FAILURE);
}

void	cmd2_process(char **argv, t_pipex *pipex, char **env)
{
	int	outfile;

	outfile = open(argv[4], O_RDWR | O_CREAT | O_TRUNC, 0000644);
	if (outfile < 0)
		quit_n_free(pipex, "open()\n", EXIT_FAILURE);
	dup2(pipex->fd[0], STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
	close(pipex->fd[1]);
	close(outfile);
	write(1, pipex->cmd2, ft_strlen(pipex->cmd2));
	write(1, "\n", 1);
	write(1, pipex->cmd2_args[0], ft_strlen(pipex->cmd2_args[0]));
	write(1, "\n", 1);
	if (pipex->cmd2)
		execve(pipex->cmd2, pipex->cmd2_args, env);
	write(2, "pipex: command not found: ", 27);
	write(2, argv[3], ft_strlen(argv[3]));
	write(2, "\n", 1);
	quit_n_free(pipex, NULL, EXIT_FAILURE);
}
