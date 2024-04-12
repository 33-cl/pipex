/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 03:30:16 by maeferre          #+#    #+#             */
/*   Updated: 2024/04/12 16:46:37 by maeferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strchr(const char *s, int c)
{
	size_t			i;
	unsigned char	*uc_s;

	if (!s)
		return (NULL);
	i = 0;
	uc_s = (unsigned char *)s;
	while (uc_s[i] != (unsigned char)c)
	{
		if (uc_s[i] == '\0')
			return (NULL);
		i++;
	}
	return (&((char *)uc_s)[i]);
}
