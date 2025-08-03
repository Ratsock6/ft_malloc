/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 23:46:49 by maxborde          #+#    #+#             */
/*   Updated: 2024/06/02 19:37:29 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_dirty_line(int fd, char *buffer)
{
	char	*dirtyline;
	int		charsread;

	charsread = 1;
	dirtyline = NULL;
	dirtyline = ft_strjoin_gnl(dirtyline, buffer);
	while (!ft_strchr_gnl(dirtyline, '\n') && charsread != 0)
	{
		charsread = read(fd, buffer, BUFFER_SIZE);
		if (charsread == -1)
		{
			buffer[0] = 0;
			free(dirtyline);
			return (NULL);
		}
		buffer[charsread] = 0;
		dirtyline = ft_strjoin_gnl(dirtyline, buffer);
	}
	if (!ft_strlen_gnl(dirtyline) && charsread == 0)
	{
		free(dirtyline);
		return (NULL);
	}
	return (dirtyline);
}

char	*get_clean_line(char *remainder)
{
	char	*str;
	int		i;
	int		y;	

	i = 0;
	y = -1;
	while (remainder[i] && remainder[i] != '\n')
		i++;
	if (remainder[i] == '\n')
		i++;
	str = malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	while (++y < i)
		str[y] = remainder[y];
	str[y] = 0;
	free(remainder);
	return (str);
}

void	clean_up_buffer(char *buffer)
{
	int	k;
	int	i;

	i = 0;
	k = 0;
	while (buffer[i] != '\n' && buffer[i])
		i++;
	if (buffer[i] == '\n')
		i++;
	while (buffer[i])
		buffer[k++] = buffer[i++];
	buffer[k] = 0;
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1] = {0};
	char		*dirtyline;
	char		*cleanline;

	dirtyline = get_dirty_line(fd, buffer);
	if (!dirtyline)
		return (NULL);
	cleanline = get_clean_line(dirtyline);
	if (!cleanline)
	{
		free(dirtyline);
		return (NULL);
	}
	clean_up_buffer(buffer);
	return (cleanline);
}
