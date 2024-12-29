/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joleksia <joleksia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 11:18:58 by joleksia          #+#    #+#             */
/*   Updated: 2024/12/28 12:59:57 by joleksia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_bzero(void *dest, size_t count)
{
	unsigned char	*dcpy;

	dcpy = (unsigned char *) dest;
	while (count--)
		*dcpy++ = 0;
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*arr;

	if (!size || !nmemb)
		return (malloc(0));
	if (size && ((nmemb * size) / size) != nmemb)
		return (NULL);
	arr = malloc(nmemb * size);
	if (!arr)
		return (NULL);
	ft_bzero(arr, nmemb * size);
	return (arr);
}

int	ft_strlen(const char *s)
{
	int	len;

	len = 0;
	if (!s || !*s)
		return (len);
	while (*s++)
		len++;
	return (len);
}

char	*ft_strncpy(char *dest, const char *src, size_t count)
{
	char	*d;

	d = dest;
	while (*src && (ssize_t) count-- > 0)
		*dest++ = *src++;
	while ((ssize_t) count-- > 0)
		*dest++ = '\0';
	return (d);
}

int	ft_fdvalid(int fd, char **s)
{
	int		fbytes;
	char	*fbuf;

	if (*s)
		return (1);
	fbuf = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	fbytes = read(fd, fbuf, BUFFER_SIZE);
	if (fbytes < 0)
	{
		free(fbuf);
		return (0);
	}
	*s = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	*s = ft_strncpy(*s, fbuf, BUFFER_SIZE);
	free(fbuf);
	return (1);
}
