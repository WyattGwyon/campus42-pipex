/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_works.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouden <clouden@student.42madird.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 12:13:27 by clouden           #+#    #+#             */
/*   Updated: 2025/08/26 12:13:34 by clouden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_error(char *str, char type)
{
	char *message;

	message = "NONE";
	if (type == 'c')
		message = ft_strjoin("pipex: command not found: ", str);	
	else if (type == 'p')
		message = ft_strjoin("pipex: permission denied: ", str);
	else if (type == 'f')
		message = ft_strjoin("pipex: no such file or directory: ", str);
	else if (type == 'q')
		message = ft_strjoin("pipex: unable to parse", str);
	else if (type == 's')
		message = "pipex Error: ft_split failed to allocate memory";
	else if (type == 'j')
		message = "pipex Error: ft_strjoin failed to allocate memory";
	if (!message)
		print_error(NULL, 'j');
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
	free(message);
}


// void	close_pipe(t_pipe_args *pa, int fd[2])
// {
	// 	if (fd[0] != -1)
	// 		close(fd[0]);
	// 	if (fd[1] != -1)
	// 		close(fd[1]);
	// 	if (prev_fd != -1)
	// 		close(prev_fd);
	// 	if (pa->infile_fd != -1)
	// 		close(pa->infile_fd);
	// 	if (pa->outfile_fd != -1)
	// 		close(pa->outfile_fd);
	// }

	
void	build_cmd(t_cmd *c, char **envp, int fd[2])
{
	c->argv = ft_split(c->raw_cmd, ' ');
	if (!c->argv)
		print_error(NULL, 's');
	if (c->argv[0] == 0)
	{
		print_error("", 'p');
		close(fd[0]);
		close(fd[1]);
		exit(127);
	}
	c->cmd = c->argv[0];
	c->path = path_parser(c->cmd, envp);
	if (!c->path)
		print_error(c->cmd, 'c'); 
	
}

void	pipe_n_fork_it(t_pipe_args *pa)
{
	if (pa->i != (pa->cmd_cnt - 1))
		if (pipe(pa->c[pa->i]->fd) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		};
	pa->c[pa->i]->pid = fork();
	if (pa->c[pa->i]->pid  == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
}

void	pipe_loop(char **envp, t_cmd *cmd, t_pipe_args *pa)
{
	if (pa->i == 0)
		dup2(pa->infile_fd, STDIN_FILENO);
	else
		dup2(cmd->prev_fd, STDIN_FILENO);
	close(cmd->fd[0]);
	if (pa->i == pa->cmd_cnt - 1)
		dup2(pa->outfile_fd, STDOUT_FILENO);
	else
		dup2(cmd->fd[1], STDOUT_FILENO);
	close(cmd->fd[1]);
	for (int i = 0; cmd->argv[i]; i++)
	{
		fprintf(stderr, "cmd->path %s\n", cmd->path);
		fprintf(stderr, "cmd->argv[%d] %s\n", i, cmd->argv[i]);
	}
	execve(cmd->path, cmd->argv, envp);
	perror("execve");
	exit(127);
}

void	pipex(t_pipe_args *pa, char **envp)
{
	pa->i = 0;
	pa->infile_fd = open(pa->infile, O_RDONLY);
	if (pa->infile_fd == -1)
		perror(pa->infile);
	pa->outfile_fd = open(pa->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pa->outfile_fd == -1)
		perror(pa->outfile);
	while (pa->i < pa->cmd_cnt)
	{
		pipe_n_fork_it(pa);		
		if (pa->c[pa->i]->pid == 0)
		{
			build_cmd(pa->c[pa->i], envp, pa->c[pa->i]->fd);
			pipe_loop(envp, pa->c[pa->i], pa);	
		}
		if (pa->c[pa->i]->pid > 0)
		{	
			if (pa->i < pa->cmd_cnt - 1)
				pa->c[pa->i + 1]->prev_fd = pa->c[pa->i]->fd[0];
			if (pa->i != 0)
				close(pa->c[pa->i]->fd[0]);
			close(pa->c[pa->i]->fd[1]);
		}
		pa->i++;
	}	
	int i = 0;
	int	status;
	while (i < pa->cmd_cnt)
	{
		if (pa->c[pa->i]->pid > 0)
		{	
			waitpid(pa->c[i]->pid, &status, 0);
			i++;
		}
	}
	
	// close_pipe(pa, fd);
	return ;
}
