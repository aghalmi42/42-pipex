/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghalmi <aghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 18:44:24 by aghalmi           #+#    #+#             */
/*   Updated: 2025/12/17 18:49:29 by aghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static void	free_pipe(int **pipes, int n_pipe)
{
	int	i;

	i = 0;
	while (i < n_pipe)
	{
		free(pipes[i]);
		i++;
	}
	free(pipes);
}

int	exec_pipex_bonus(t_pipex *data)
{
	int		**pipes;
	pid_t	pid;
	int		exit_code;

	pipes = create_all_pipes(data->n_cmd - 1);
	pid = create_all_processus(data, pipes);
	close_parent(data, pipes);
	exit_code = wait_child(pid, data->n_cmd);
	free_pipe(pipes, data->n_cmd - 1);
	free(pid);
	return (exit_code);
}
