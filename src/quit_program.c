/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit_program.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 15:21:38 by maeferre          #+#    #+#             */
/*   Updated: 2024/03/21 15:39:06 by maeferre         ###   ########.fr       */
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

void	quit_error(t_pipex *pipex, char *msg)
{
	// free everything
	if (pipex->cmd1)
		free_map(pipex->cmd1);
	if (pipex->cmd2)
		free_map(pipex->cmd2);
		


	// write error + exit
	if (msg)
	{
		write(2, "Error : ", 8);
		write(2, msg, ft_strlen(msg));
		exit(EXIT_FAILURE);
	}
}
