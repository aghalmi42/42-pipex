/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghalmi <aghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 18:51:37 by aghalmi           #+#    #+#             */
/*   Updated: 2025/12/17 19:00:26 by aghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static int	check_limiter(char *line, char *limiter)
{
	int	len;

	len = ft_strlen(limiter);
	if (ft_strncmp(line, limiter, len) == 0)
	{
		if (line[len] == '\n')
			return (1);
	}
	return (0);
}

static void	read_heredoc(int pipe_fd, char *limiter)
{
	char	*line;

	line = get_next_line(STDIN_FILENO);
	while (line)
	{
		if (check_limiter(line, limiter))
		{
			free(line);
			break ;
		}
		write(pipe_fd, line, ft_strlen(line));
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
}

