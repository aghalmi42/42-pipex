/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghalmi <aghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 17:54:20 by aghalmi           #+#    #+#             */
/*   Updated: 2025/12/16 14:26:52 by aghalmi          ###   ########.fr       */
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
	int		i;
	char	*full_path;
	char	*tmp;

	i = 0;
	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		full_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}
