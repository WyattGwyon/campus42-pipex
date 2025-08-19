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

typedef struct s_pipe
{
	char	*infile;
	int		fd_in;
	char	*cmd1;
	char	*cmd2;
	char	*outfile;
	int		fd_out;
}	t_pipe;

int	arg_parser(int argc, char *argv[]);

# endif
