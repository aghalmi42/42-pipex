/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghalmi <aghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 17:54:20 by aghalmi           #+#    #+#             */
/*   Updated: 2025/12/14 19:23:45 by aghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	**path(char **envp)
{
	int		i;
	char	*path_line;
	char	**path;

	i = 0;
	path = NULL;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path_line = envp[i] + 5;
			path = ft_split(path_line, ':');
			break ;
		}
		i++;
	}
	return (path);
}

char	*find_cmd_path(char *cmd, char **path)
{
	int	i;
}
