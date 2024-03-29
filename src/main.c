/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: debian <debian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 21:34:02 by maeferre          #+#    #+#             */
/*   Updated: 2024/03/26 19:33:24 by debian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
 *	REMPLACER TOUTES LES FONCTIONS INTERDITES PAR LES MIENNES	
*/

// Fonctions interdites
#include <stdio.h>
#include <string.h>

void	check_files_exists(char **argv, char **env, t_pipex *pipex);
char	*get_path(char *command, t_pipex *pipex, char **env);

void	cmd1_process(char **argv, t_pipex *pipex, int *fd, char **env)
{
	int	infile;

	infile = open(argv[1], O_RDONLY, 0777);
	if (infile == -1)
		quit_error(pipex, "open()\n");
	dup2(fd[1], STDOUT_FILENO);
	dup2(infile, STDIN_FILENO);
	close(fd[0]);
	execve(pipex->cmd1, pipex->cmd1_args, env);
}

void	cmd2_process(char **argv, t_pipex *pipex, int *fd, char **env)
{
	int	outfile;

	outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (outfile == -1)
		quit_error(pipex, "open()\n");
	dup2(fd[0], STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
	close(fd[1]);
	execve(pipex->cmd2, pipex->cmd2_args, env);
}

int	main(int argc, char **argv, char **env)
{
	t_pipex		pipex;
	int		fd[2];
	__pid_t		pid1;

	ft_bzero(&pipex, sizeof(t_pipex));
	if (argc != 5)
		quit_error(&pipex, "Invalid number of arguments\n");	
	check_files_exists(argv, env, &pipex);
	if (pipe(fd) == -1)
		quit_error(&pipex, "pipe()\n");
	pipex.cmd1_args = ft_split(argv[2], ' ');
	pipex.cmd2_args = ft_split(argv[3], ' ');
	if (!pipex.cmd1_args || !pipex.cmd2_args)
		quit_error(&pipex, "ft_split()\n");
	pipex.cmd1 = get_path(pipex.cmd1_args[0], &pipex, env);
	pipex.cmd2 = get_path(pipex.cmd2_args[0], &pipex, env);

	pid1 = fork();
	if (pid1 == -1)
		quit_error(&pipex, "fork()\n");
	if (pid1 == 0)
		cmd1_process(argv, &pipex, fd, env);
	waitpid(pid1, NULL, 0);
	cmd2_process(argv, &pipex, fd, env);

	quit_error(&pipex, NULL);
}

void	check_files_exists(char **argv, char **env, t_pipex *pipex)
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
		execve(get_path("touch", pipex, env), (char *[]){"touch", argv[4], NULL}, env);
}

char	*get_path(char *command, t_pipex *pipex, char **env)
{
	size_t	i;
	char	*path;
	char	**possible_paths;

	i = 0;
	while (ft_strncmp(env[i], "PATH", 4))
		i++;
	possible_paths = ft_split(env[i] + 5, ':');
	if (!possible_paths)
		quit_error(pipex, "ft_split()\n");
	i = -1;
	while (i++, possible_paths[i])
	{
		path = malloc(sizeof(char) + ft_strlen(possible_paths[i]) + ft_strlen(command) + 2);
		if (!path)
			quit_error(pipex, "malloc()\n");
		ft_strcpy(path, possible_paths[i]);
		ft_strcat(path, "/");
		ft_strcat(path, command);
		if (!access(path, F_OK))
			return (free_map(possible_paths), path);
		free(path);
	}
	free_map(possible_paths);
	return (NULL);
}
