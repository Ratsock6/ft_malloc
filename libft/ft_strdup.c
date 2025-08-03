/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 14:26:24 by aallou-v          #+#    #+#             */
/*   Updated: 2023/10/18 15:12:55 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*tab;
	int		i;

	i = 0;
	while (src[i])
		i++;
	tab = (char *) malloc(sizeof(char) * i + 1);
	if (!tab)
		return (NULL);
	i = -1;
	while (src[++i])
		tab[i] = src[i];
	tab[i] = '\0';
	return (tab);
}
