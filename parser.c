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

// frees the first string 
// because the first arg of ft_stjoin_n is always a malloced process
// this is helper function only for ft_strjoin_n
char	*ft_strjoin_free(char *s1, const char *s2)
{
	char *joined;

	joined = ft_strjoin(s1, s2);
	free(s1);
	return (joined);
}

char	*ft_strjoin_n(char **str_segs)
{
	int		i;
	char	*joined_str;

	if (!str_segs || !*str_segs)
		return (ft_calloc(1, 1));
	joined_str = ft_strdup(str_segs[0]);
	i = 1;
	while (str_segs[i])
	{
		joined_str = ft_strjoin_free(joined_str, str_segs[i]);
		i++;
	}
	return (joined_str);
}

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
					if (!access(p.path, X_OK))
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
// for each cmd split for argv avoid ' '(squote)
// then path for cmd
int	arg_parser(int argc, char *argv[], char **envp, t_pipex *p)
{
	p->i = 0;
	if (argc < 5)
	{
		ft_printf("pipex: usage: %s infile cmd1 cmd2 outfile\n", argv[0]);		
		exit(EXIT_FAILURE);
	}
	if (!access(argv[1], F_OK))
	{
		ft_printf("%s: no such file or directory: %s\n", argv[0], argv[1]);
		p->infile = NULL;
	}
	else if (!access(argv[1], R_OK))
	{
		ft_printf("%s: permission denied: %s\n", argv[0], argv[1]);
		p->infile = NULL;
	}
	else 
		p->infile = ft_strdup(argv[1]);
	if (!access(argv[argc-1], W_OK))
	{
		ft_printf("%s: permission denied: %s\n", argv[0], argv[argc-1]);
		p->outfile = NULL;
	}
	else 
		p->outfile = argv[argc-1];
	p->cmd_cnt = argc - 3;
	while (p->i < p->cmd_cnt)
	{
		p->commands[p->i] = ft_calloc(1, sizeof(t_cmd));
		p->commands[p->i]->raw_cmd = argv[2 + p->i];
		p->i++;
	}
	return (0);
}
