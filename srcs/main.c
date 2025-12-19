/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghalmi <aghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 15:10:46 by aghalmi           #+#    #+#             */
/*   Updated: 2025/12/19 11:06:45 by aghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static int	get_cmd_start(t_pipex *data)
{
	if (data->heredoc)
		return (3);
	return (2);
}

static void	execute_command(t_pipex *data)
{
	int	exit_code;

	if (data->n_cmd == 2 && data->heredoc == 0)
	{
		create_pipe(data);
		exit_code = exec_pipex(data);
	}
	else
		exit_code = exec_pipex_bonus(data);
	free_child(data);
	if (data->outfile == -1)
		exit(1);
	exit(exit_code);
}

int	main(int ac, char **av, char **envp)
{
	t_pipex	data;
	int		cmd_start;

	if (ac >= 2 && ft_strncmp(av[1], "here_doc", 9) == 0)
		init_heredoc(&data, ac, av);
	else
		init_manda(&data, ac, av);
	data.env = envp;
	data.cmd = malloc(sizeof(char **) * data.n_cmd);
	if (!data.cmd)
		error("fail Malloc");
	cmd_start = get_cmd_start(&data);
	parsing_cmd(&data, av, cmd_start);
	data.path = path(envp);
	if (!data.path)
	{
		free_child(&data);
		error("Path is not found");
	}
	if (data.heredoc)
		open_file_heredoc(&data);
	else
		open_file(&data);
	execute_command(&data);
}
