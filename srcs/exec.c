/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghalmi <aghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 16:22:45 by aghalmi           #+#    #+#             */
/*   Updated: 2025/12/19 11:13:16 by aghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	exec_child1(t_pipex *data)
{
	setup_child1(data);
	exec_command(data, data->cmd[0], 0);
}

void	exec_child2(t_pipex *data)
{
	setup_child2(data);
	exec_command(data, data->cmd[1], 1);
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
	close_parent_fd(data);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, &status, 0);
	if (WIFEXITED(status))
		exit_code = WEXITSTATUS(status);
	return (exit_code);
}
