/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 14:18:50 by maeferre          #+#    #+#             */
/*   Updated: 2024/04/12 17:08:41 by maeferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	check_files_exists(char **argv)
{
	if (access(argv[1], F_OK) == -1)
	{
		write(2, "pipex: no such file or directory: ", 34);
		write(2, argv[1], ft_strlen(argv[1]));
		write(2, "\n", 1);
		return (1);
	}
	return (0);
}

char	*get_command(char *command, t_pipex *pipex, char **env)
{
	char	*path;

	if (ft_strchr(command, '/'))
	{
		path = ft_strdup(command);
		execve("./test.sh", (char *[]){"./test.sh", NULL}, env);
		return (path);
	}
	else
	{
		path = get_path(command, pipex, env);
		return (path);
	}
}

char	*fill_path(char *path, char **possible_paths, char *command, int i)
{
	ft_strcpy(path, possible_paths[i]);
	ft_strcat(path, "/");
	ft_strcat(path, command);
	return (path);
}

char	*get_path(char *command, t_pipex *pipex, char **env)
{
	size_t	i;
	char	*path;
	char	**paths;

	i = 0;
	if (!env || !*env)
		return (NULL);
	while (ft_strncmp(env[i], "PATH", 4))
		i++;
	paths = ft_split(env[i] + 5, ':');
	if (!paths)
		quit_n_free(pipex, "ft_split()\n", EXIT_FAILURE);
	i = -1;
	while (i++, paths[i])
	{
		path = malloc(sizeof(char) + ft_strlen(paths[i])
				+ ft_strlen(command) + 2);
		if (!path)
			return (free_map(paths), quit_n_free(pipex, "malloc()\n", 1), NULL);
		path = fill_path(command, paths, command, i);
		if (!access(path, F_OK))
			return (free_map(paths), path);
		free(path);
	}
	return (free_map(paths), NULL);
}
