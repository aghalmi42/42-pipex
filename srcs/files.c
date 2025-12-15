/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghalmi <aghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 16:15:29 by aghalmi           #+#    #+#             */
/*   Updated: 2025/12/15 16:57:55 by aghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	open_file(t_pipex *data)
{
	data->infile = open(data->filename, O_RDONLY);
	if (data->infile == -1)
		error("Error for open infile fd\n");
	data->outfile = open(data->fileout, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data->outfile == -1)
		error("Error for open outfile fd\n");
}
