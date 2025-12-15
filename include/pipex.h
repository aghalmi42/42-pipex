/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghalmi <aghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 15:12:52 by aghalmi           #+#    #+#             */
/*   Updated: 2025/12/15 16:49:08 by aghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_pipex
{
	char	*filename;
	char	*fileout;
	int		infile;
	int		outfile;
	char	***cmd;
	int		n_cmd;
	int		fd[2];
	char	**env;
	char	**path;
}			t_pipex;

void		error(char *msg);
char		**path(char **envp);
char		*find_cmd_path(char *cmd, char **path);
void		open_file(t_pipex *data);
void		create_pipe(t_pipex *data);
void		exec_child1(t_pipex *data);
void		exec_child2(t_pipex *data);
void		exec_pipex(t_pipex *data);
#endif