/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joleksia <joleksia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 11:19:07 by joleksia          #+#    #+#             */
/*   Updated: 2024/12/28 12:55:42 by joleksia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

/* SECTION: Defines */
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

/* SECTION: Inclusions */
# include <unistd.h>
# include <stdlib.h>

/* SECTION: Function declaration - main */
char	*get_next_line(int fd);

/* SECTION: Function declaration - utils */
void	*ft_calloc(size_t nmemb, size_t size);
int		ft_strlen(const char *s);
char	*ft_strncpy(char *dest, const char *src, size_t count);
void	ft_bzero(void *dest, size_t count);
char	*ft_strrchr(const char *s, int c);
char	*ft_strnjoin(char *s1, char *s2, size_t c);
int		ft_fdvalid(int fd, char **s);

#endif
