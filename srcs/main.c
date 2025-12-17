/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghalmi <aghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 15:10:46 by aghalmi           #+#    #+#             */
/*   Updated: 2025/12/17 19:35:12 by aghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

// int	main(int ac, char **av, char **envp)
// {
// 	t_pipex	data;
// 	int		exit_code;

// 	if (ac != 5)
// 		error("ERROR\nUsage : ./pipex file1 cmd1 cmd2 file2");
// 	data.filename = av[1];
// 	data.fileout = av[4];
// 	data.env = envp;
// 	data.n_cmd = 2;
// 	data.cmd = malloc(sizeof(char **) * 2);
// 	if (!data.cmd)
// 		error("Malloc fail\n");
// 	data.cmd[0] = ft_split(av[2], ' ');
// 	data.cmd[1] = ft_split(av[3], ' ');
// 	data.path = path(envp);
// 	if (!data.path)
// 	{
// 		free_child(&data);
// 		error("PATH is not found\n");
// 	}
// 	if (!data.cmd[0] || !data.cmd[1] || !data.cmd[0][0] || !data.cmd[1][0]
// 		|| data.cmd[0][0][0] == '\0' || data.cmd[1][0][0] == '\0')
// 	{
// 		free_child(&data);
// 		error("cmd empty");
// 	}
// 	open_file(&data);
// 	create_pipe(&data);
// 	exit_code = exec_pipex(&data);
// 	free_child(&data);
// 	if (data.outfile == -1)
// 		return (1);
// 	return (exit_code);
// }
