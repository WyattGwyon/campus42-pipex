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

typedef struct s_pipe
{
	char	*infile;
	int		fd_in;
	char	*cmd1;
	char	*cmd2;
	char	*outfile;
	int		fd_out;
}	t_pipe;

typedef struct s_path
{
	char	*path_start;//
	char	**raw_path;//
	char	**path_array;
	char	*path;//
	int		is_cmd;//
	int		i;//
	int		j;//
}	t_path;

typedef	struct s_cmd
{
	char	*raw_cmd;
	char	**argv;
	char	*path;
}	t_cmd;

typedef struct s_pipex
{
	char	*infile;
	char	*outfile;
	t_cmd 	**commands;
	int		cmd_cnt;
}	t_pipex;

int		arg_parser(int argc, char *argv[], char **envp, t_pipex *p);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strjoin_n(char **str_segs);
size_t	ft_strlen(const char *s);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strdup(const char *s1);
char	*ft_strjoin_n(char **str_segs);
void	ft_strarr_free(char ***strarr);

# endif
