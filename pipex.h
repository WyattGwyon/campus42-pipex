/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouden <clouden@student.42madrid.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 16:28:20 by clouden           #+#    #+#             */
/*   Updated: 2025/08/18 16:28:25 by clouden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>

typedef struct s_path
{
	char	*path_start;
	char	**raw_path;
	char	**path_array;
	char	*path;
	int		is_cmd;
	int		i;
	int		j;
}	t_path;

typedef struct s_process
{

}	t_process;

typedef	struct s_cmd
{
	char	*raw_cmd;
	char	**argv;
	char	*path;
	char	*cmd;
	int		fd[2];
	int		prev_fd;
	pid_t	pid;
}	t_cmd;

typedef struct s_pipe_args
{
	char	*infile;
	int		infile_fd;
	char	*outfile;
	int		outfile_fd;
	int		cmd_cnt;
	int		i;
	t_cmd 	**c;
}	t_pipe_args;

int		arg_parser(int argc, char *argv[], t_pipe_args *p);
char	*path_parser(char *cmd, char **envp);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strdup(const char *s1);
void	ft_strarr_free(char ***strarr);
int		ft_printf(const char *fmt, ...);
void	ft_putstr_fd(char *s, int fd);
char	*ft_strjoin(char const *s1, char const *s2);
void	pipex(t_pipe_args *pa, char **envp);

# endif
