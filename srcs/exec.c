/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghalmi <aghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 16:22:45 by aghalmi           #+#    #+#             */
/*   Updated: 2025/12/15 16:52:40 by aghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	exec_child1(t_pipex *data)
{
	char	*cmd_path;

	dup2(data->infile, STDIN_FILENO);
	dup2(data->fd[1], STDOUT_FILENO);
	close(data->fd[0]);
	close(data->fd[1]);
	close(data->infile);
	close(data->outfile);
	cmd_path = find_cmd_path(data->cmd[0][0], data->path);
	if (!cmd_path)
		error("cmd not found\n");
	execve(cmd_path, data->cmd[0], data->env);
	error("Fail execve()\n");
}

void	exec_child2(t_pipex *data)
{
	char	*cmd_path;

	dup2(data->fd[0], STDIN_FILENO);
	dup2(data->outfile, STDOUT_FILENO);
	close(data->fd[0]);
	close(data->fd[1]);
	close(data->infile);
	close(data->outfile);
	cmd_path = find_cmd_path(data->cmd[1][0], data->path);
	if (!cmd_path)
		error("cmd not found\n");
	execve(cmd_path, data->cmd[1], data->env);
	error("fail execve()\n");
}

void	exec_pipex(t_pipex *data)
{
	pid_t	pid1;
	pid_t	pid2;

	pid1 = fork();
	if (pid1 == -1)
		error("Fail fork\n");
	if (pid1 == 0)
		exec_child1(data);
	pid2 = fork();
	if (pid2 == -1)
		error("Fail fork\n");
	if (pid2 == 0)
		exec_child2(data);
	close(data->fd[0]);
	close(data->fd[1]);
	close(data->infile);
	close(data->outfile);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}
