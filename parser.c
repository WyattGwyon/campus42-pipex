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



char *path_parser(char *cmd, char **envp)
{
	t_path	p;
	int		i;
	int		j;

	p.path_start = "PATH=";
	i = 0;
	while (envp[i] != NULL) 
		{
			if (!ft_strncmp(p.path_start, envp[i], 5))
			{
				p.raw_path = ft_split(envp[i] + 5, ':');
				j = 0;
				while (p.raw_path[j] != NULL)
				{
					p.path = ft_strjoin(p.raw_path[j], "/");
					p.path = ft_strjoin(p.path, cmd);
					p.is_cmd = access(p.path, F_OK);
					if (!cmd)
					{
						printf("COMMAND EXISTS at this PATH %s\n", p.path);
						return (p.path);
					}
					else 
						printf("IS NOT HERE %s\n", p.path);
					j++;
				}
			}
			i++;
		}
	return(NULL);
}

int	arg_parser(int argc, char *argv[], char **envp)
{
	// t_pipe	pp;
	int 	i;
	int		pipefd[2];
	pid_t	pid;

	i = 1;
	if (argc < 5)
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
		char *cmd_path;
		
		cmd_path = path_parser(argv[2], envp);
		printf("%s\n", cmd_path);
	}

	
	printf("hola\n");
	// 

	return (0);
}
