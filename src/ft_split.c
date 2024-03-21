/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 15:08:13 by maeferre          #+#    #+#             */
/*   Updated: 2024/03/21 15:32:42 by maeferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strdup(const char *s)
{
	char	*new_string;
	size_t	s_len;
	size_t	i;

	i = 0;
	s_len = ft_strlen(s);
	new_string = (char *)malloc(sizeof(char) * (s_len + 1));
	if (!new_string)
		return (NULL);
	while (i < s_len)
	{
		new_string[i] = s[i];
		i++;
	}
	new_string[i] = '\0';
	return (new_string);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*new_string;
	size_t		i;
	size_t		len_s;

	i = 0;
	len_s = ft_strlen(s);
	if (!s)
		return (NULL);
	if ((size_t)start > len_s)
		return (ft_strdup(""));
	if (len > len_s)
		len = len_s;
	if (len > len_s - start)
		len = len_s - start;
	new_string = malloc(sizeof(char) * (len + 1));
	if (!new_string)
		return (0);
	while (i < len)
	{
		new_string[i] = s[start + i];
		i++;
	}
	new_string[i] = '\0';
	return (new_string);
}

static int	ft_len_word(char const *s, char c)
{
	size_t		length;

	length = 0;
	while (*s && *s != c)
	{
		length++;
		s++;
	}
	return (length);
}

static size_t	ft_count_word(char const *s, char c)
{
	size_t	i;
	size_t	nb_strings;

	i = 0;
	nb_strings = 0;
	while (s[i] == c && s[i])
		i++;
	while (s[i])
	{
		nb_strings++;
		while (s[i] != c && s[i])
			i++;
		while (s[i] == c && s[i])
			i++;
	}
	return (nb_strings);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	size_t	nb_strings;
	size_t	i;

	if (!s)
		return (NULL);
	nb_strings = ft_count_word(s, c);
	tab = (char **)malloc(sizeof(char *) * (nb_strings + 1));
	if (!tab)
		return (NULL);
	tab[nb_strings] = NULL;
	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			tab[i] = ft_substr(s, 0, ft_len_word(s, c));
			if (!tab[i++])
				return (free_map(tab), NULL);
			s += ft_len_word(s, c);
		}
		else
			s++;
	}
	return (tab);
}