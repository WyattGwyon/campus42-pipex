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

void	init_pa(t_pipe_args *pa)
{
    pa->infile = NULL;
    pa->outfile = NULL;
    pa->infile_fd = -1;
    pa->outfile_fd = -1;
    pa->cmd_cnt = 0;
    pa->i = 0;
    pa->pipefd[0] = -1;
    pa->pipefd[1] = -1;
    pa->c = NULL;
}

void	init_cmd(t_cmd *c)
{
	c->argv = NULL;
	c->path = NULL;
	c->cmd = NULL;
	c->fd[0] = -1;
	c->fd[1] = -1;		
	c->prev_fd = -1;
	c->pid = -1;
}

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
