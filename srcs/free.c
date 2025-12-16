/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghalmi <aghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 14:18:20 by aghalmi           #+#    #+#             */
/*   Updated: 2025/12/16 14:23:41 by aghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_child(t_pipex *data)
{
	if (data->cmd)
	{
		if (data->cmd[0])
			free_tab(data->cmd[0]);
		if (data->cmd[1])
			free_tab(data->cmd[1]);
		free(data->cmd);
	}
	if (data->path)
		free_tab(data->path);
}
