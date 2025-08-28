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

pid_t	pipe_n_fork_it(int fd[2], int i, int cnt)
{
	pid_t	pid;

	if (i != (cnt - 1))
		if (pipe(fd) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		};
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	return (pid);
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
	if (!c->argv[0])
	{
		print_error("", 'p');
		close(fd[0]);
		close(fd[1]);
		exit(127);
	}
	c->cmd = c->argv[0];
	c->path = path_parser(c->raw_cmd, envp);

	if (!c->path)
		print_error(c->cmd, 'c'); 

}

void	pipe_loop(int fd[2], char **envp, t_pipe_args *pa)
{
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	execve(pa->c[pa->i]->path, pa->c[pa->i]->argv, envp);
	perror("execve");
	exit(127);
}

void	pipex(t_pipe_args *pa, char **envp)
{
	int	fd[2];
	pid_t	pid;
	// pid_t	pids[pa->cmd_cnt];

	pa->i = 0;
	pa->infile_fd = open(pa->infile, O_RDONLY);
	if (pa->infile_fd == -1)
		perror(pa->infile);
	pa->outfile_fd = open(pa->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pa->outfile_fd == -1)
		perror(pa->outfile);
	while (pa->i < pa->cmd_cnt)
	{
		pid = pipe_n_fork_it(fd, pa->i, pa->cmd_cnt);		
		if (pid == 0)
		{
			build_cmd(pa->c[pa->i], envp, fd);
			pipe_loop(fd, envp, pa);
		}
		pa->i++;
	}
	// close_pipe(pa, fd);
}
