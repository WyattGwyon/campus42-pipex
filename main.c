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

int	main(int argc, char *argv[], char **envp)
{
	t_pipe_args	pa;
	int			exit_code;

	exit_code = 0;
	init_pa(&pa);
	arg_parser(argc, argv, &pa);
	pa.i = 0;
	while (pa.i < pa.cmd_cnt)
	{
		init_cmd(pa.c[pa.i]);
		exit_code = pipex(&pa, envp);
		pa.i++;
	}
	free_pipe_args(&pa);
	return (exit_code);
}
