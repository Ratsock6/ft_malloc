/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 13:50:39 by aallou-v          #+#    #+#             */
/*   Updated: 2025/08/04 14:08:08 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int	main(void)
{
	char	*str;

	printf("===== TEST malloc =====\n");
	str = malloc(20);
	if (!str)
		return (printf("malloc failed\n"), 1);
	strcpy(str, "Hello malloc!");
	printf("Allocated and wrote: %s\n", str);
	printf("===== TEST realloc =====\n");
	str = realloc(str, 40);
	if (!str)
		return (printf("realloc failed\n"), 1);
	strcat(str, " Realloc OK.");
	printf("Reallocated and wrote: %s\n", str);
	printf("===== TEST free =====\n");
	free(str);
	printf("Memory freed\n");
	return (0);
}
