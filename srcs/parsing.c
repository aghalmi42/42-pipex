/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghalmi <aghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 19:00:45 by aghalmi           #+#    #+#             */
/*   Updated: 2025/12/19 10:48:53 by aghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static void	free_prev_cmd(t_pipex *data, int up)
{
	int	j;

	j = 0;
	while (j < up)
	{
		if (data->cmd[j])
			free_tab(data->cmd[j]);
		j++;
	}
	free(data->cmd);
}

void	parsing_cmd(t_pipex *data, char **av, int cmd_start)
{
	int	i;

	i = 0;
	while (i < data->n_cmd)
	{
		if (!av[cmd_start + i] || av[cmd_start + i][0] == '\0')
		{
			free_prev_cmd(data, i);
			error("Cmd empty");
		}
		data->cmd[i] = ft_split(av[cmd_start + i], ' ');
		if (!data->cmd[i] || !data->cmd[i][0])
		{
			free_prev_cmd(data, i + 1);
			error("Cmd empty");
		}
		if (data->cmd[i][0][0] == '\0')
		{
			free_prev_cmd(data, i + 1);
			error("Cmd empty");
		}
		i++;
	}
}

void	init_manda(t_pipex *data, int ac, char **av)
{
	if (ac < 5)
		error("ERROR\nUsage : ./pipex file1 cmd1 cmd2 ... file2");
	data->heredoc = 0;
	data->limiter = NULL;
	data->filename = av[1];
	data->fileout = av[ac - 1];
	data->n_cmd = ac - 3;
}

void	init_heredoc(t_pipex *data, int ac, char **av)
{
	if (ac < 6)
		error("ERROR\nUsage ./pipex here_doc LIMITER cmd1 cmd2 file2");
	data->heredoc = 1;
	data->limiter = av[2];
	data->filename = NULL;
	data->fileout = av[ac - 1];
	data->n_cmd = ac - 4;
}
