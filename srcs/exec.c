/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghalmi <aghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 16:22:45 by aghalmi           #+#    #+#             */
/*   Updated: 2025/12/16 14:17:34 by aghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	exec_child1(t_pipex *data)
{
	char	*cmd_path;

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
	cmd_path = find_cmd_path(data->cmd[0][0], data->path);
	if (!cmd_path)
	{
		write(2, data->cmd[0][0], ft_strlen(data->cmd[0][0]));
		write(2, "cmd not found\n", 14);
		free_child(data);
		exit(127);
	}
	execve(cmd_path, data->cmd[0], data->env);
	free(cmd_path);
	free_child(data);
	perror("execve");
	exit(126); // cmd trv mais pas executable
}

void	exec_child2(t_pipex *data)
{
	char	*cmd_path;

	dup2(data->fd[0], STDIN_FILENO);
	if (data->outfile != -1)
		dup2(data->outfile, STDOUT_FILENO);
	close(data->fd[0]);
	close(data->fd[1]);
	if (data->infile != -1)
		close(data->infile);
	if (data->outfile != -1)
		close(data->outfile);
	cmd_path = find_cmd_path(data->cmd[1][0], data->path);
	if (!cmd_path)
	{
		write(2, data->cmd[1][0], ft_strlen(data->cmd[1][0]));
		write(2, "cmd not found\n", 14);
		free_child(data);
		exit(127);
	}
	execve(cmd_path, data->cmd[1], data->env);
	free(cmd_path);
	free_child(data);
	perror("execve");
	exit(126);
}

int	exec_pipex(t_pipex *data)
{
	pid_t	pid1;
	pid_t	pid2;
	int		status;
	int		exit_code;

	exit_code = 0;
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
	if (data->infile != -1)
		close(data->infile);
	if (data->outfile != -1)
		close(data->outfile);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, &status, 0);
	if (WIFEXITED(status))
		exit_code = WEXITSTATUS(status);
	return (exit_code);
}
