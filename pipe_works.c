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

void	pipe_it(t_pipe_args *pa)
{
	if (pipe(pa->pipefd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
}

void	fork_it(t_pipe_args *pa)
{
	pa->pid = fork();
	if (pa->pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
}

void	first_child(char **envp, t_pipe_args *pa)
{
	if (pa->pid == 0)
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

void	last_child(char **envp, t_pipe_args *pa)
{
	if (pa->pid == 0)
	{
		pa->outfile_fd = open(pa->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (pa->outfile_fd == -1)
			file_fail(pa);
		assign_cmd(pa->c[pa->i]);
		if (access(pa->c[pa->i]->cmd, X_OK) == 0)
			pa->c[pa->i]->path = pa->c[pa->i]->cmd;
		else if (find_cmd(pa->c[pa->i], envp) != 0)
			cmd_fail(pa);
		dup2(pa->pipefd[0], STDIN_FILENO);
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
	int	exit_code;

	pa->i = 0;
	pipe_it(pa);
	fork_it(pa);
	first_child(envp, pa);
	pa->i = 1;
	fork_it(pa);
	last_child(envp, pa);
	close(pa->pipefd[0]);
	close(pa->pipefd[1]);
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
	return (exit_code);
}
