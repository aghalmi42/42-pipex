/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bonus2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghalmi <aghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 18:25:18 by aghalmi           #+#    #+#             */
/*   Updated: 2025/12/18 12:04:20 by aghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	**create_all_pipe(int n_pipe)
{
	int	**pipes;
	int	i;

	i = 0;
	pipes = malloc(sizeof(int *) * n_pipe);
	if (!pipes)
		error("Fail malloc pipe");
	while (i < n_pipe)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i])
			error("Fail malloc pipe");
		if (pipe(pipes[i]) == -1)
			error("Fail to create pipe");
		i++;
	}
	return (pipes);
}

pid_t	*create_all_processus(t_pipex *data, int **pipes)
{
	pid_t	*pid;
	int		i;

	i = 0;
	pid = malloc(sizeof(pid_t) * data->n_cmd);
	if (!pid)
		error("Fail malloc pid");
	while (i < data->n_cmd)
	{
		pid[i] = fork();
		if (pid[i] == -1)
			error("Fail fork");
		if (pid[i] == 0)
			execute_cmd(data, i, pipes);
		i++;
	}
	return (pid);
}

void	close_parent(t_pipex *data, int **pipes)
{
	int	i;

	i = 0;
	while (i < data->n_cmd - 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
	if (data->infile != -1)
		close(data->infile);
	if (data->outfile != -1)
		close(data->outfile);
}

int	wait_child(pid_t *pid, int n_cmd)
{
	int	i;
	int	status;

	i = 0;
	while (i < n_cmd)
	{
		if (i == n_cmd - 1)
			waitpid(pid[i], &status, 0);
		else
			waitpid(pid[i], NULL, 0);
		i++;
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (0);
}
