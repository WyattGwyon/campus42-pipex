/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_clean.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouden <clouden@student.42madrid.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 22:40:29 by clouden           #+#    #+#             */
/*   Updated: 2025/09/09 22:42:16 by clouden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_error(char *str, char type)
{
	char	*message;

	message = "NONE";
	if (type == 'p')
		message = ft_strjoin("pipex: permission denied: ", str);
	else if (type == 'c')
		message = ft_strjoin("pipex: command not found: ", str);
	else if (type == 'f')
		message = ft_strjoin("pipex: no such file or directory: ", str);
	else if (type == 'q')
		message = ft_strjoin("pipex: unable to parse", str);
	else if (type == 's')
	{
		message = "pipex Error: ft_split failed to allocate memory";
		ft_putstr_fd(message, 2);
		ft_putstr_fd("\n", 2);
		return ;
	}
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
	free(message);
	message = NULL;
}

void	free_cmd(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (!cmd)
		return ;
	if (cmd->argv)
	{
		while (cmd->argv[i])
		{
			free(cmd->argv[i]);
			i++;
		}
		free(cmd->argv);
	}
	if (cmd->path)
		free(cmd->path);
	free(cmd);
}

void	free_pipe_args(t_pipe_args *pa)
{
	int	i;

	i = 0;
	if (!pa || !pa->c)
		return ;
	while (i < pa->cmd_cnt)
	{
		free_cmd(pa->c[i]);
		i++;
	}
	free(pa->c);
}

void	file_fail(t_pipe_args *pa)
{
	free_pipe_args(pa);
	perror(pa->infile);
	close(pa->pipefd[0]);
	close(pa->pipefd[1]);
	exit(EXIT_FAILURE);
}

void	cmd_fail(t_pipe_args *pa)
{
	free_pipe_args(pa);
	close(pa->infile_fd);
	close(pa->outfile_fd);
	close(pa->pipefd[0]);
	close(pa->pipefd[1]);
	exit(127);
}
