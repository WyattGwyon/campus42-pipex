/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouden <clouden@student.42madrid.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 16:53:40 by clouden           #+#    #+#             */
/*   Updated: 2025/09/24 16:53:42 by clouden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_path(t_path *p)
{
	p->path_start = "PATH=";
	p->raw_path = NULL;
	p->path_array = NULL;
	p->path = NULL;
	p->is_cmd = 0;
	p->i = 0;
	p->j = 0;
}

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
	pa->pid = -1;
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
