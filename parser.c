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

char	*make_path(const char *dir, const char *cmd)
{
	char	*tmp;
	char	*full;

	if (!dir || !cmd)
		return (NULL);
	tmp = ft_strjoin(dir , "/");
	if (!tmp)
		return (NULL);
	full = ft_strjoin(tmp, cmd);
	free(tmp);
	if (!full)
		return (NULL);
	return(full);
}

char	*path_parser(char *cmd, char **envp)
{
	t_path	p;

	p.path_start = "PATH=";
	p.i = 0;
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
					if (!(p.path = make_path(p.raw_path[p.j], cmd)))
						return(ft_strarr_free(&p.raw_path), NULL);
					if (!access(p.path, X_OK) || !access(cmd, F_OK))
						return (ft_strarr_free(&p.raw_path), p.path);
					free(p.path);
					p.j++;
				}
			}
			p.i++;
		}
	return (NULL);
}

// isolate values -infile name -outfile name -raw cmds -cmd_cnts
int	arg_parser(int argc, char *argv[], t_pipe_args *pa)
{
	pa->i = 0;
	if (argc < 5)
	{
		ft_printf("pipex: usage: %s infile cmd1 cmd2 outfile\n", argv[0]);		
		exit(EXIT_FAILURE);
	}
	pa->infile = argv[1];
	pa->outfile = argv[argc-1];
	pa->cmd_cnt = argc - 3;
	while (pa->i < pa->cmd_cnt)
	{
		pa->c[pa->i] = ft_calloc(1, sizeof(t_cmd));
		pa->c[pa->i]->raw_cmd = argv[2 + pa->i];
		pa->i++;
	}
	return (0);
}

	// if (!access(argv[1], F_OK))
	// 	ft_printf("pipex: no such file or directory: %s\n", argv[1]);
	// else if (!access(argv[1], R_OK))
	// 	ft_printf("pipex: permission denied: %s\n", argv[1]);
	// if (!access(argv[argc-1], W_OK))
	// ft_printf("pipex: permission denied: %s\n", argv[argc-1]);

// char **cmd_parser(char *raw_cmd)
// {
// 	if raw_cmd has  single quotes
// 		count number of ' '
		
// 		if number is not even send error message cannot parse
// 		return

// 		split the raw_cmd 

// }