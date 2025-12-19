/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghalmi <aghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 11:10:00 by aghalmi           #+#    #+#             */
/*   Updated: 2025/12/19 11:12:26 by aghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	setup_child1(t_pipex *data)
{
	if (data->infile != -1)
		dup2(data->infile, STDIN_FILENO);
	else
		close(STDIN_FILENO);
	dup2(data->fd[1], STDOUT_FILENO);
	close(data->fd[0]);
	close(data->fd[1]);
	if (data->infile != -1)
		close(data->infile);
	if (data->outfile != -1)
		close(data->outfile);
}

void	setup_child2(t_pipex *data)
{
	dup2(data->fd[0], STDIN_FILENO);
	if (data->outfile != -1)
		dup2(data->outfile, STDOUT_FILENO);
	close(data->fd[0]);
	close(data->fd[1]);
	if (data->infile != -1)
		close(data->infile);
	if (data->outfile != -1)
		close(data->outfile);
}

void	close_parent_fd(t_pipex *data)
{
	close(data->fd[0]);
	close(data->fd[1]);
	if (data->infile != -1)
		close(data->infile);
	if (data->outfile != -1)
		close(data->outfile);
}

void	exec_command(t_pipex *data, char **cmd, int cmd_index)
{
	char	*cmd_path;

	(void)cmd_index;
	cmd_path = find_cmd_path(cmd[0], data->path);
	if (!cmd_path)
	{
		write(2, cmd[0], ft_strlen(cmd[0]));
		write(2, ": command not found\n", 20);
		free_child(data);
		exit(127);
	}
	execve(cmd_path, cmd, data->env);
	free(cmd_path);
	free_child(data);
	perror("execve");
	exit(126);
}
