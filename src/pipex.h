/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 21:34:05 by maeferre          #+#    #+#             */
/*   Updated: 2024/04/12 17:00:59 by maeferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <fcntl.h>
# include <stdbool.h>
# include <sys/wait.h>

typedef struct s_pipex
{
	int		error;
	int		fd[2];
	char	**cmd1_args;
	char	**cmd2_args;
	char	*cmd1;
	char	*cmd2;
	int		status;
}	t_pipex;

// Main functions
int		check_files_exists(char **argv);
char	*get_command(char *command, t_pipex *pipex, char **env);
char	*get_path(char *command, t_pipex *pipex, char **env);

// Libft functions
char	*ft_strchr(const char *s, int c);
char	*ft_strcat(char *dest, char *src);
char	*ft_strcpy(char *dest, char *src);
int		ft_strncmp(char *s1, char *s2, unsigned int n);
size_t	ft_strlen(const char *s);
char	**ft_split(char const *s, char c);
void	*ft_bzero(void *s, size_t n);
char	*ft_strdup(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);

// Leaving program related functions
void	free_map(char **map);
void	quit_n_free(t_pipex *pipex, char *msg, int status);

#endif
