/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouden <clouden@student.42madird.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 12:50:56 by clouden           #+#    #+#             */
/*   Updated: 2025/08/25 12:53:39 by clouden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void init_pa(t_pipe_args *pa)
{
	pa->infile = NULL;
	pa->outfile = NULL;
	pa->cmd_cnt = 0;
}

int	main(int argc, char *argv[], char **envp)
{
	t_pipe_args	pa;
	int exit_code;

	exit_code = 0;
	init_pa(&pa);
	arg_parser(argc, argv, &pa);
	pa.i = 0;
	while (pa.i < pa.cmd_cnt)
	{
		exit_code = pipex(&pa, envp);
		pa.i++;
	}
	//clean_pipe(%p);
	return (exit_code);
}
