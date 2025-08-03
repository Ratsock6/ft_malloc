/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_str_tab.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 18:54:34 by aallou-v          #+#    #+#             */
/*   Updated: 2024/05/14 14:25:35 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_str_tab(char **str_tab)
{
	size_t	i;

	if (str_tab)
	{
		i = 0;
		while (str_tab[i])
		{
			free(str_tab[i]);
			i++;
		}
		free(str_tab);
	}
}