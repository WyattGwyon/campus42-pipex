/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouden <clouden@student.42madrid.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 16:26:33 by clouden           #+#    #+#             */
/*   Updated: 2025/08/18 16:26:42 by clouden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	assign_cmd(t_cmd *c, char *filename)
{
	c->argv = ft_split(c->raw_cmd, ' ');
	if (!c->argv)
	{
		print_error(NULL, 's');
		return (EXIT_FAILURE);
	}
	if (c->argv[0] == 0)
	{
		print_error(filename, 'p');
		return (EXIT_FAILURE);
	}
	c->cmd = c->argv[0];
	return (0);
}

int	find_cmd(t_cmd *c, char **envp)
{
	c->path = path_parser(c->cmd, envp);
	if (!c->path)
	{
		print_error(c->cmd, 'c');
		return (127);
	}
	return (0);
}

char	*make_path(const char *dir, const char *cmd)
{
	char	*tmp;
	char	*full;

	if (!dir || !cmd)
		return (NULL);
	tmp = ft_strjoin(dir, "/");
	if (!tmp)
		return (NULL);
	full = ft_strjoin(tmp, cmd);
	free(tmp);
	if (!full)
		return (NULL);
	return (full);
}

char	*path_parser(char *cmd, char **envp)
{
	t_path	p;

	init_path(&p);
	while (envp[p.i] != NULL)
	{
		if (!ft_strncmp(p.path_start, envp[p.i], 5))
		{
			p.raw_path = ft_split(envp[p.i] + 5, ':');
			if (!p.raw_path)
				return (NULL);
			p.j = 0;
			while (p.raw_path[p.j] != NULL)
			{
				p.path = make_path(p.raw_path[p.j], cmd);
				if (access(p.path, X_OK) == 0)
					return (ft_strarr_free(&p.raw_path), p.path);
				free(p.path);
				p.j++;
			}
		}
		p.i++;
	}
	return (ft_strarr_free(&p.raw_path), NULL);
}

int	arg_parser(int argc, char *argv[], t_pipe_args *pa)
{
	pa->i = 0;
	if (argc != 5)
	{
		ft_printf("pipex: usage: %s infile cmd1 cmd2 outfile\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	pa->infile = argv[1];
	pa->outfile = argv[argc - 1];
	pa->cmd_cnt = argc - 3;
	pa->c = ft_calloc(pa->cmd_cnt, sizeof(t_cmd *));
	if (!pa->c)
	{
		ft_printf("pipex: failed to allocate memory\n");
		exit(EXIT_FAILURE);
	}
	while (pa->i < pa->cmd_cnt)
	{
		pa->c[pa->i] = NULL;
		pa->c[pa->i] = ft_calloc(1, sizeof(t_cmd));
		pa->c[pa->i]->raw_cmd = NULL;
		pa->c[pa->i]->raw_cmd = argv[2 + pa->i];
		pa->i++;
	}
	return (0);
}
