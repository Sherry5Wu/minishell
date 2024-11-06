/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzheng <yzheng@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 12:20:17 by yzheng            #+#    #+#             */
/*   Updated: 2024/11/05 15:24:30 by yzheng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_free(char **str)
{
	free(*str);
	*str = NULL;
	return (NULL);
}

static char	*getbuffer(int fd,	char *line)
{
	char		*buffer;
	int			bytesread;

	buffer = malloc((BUFFER_SIZE + 1));
	if (!buffer)
		return (ft_free(&line));
	bytesread = 1;
	while (!(fft_strchr(line, '\n')) && bytesread > 0)
	{
		bytesread = read(fd, buffer, BUFFER_SIZE);
		if (bytesread > 0)
		{
			buffer[bytesread] = '\0';
			line = fft_strjoin (line, buffer);
		}
	}
	free(buffer);
	if (bytesread == -1)
		return (ft_free(&line));
	return (line);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*bufferline;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	bufferline = getbuffer(fd, bufferline);
	if (!bufferline)
		return (NULL);
	line = ft_getline(bufferline);
	if (!line)
		return (ft_free(&bufferline));
	bufferline = getnewline(bufferline);
	return (line);
}
