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
	
int	assign_cmd(t_cmd *c)
{
	c->argv = ft_split(c->raw_cmd, ' ');
	if (!c->argv)
	{
		print_error(NULL, 's');
		return (127);
	}
	if (c->argv[0] == 0)
	{
		print_error("", 'p');
		return (127);
	}
	c->cmd = c->argv[0];
	
	return (0);
}

int find_cmd(t_cmd *c, char **envp)
{
	c->path = path_parser(c->cmd, envp);
	if (!c->path)
	{
		print_error(c->cmd, 'c');
		return (127);	
	}
	return (0);
}

void	pipe_n_fork_it(t_pipe_args *pa)
{
	if (pa->i < (pa->cmd_cnt - 1))
		if (pipe(pa->c[pa->i]->fd) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		};
	if (pa->i > 0)
        pa->c[pa->i]->prev_fd = pa->c[pa->i-1]->fd[0];
	pa->c[pa->i]->pid = fork();
	if (pa->c[pa->i]->pid  == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
}

void	first_child(char **envp, t_pipe_args *pa)
{
	if (pa->c[pa->i]->pid == 0)
	{
		pa->infile_fd = open(pa->infile, O_RDONLY);
		if (pa->infile_fd == -1)
			file_fail(pa);
		assign_cmd(pa->c[pa->i]);
		if (access(pa->c[pa->i]->cmd, X_OK) == 0)
			pa->c[pa->i]->path = pa->c[pa->i]->cmd;
		else if (find_cmd(pa->c[pa->i], envp) != 0)
			cmd_fail(pa);
		dup2(pa->infile_fd, STDIN_FILENO);
		dup2(pa->pipefd[1], STDOUT_FILENO);
		close(pa->infile_fd);
		close(pa->pipefd[0]);
		close(pa->pipefd[1]);
		execve(pa->c[pa->i]->path, pa->c[pa->i]->argv, envp);
		perror("execve");
		exit(127);
	}
}

void last_child(char **envp, t_pipe_args *pa)
{
	if (pa->c[pa->i]->pid == 0)
	{
		pa->outfile_fd = open(pa->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (pa->outfile_fd == -1)
			file_fail(pa);
		assign_cmd(pa->c[pa->i]);
		if (access(pa->c[pa->i]->cmd, X_OK) == 0)
			pa->c[pa->i]->path = pa->c[pa->i]->cmd;
		else if (find_cmd(pa->c[pa->i], envp) != 0)
			cmd_fail(pa);
		dup2(pa->c[pa->i]->prev_fd, STDIN_FILENO);
		dup2(pa->outfile_fd, STDOUT_FILENO);
		close(pa->outfile_fd);
		close(pa->pipefd[0]);
		close(pa->pipefd[1]);
		execve(pa->c[pa->i]->path, pa->c[pa->i]->argv, envp);
		perror("execve");
		exit(127);
	}
}

int	pipex(t_pipe_args *pa, char **envp)
{
	int	status;
	int exit_code;

	pa->i = 0;
	pipe_n_fork_it(pa);
	first_child(envp, pa);
	pa->i = 1;
	pa->c[pa->i]->prev_fd = pa->pipefd[0];
	pipe_n_fork_it(pa);
	last_child(envp, pa);
	if (pa->pipefd[0] >= 0)
		close(pa->pipefd[0]);
	if (pa->pipefd[1] <= 0)
		close(pa->pipefd[1]);
	if (pa->c[pa->i]->prev_fd)
		close(pa->c[pa->i]->prev_fd);
	if (pa->c && pa->c[0] && pa->c[0]->pid > 0)
    	waitpid(pa->c[0]->pid, NULL, 0);
	if (pa->c && pa->c[1] && pa->c[1]->pid > 0) 
	{
    	waitpid(pa->c[1]->pid, &status, 0);
    	if (WIFEXITED(status))
        	exit_code = WEXITSTATUS(status);
    	else
        	exit_code = 1;
	} 
	else 
		exit_code = 1;
	return exit_code;
}
