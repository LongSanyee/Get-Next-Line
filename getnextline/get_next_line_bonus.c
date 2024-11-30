/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rammisse <rammisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 13:42:27 by rammisse          #+#    #+#             */
/*   Updated: 2024/11/29 17:51:58 by rammisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (*s == c)
		return ((char *)s);
	else
		return (NULL);
}

char	*readline_bonus(int fd, char *str)
{
	char	*buffer;
	ssize_t	bytes;

	bytes = 1;
	buffer = (char *)ft_calloc((size_t)BUFFER_SIZE + 1, sizeof(char));
	while (bytes > 0 && !ft_strchr(str, '\n'))
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == -1)
		{
			free(buffer);
			free(str);
			return (NULL);
		}
		buffer[bytes] = '\0';
		str = ft_strjoin(str, buffer);
	}
	free(buffer);
	return (str);
}

char	*extractline_bonus(char *str)
{
	size_t	i;
	size_t	j;
	char	*line;

	i = 0;
	j = 0;
	if (!str || !*str)
		return (NULL);
	while (str[i] != '\n' && str[i])
		i++;
	if (str[i] == '\n')
		i++;
	line = (char *)ft_calloc(i + 1, sizeof(char));
	while (j < i)
	{
		line[j] = str[j];
		j++;
	}
	line[j] = '\0';
	return (line);
}

char	*getremainder_bonus(char *str)
{
	char	*tempbuff;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (str[i] != '\n' && str[i])
		i++;
	if (!str[i])
	{
		free(str);
		return (NULL);
	}
	tempbuff = (char *)ft_calloc(((ft_strlen(str) - i) + 1), sizeof(char));
	i++;
	while (str[i])
		tempbuff[j++] = str[i++];
	tempbuff[j] = '\0';
	free(str);
	return (tempbuff);
}

char	*get_next_line(int fd)
{
	static char	*str[OPEN_MAX];
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 1 || BUFFER_SIZE > SIZE_MAX)
		return (NULL);
	str[fd] = readline_bonus(fd, str[fd]);
	if (!str[fd])
		return (NULL);
	line = extractline_bonus(str[fd]);
	str[fd] = getremainder_bonus(str[fd]);
	return (line);
}
