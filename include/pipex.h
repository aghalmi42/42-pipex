/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghalmi <aghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 15:12:52 by aghalmi           #+#    #+#             */
/*   Updated: 2025/12/18 12:00:33 by aghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include "../libft/get_next_line.h"
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
	char	*limiter;
	int		heredoc;
}			t_pipex;

void		error(char *msg);
char		**path(char **envp);
char		*find_cmd_path(char *cmd, char **path);
void		open_file(t_pipex *data);
void		create_pipe(t_pipex *data);
void		exec_child1(t_pipex *data);
void		exec_child2(t_pipex *data);
int			exec_pipex(t_pipex *data);
void		free_tab(char **tab);
void		free_child(t_pipex *data);
void		execute_cmd(t_pipex *data, int i, int **pipes);
int			**create_all_pipe(int n_pipe);
pid_t		*create_all_processus(t_pipex *data, int **pipes);
void		close_parent(t_pipex *data, int **pipes);
int			wait_child(pid_t *pid, int n_cmd);
int			exec_pipex_bonus(t_pipex *data);
int			here_doc(char *limiter);
void		open_file_heredoc(t_pipex *data);
void		parsing_cmd(t_pipex *data, char **av, int cmd_start);
void		init_manda(t_pipex *data, int ac, char **av);
void		init_heredoc(t_pipex *data, int ac, char **av);
#endif