/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghalmi <aghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 18:51:37 by aghalmi           #+#    #+#             */
/*   Updated: 2025/12/19 11:04:07 by aghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static int	check_limiter(char *line, char *limiter)
{
	int	len_line;
	int	len_limiter;

	len_limiter = ft_strlen(limiter);
	len_line = ft_strlen(line);
	if (line[len_line - 1] == '\n')
		len_line--;
	if (len_line == len_limiter && ft_strncmp(line, limiter, len_limiter) == 0)
		return (1);
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

int	here_doc(char *limiter)
{
	int	pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		error("Fail pipe");
	read_heredoc(pipe_fd[1], limiter);
	close(pipe_fd[1]);
	return (pipe_fd[0]);
}

void	open_file_heredoc(t_pipex *data)
{
	data->infile = here_doc(data->limiter);
	data->outfile = open(data->fileout, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (data->outfile == -1)
		perror(data->fileout);
}
