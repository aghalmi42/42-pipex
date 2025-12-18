/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghalmi <aghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 18:08:43 by aghalmi           #+#    #+#             */
/*   Updated: 2025/12/18 19:12:33 by aghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static void	redirect_input(t_pipex *data, int i, int **pipes)
{
	if (i == 0)
	{
		if (data->infile != -1)
			dup2(data->infile, STDIN_FILENO);
		else
			close(STDIN_FILENO);
	}
	else
		dup2(pipes[i - 1][0], STDIN_FILENO);
}

static void	redirect_output(t_pipex *data, int i, int **pipes)
{
	if (i == data->n_cmd - 1)
	{
		if (data->outfile != -1)
			dup2(data->outfile, STDOUT_FILENO);
	}
	else
		dup2(pipes[i][1], STDOUT_FILENO);
}

static void	close_pipe(int **pipes, int n_pipe)
{
	int	i;

	i = 0;
	while (i < n_pipe)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}

static void	exec_cmd(t_pipex *data, int i, int **pipes, char *cmd_path)
{
	(void)pipes;
	if (!cmd_path)
	{
		write(2, data->cmd[i][0], ft_strlen(data->cmd[i][0]));
		write(2, "cmd not found\n", 14);
		free_child(data);
		exit(127);
	}
	execve(cmd_path, data->cmd[i], data->env);
	free(cmd_path);
	free_child(data);
	perror("execve");
	exit(126);
}

void	execute_cmd(t_pipex *data, int i, int **pipes)
{
	char	*cmd_path;

	redirect_input(data, i, pipes);
	redirect_output(data, i, pipes);
	close_pipe(pipes, data->n_cmd - 1);
	if (data->infile != -1)
		close(data->infile);
	if (data->outfile != -1)
		close(data->outfile);
	cmd_path = find_cmd_path(data->cmd[i][0], data->path);
	exec_cmd(data, i, pipes, cmd_path);
}
