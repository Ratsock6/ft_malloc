/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 23:46:14 by maxborde          #+#    #+#             */
/*   Updated: 2024/06/02 19:33:36 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen_gnl(char *s)
{
	size_t	len;

	len = 0;
	if (!s)
		return (0);
	while (s[len])
		len++;
	return (len);
}

char	*ft_strchr_gnl(char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == c)
			return (s);
		s++;
	}
	return (NULL);
}

char	*ft_strjoin_gnl(char *left_str, char *buff)
{
	char	*string;
	int		i;
	int		k;

	if (!left_str)
	{
		left_str = malloc(sizeof(char) * 1);
		left_str[0] = 0;
	}
	if (!buff)
		return (NULL);
	string = malloc(sizeof(char) * (ft_strlen(left_str) + ft_strlen(buff) + 1));
	if (!string)
		return (NULL);
	i = -1;
	k = -1;
	while (left_str[++i])
		string[i] = left_str[i];
	while (buff[++k])
		string[i + k] = buff[k];
	free(left_str);
	string[i + k] = 0;
	return (string);
}
