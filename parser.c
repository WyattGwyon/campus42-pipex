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

int	arg_parser(int argc, char *argv[], char **envp)
{
	// t_pipe	pp;
	int 	i;
	int		pipefd[2];
	pid_t	pid;

	i = 1;
	if (argc != 5)
	{
		return (0);
	}
	while (i < argc)
	{
		printf("%s ", argv[i]);
		i++;
	}
	printf("\n");


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
		//printf("hijo\n");
		// int i = 0;
		// while (envp[i] != NULL)
		// {
		// 	printf("%s\n", envp[i]);
		// 	i++;
		// }
		// close(pipefd[0]);
		// dup2(pipefd[1], STDOUT_FILENO);
		// close(pipefd[1]);
		// execve(*argv[2]);
		exit(EXIT_SUCCESS);
	}
	if (pid > 0)
	{
		printf("pad\n");
		int i = 0;
		char *path_start = "PATH=";
		char **raw_path;
		char *path;
		int	cmd;
		while (envp[i] != NULL) 
		{
			if (!ft_strncmp(path_start, envp[i], 5))
			{
				printf("%s\n", (envp[i] + 5));
				raw_path = ft_split(envp[i] + 5, ':');
				int j = 0;
				while (raw_path[j] != NULL)
				{
					path = ft_strjoin(raw_path[j], "/");
					path = ft_strjoin(path, argv[2]);
					//printf("%s\n", path);
					cmd = access(path, F_OK);
					if (cmd)
						printf("COMMAND EXISTS at this PATH %s\n", path);
					else 
						printf("IS NOT HERE %s\n", path);
					j++;
				}
			}
			i++;
		}
	}

	
	printf("hola\n");
	// 

	return (0);
}
