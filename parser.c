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

// frees the first string 
// because the first arg of ft_stjoin_n is always a malloced process
// this is healper function only for ft_strjoin_n
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

// static char	**three_array(char *s1, char *s2, char *s3)
// {
// 	char	*array[4];

// 	array[0] = s1;
// 	array[1] = s2;
// 	array[2] = s3;
// 	array[3] = NULL;
// 	return (array);
// }

char	*make_path(const char *dir, const char *cmd)
{
	char	*tmp;
	char	*full;

	if (!dir || !cmd)
		return (NULL);
	tmp = ft_strjoin(dir , "/");
	if (!tmp)
		return (NULL);
	full = ft_strjoin(tmp, cmd);
	free(tmp);
	if (!full)
		return (NULL);
	return(full);
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
				if (!p.raw_path)
					return (NULL);
				p.j = 0;
				while (p.raw_path[p.j] != NULL)
				{
					if (!(p.path = make_path(p.raw_path[p.j], cmd)))
						return(ft_strarr_free(&p.raw_path), NULL);
					if (!access(p.path, X_OK))
						return (ft_strarr_free(&p.raw_path), p.path);
					free(p.path);
					p.j++;
				}
			}
			p.i++;
		}
	return (NULL);
}

int	arg_parser(int argc, char *argv[], char **envp, t_pipex *p)
{
	int 	i;
	int		pipefd[2];
	pid_t	pid;


	i = 1;
	if (argc < 5)
	{
		return (0);
	}

	char *cmd_path;
	extern char **environ;
	cmd_path = path_parser(argv[2], envp);
	if (!cmd_path)
	{
		fprintf(stderr, "%s: command not found: %s\n", argv[0], argv[2]);
		exit(EXIT_FAILURE);
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
	return (0);
}
