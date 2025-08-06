/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouden <clouden@student.42madrid.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 14:14:59 by clouden           #+#    #+#             */
/*   Updated: 2025/08/06 14:15:02 by clouden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	main(int argc, char *argv[])
{
	int i;

	i = 1;
	if (argc != 5)
	{
		return (0);
	}
	while (i < argc)
	{
		printf("%s ", argv[i]);
		i++;
	}
	printf("\n");
	return (0);
}
