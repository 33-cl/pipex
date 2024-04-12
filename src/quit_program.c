/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit_program.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 15:21:38 by maeferre          #+#    #+#             */
/*   Updated: 2024/04/12 17:09:35 by maeferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_map(char **map)
{
	size_t	i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	quit_n_free(t_pipex *pipex, char *msg, int status)
{
	close(pipex->fd[0]);
	close(pipex->fd[1]);
	if (pipex->cmd1)
		free(pipex->cmd1);
	if (pipex->cmd2)
		free(pipex->cmd2);
	if (pipex->cmd1_args)
		free_map(pipex->cmd1_args);
	if (pipex->cmd2_args)
		free_map(pipex->cmd2_args);
	if (msg)
	{
		write(2, "Error : ", 8);
		write(2, msg, ft_strlen(msg));
	}
	if (WIFEXITED(status))
		exit(WEXITSTATUS(status));
	else
	{
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
			exit(128 + SIGINT);
		else if (WIFSIGNALED(status) && WTERMSIG(status) == SIGQUIT)
			exit(128 + SIGQUIT);
		exit(127);
	}
}
