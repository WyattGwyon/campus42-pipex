/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_works.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouden <clouden@student.42madird.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 12:13:27 by clouden           #+#    #+#             */
/*   Updated: 2025/10/14 17:19:30 by clouden          ###   ########.fr       */
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
	pa->c[pa->i]->pid = fork();
	if (pa->c[pa->i]->pid == -1)
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
			file_fail(pa, pa->infile);
		assign_cmd(pa->c[pa->i], pa->infile);
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

void	middle_child(char **envp, t_pipe_args *pa)
{
	if (pa->c[pa->i]->pid == 0)
	{	
		assign_cmd(pa->c[pa->i], pa->outfile);
		if (access(pa->c[pa->i]->cmd, X_OK) == 0)
			pa->c[pa->i]->path = pa->c[pa->i]->cmd;
		else if (find_cmd(pa->c[pa->i], envp) != 0)
			cmd_fail(pa);
		dup2(pa->prev_fd, STDIN_FILENO);
		dup2(pa->pipefd[1], STDOUT_FILENO);
		close(pa->prev_fd);
		close(pa->pipefd[0]);
		close(pa->pipefd[1]);
		execve(pa->c[pa->i]->path, pa->c[pa->i]->argv, envp);
		perror("execve");
		exit(127);	
	}
}

void	last_child(char **envp, t_pipe_args *pa)
{
	if (pa->c[pa->i]->pid == 0)
	{
		pa->outfile_fd = open(pa->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (pa->outfile_fd == -1)
			file_fail(pa, pa->outfile);
		assign_cmd(pa->c[pa->i], pa->outfile);
		if (access(pa->c[pa->i]->cmd, X_OK) == 0)
			pa->c[pa->i]->path = pa->c[pa->i]->cmd;
		else if (find_cmd(pa->c[pa->i], envp) != 0)
			cmd_fail(pa);
		dup2(pa->pipefd[0], STDIN_FILENO);
		dup2(pa->outfile_fd, STDOUT_FILENO);
		close(pa->outfile_fd);
		close(pa->pipefd[0]);	
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
	pa->prev_fd = -1;
	pipe_it(pa);
	fork_it(pa);
	first_child(envp, pa);
	pa->i = 1;
	while (pa->i < pa->cmd_cnt - 1)
	{
		close(pa->prev_fd);
		pa->prev_fd = pa->pipefd[0];
		close(pa->pipefd[1]);	
		pipe_it(pa);
		fork_it(pa);
		middle_child(envp, pa);
		close(pa->pipefd[1]);
		pa->i++;
	}
	close(pa->prev_fd);
	fork_it(pa);
	last_child(envp, pa);
	close(pa->pipefd[0]);
	int i = 0;
	pid_t last_pid;
	while (i < pa->cmd_cnt)
	{
		last_pid = waitpid(-1 , &status, 0);
		if (last_pid == pa->c[pa->cmd_cnt - 1]->pid) 
		{
			if (WIFEXITED(status))
				exit_code = WEXITSTATUS(status);
		}
		i++;
	}	
	return (exit_code);
}
