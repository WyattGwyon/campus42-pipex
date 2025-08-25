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

static char	**three_array(char *s1, char *s2, char *s3)
{
	char	**array[3];

	*array[0] = s1;
	*array[1] = s2;
	*array[2] = s3;
	return (array);
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
				p.j = 0;
				while (p.raw_path[p.j] != NULL)
				{
					p.path_array = three_array(p.raw_path, "/", cmd);
					p.path = ft_strjoin_n(p.path_array);
					p.is_cmd = access(p.path, F_OK);
					if (!p.is_cmd)
						return (p.path);
					p.j++;
				}
			}
			p.i++;
		}
	return (NULL);
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
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		char *cmd_path;
		extern char **environ;
		
		cmd_path = path_parser(argv[2], envp);
		char *exec_argv[] = {argv[2], NULL};
		execve(cmd_path, exec_argv, environ);
		exit(EXIT_SUCCESS);
	}
	
	pid = fork();

	if (pid == 0)
	{
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		//dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		char *cmd_path;
		extern char **environ;
		
		cmd_path = path_parser(argv[3], envp);
		char *exec_argv[] = {argv[3], NULL};
		execve(cmd_path, exec_argv, environ);
		exit(EXIT_SUCCESS);
			
	}
	

	
	printf("hola\n");
	// 

	return (0);
}
