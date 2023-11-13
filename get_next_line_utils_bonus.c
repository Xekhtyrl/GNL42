/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 15:12:33 by lvodak            #+#    #+#             */
/*   Updated: 2023/11/12 17:02:10 by lvodak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i] != c && s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup(char *src)
{
	char	*dup;
	int		i;
	int		j;

	i = 0;
	if (!src)
		return (0);
	j = ft_strlen(src, 0);
	dup = malloc(sizeof(char) * (j + 1));
	if (!dup)
		return (0);
	if (j != 0)
	{
		while (src[i])
		{
			dup[i] = src[i];
			i++;
		}
	}
	dup[i] = '\0';
	return (dup);
}

char	*ft_strchr(char *s, int clue)
{
	int		i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0' && s[i] != 3 && s[i] != 26)
	{
		if (s[i] == (unsigned char)clue)
			return (&s[++i]);
		i++;
	}
	return (0);
}

char	*ft_free_cond(char **rest, char **buffer, int end_file)
{
	if (rest)
		free(*rest);
	if (buffer)
	{
		free(*buffer);
		*buffer = NULL;
	}
	if (end_file)
		*rest = NULL;
	return (0);
}
