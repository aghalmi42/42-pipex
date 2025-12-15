/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghalmi <aghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 15:10:46 by aghalmi           #+#    #+#             */
/*   Updated: 2025/12/15 17:18:02 by aghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	main(int ac, char **av, char **envp)
{
	t_pipex	data;

	if (ac != 5)
		error("ERROR\nStruct usage : ./pipex file1 cmd1 cmd2 file2");
	data.filename = av[1];
	data.fileout = av[4];
	data.env = envp;
	data.n_cmd = 2;
	data.cmd = malloc(sizeof(char **) * 2);
	if (!data.cmd)
		error("Malloc fail\n");
	data.cmd[0] = ft_split(av[2], ' ');
	data.cmd[1] = ft_split(av[3], ' ');
	if (!data.cmd[0] || !data.cmd[1])
		error("Parsing cmd fail\n");
	data.path = path(envp);
	if (!data.path)
		error("PATH is not found\n");
	open_file(&data);
	create_pipe(&data);
	exec_pipex(&data);
	return (0);
}
