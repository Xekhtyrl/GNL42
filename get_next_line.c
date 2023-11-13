/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 17:12:27 by lvodak            #+#    #+#             */
/*   Updated: 2023/11/13 17:10:26 by lvodak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_substr(char **s, unsigned int start, size_t len, int c)
{
	char			*dst;
	unsigned long	i;
	unsigned long	l;

	if (!*s)
		return (0);
	l = (int)ft_strlen((char *)*s, 0) - start;
	if (l > len)
		l = len;
	dst = malloc((l + 1) * sizeof(char));
	if (!dst)
	{
		ft_free_cond(s, NULL, 1);
		return (0);
	}
	i = 0;
	while ((*s)[i] && i < l)
	{
		dst[i] = (*s)[start + i];
		i++;
	}
	dst[i] = '\0';
	if (c == 1)
		free(*s);
	return (dst);
}

static char	*ft_strjoin(char *s1, char *s2)
{
	char	*s3;
	int		j;

	if (!s1)
		s1 = ft_strdup("");
	if (!s2 || !s1)
		return (0);
	s3 = malloc(sizeof(char) * (ft_strlen(s1, 0) + ft_strlen(s2, 0) + 1));
	if (!s3)
	{
		free(s1);
		return (0);
	}
	j = 0;
	while (*s1 != '\0' && ft_strlen(s1, 0) != 0)
		s3[j++] = *s1++;
	free(s1 - j);
	while (*s2)
		s3[j++] = *s2++;
	s3[j] = '\0';
	return (s3);
}

static char	*check_str(char **rest, int c)
{
	char	*str;
	int		i;

	if (c)
	{
		if (ft_strlen(*rest, '\0') == 0)
			return (0);
		str = ft_strdup(*rest);
		return (str);
	}
	if (*rest[0] == '\0')
		return (NULL);
	i = ft_strlen(*rest, '\n');
	str = ft_substr(rest, 0, i + 1, 0);
	if (!str)
		return (0);
	*rest = ft_substr(rest, i + 1, ft_strlen(*rest, '\0') - (i + 1), 1);
	return (str);
}

static char	*ft_main_fct(int n, char **buffer, char **rest)
{
	char	*final;

	if (n <= 0)
	{
		if (*rest && n == 0)
		{
			final = check_str(&(*rest), 1);
			ft_free_cond(&(*rest), buffer, 1);
			return (final);
		}
		ft_free_cond(&(*rest), buffer, 1);
		return (NULL);
	}
	(*buffer)[n] = '\0';
	*rest = ft_strjoin(*rest, *buffer);
	if (ft_strchr(*rest, '\n'))
	{
		ft_free_cond(NULL, buffer, 0);
		return (check_str(&(*rest), 0));
	}
	else
		return (0);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*rest;
	char		*final;
	int			n;

	if (BUFFER_SIZE <= 0 || BUFFER_SIZE >= INT32_MAX || fd < 0)
		return (0);
	n = 1;
	if ((rest && (ft_strchr(rest, '\n'))))
		return (check_str(&rest, 0));
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (ft_free_cond(&rest, NULL, 1));
	while (n > 0)
	{
		n = read(fd, buffer, BUFFER_SIZE);
		final = ft_main_fct(n, &buffer, &rest);
		if (final == NULL && n < 0)
			return (NULL);
		if (ft_strchr(final, '\n') || (!ft_strchr(final, '\n') && n == 0))
			return (final);
	}
	ft_free_cond(&rest, &buffer, 1);
	return (NULL);
}
