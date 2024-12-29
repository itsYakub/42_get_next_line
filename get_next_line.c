/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joleksia <joleksia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 11:19:04 by joleksia          #+#    #+#             */
/*   Updated: 2024/12/29 11:46:21 by joleksia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stddef.h>

char	*ft_strrchr(const char *s, int c)
{
	char	*scpy;

	scpy = (char *) s + ft_strlen(s);
	while (scpy >= s)
	{
		if (*scpy == (char) c)
			return (scpy);
		scpy--;
	}
	return (NULL);
}

char	*ft_strnjoin(char *s1, char *s2, size_t c)
{
	char	*str;
	size_t	bytes;

	if (!s1 || !s2)
		return (NULL);
	bytes = ft_strlen(s1) + c;
	str = (char *) ft_calloc(bytes + 1, sizeof(char));
	if (!str)
		return (NULL);
	str = ft_strncpy(str, s1, ft_strlen(s1));
	str += ft_strlen(s1);
	str = ft_strncpy(str, s2, c);
	str -= ft_strlen(s1);
	free(s1);
	return (str);
}

static char	*ft_process_chunk(char *dst, char **fcptr)
{
	char	*fcontent;

	fcontent = *fcptr;
	if (ft_strrchr(dst, '\n'))
		return (dst);
	while (fcontent && *fcontent)
	{
		if (*fcontent == '\n')
		{
			fcontent++;
			dst = ft_strnjoin(dst, *fcptr, fcontent - *fcptr);
			*fcptr = ft_strncpy(*fcptr, fcontent, ft_strlen(fcontent) + 1);
			fcontent = *fcptr;
			return (dst);
		}
		fcontent++;
	}
	dst = ft_strnjoin(dst, *fcptr, ft_strlen(*fcptr));
	ft_bzero(*fcptr, fcontent - *fcptr);
	return (dst);
}

static size_t	ft_process_file(int fd, char **dst, char **fcptr)
{
	size_t		fbytes;
	char		*fbuf;

	fbytes = 0;
	*dst = ft_process_chunk(*dst, fcptr);
	if (ft_strrchr(*dst, '\n'))
		return (fbytes);
	fbuf = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	fbytes = read(fd, fbuf, BUFFER_SIZE);
	*fcptr = ft_strncpy(*fcptr, fbuf, ft_strlen(fbuf) + 1);
	free(fbuf);
	*dst = ft_process_chunk(*dst, fcptr);
	return (fbytes);
}

char	*get_next_line(int fd)
{
	static char	*fcptr = NULL;
	static int	fnull = 0;
	size_t		fbytes;
	char		*dst;

	if (!fnull && BUFFER_SIZE > 0)
	{
		if (!ft_fdvalid(fd, &fcptr))
			return (NULL);
		dst = ft_calloc(1, 1);
		while (1)
		{
			fbytes = ft_process_file(fd, &dst, &fcptr);
			if (fbytes < BUFFER_SIZE || ft_strrchr(dst, '\n'))
			{
				if (ft_strlen(dst))
					return (dst);
				free(dst);
				free(fcptr);
				fnull = 1;
				return (NULL);
			}
		}
	}
	return (NULL);
}
