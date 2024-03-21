/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 21:34:05 by maeferre          #+#    #+#             */
/*   Updated: 2024/03/21 15:30:01 by maeferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <sys/wait.h>

typedef struct s_pipex
{
	char	**cmd1;
	char	**cmd2;
}	t_pipex;

// Libft functions
size_t	ft_strlen(const char *s);
char	**ft_split(char const *s, char c);
void	*ft_bzero(void *s, size_t n);
char	*ft_strdup(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);

// Leaving program related functions
void	free_map(char **map);
void	quit_error(t_pipex *pipex, char *msg);

#endif