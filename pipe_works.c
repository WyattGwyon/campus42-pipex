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




int	execute_pipe(t_pipex p)
{
	int	pipefd[2];
	int	pid;

	if (pipe(pipefd) == -1)
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
	if (pid == 0)
	{
		char *cmd_path;
		extern char **environ;
		cmd_path = path_parser(argv[2], envp);
		if (!cmd_path)
		{
			fprintf(stderr, "%s: command not found: %s\n", argv[0], argv[2]);
			exit(EXIT_FAILURE);
		}
		printf("cmd1_path %s\n", cmd_path);
		char *exec_argv[] = {argv[2], NULL};
		
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		execve(cmd_path, exec_argv, environ);
		exit(EXIT_SUCCESS);
	}
	
	pid = fork();
	
	if (pid == 0)
	{
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		char *cmd_path;
		extern char **environ;
		
		cmd_path = path_parser(argv[3], envp);
		fprintf(stderr,"cmd2_path %s\n", cmd_path);
		char *exec_argv[] = {argv[3], NULL};
		execve(cmd_path, exec_argv, environ);
		exit(EXIT_SUCCESS);	
	}
	
	pid = fork();
	
	if (pid == 0)
	{
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
		char *cmd_path;
		extern char **environ;
		
		cmd_path = path_parser(argv[4], envp);
		printf("cmd3_path %s\n", cmd_path);
		char *exec_argv[] = {argv[3], NULL};
		execve(cmd_path, exec_argv, environ);
		exit(EXIT_SUCCESS);	
	}
}