/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghalmi <aghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 03:20:57 by aghalmi           #+#    #+#             */
/*   Updated: 2025/11/27 01:59:03 by aghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*line_extracting(char *save)
{
	size_t	i;
	size_t	len;
	char	*new_line;
	char	*str;

	if (!save || !*save)
		return (NULL);
	i = 0;
	len = 0;
	new_line = ft_strchr(save, '\n');
	if (new_line == NULL)
		return (ft_strdup(save));
	len = new_line - save + 1;
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	while (i < len)
	{
		str[i] = save[i];
		i++;
	}
	str[len] = '\0';
	return (str);
}

static char	*line_update(char *save)
{
	char	*next_line;
	char	*next_str;

	next_line = ft_strchr(save, '\n');
	if (!next_line)
	{
		free(save);
		return (NULL);
	}
	if (!*(next_line + 1))
	{
		free(save);
		return (NULL);
	}
	next_str = ft_strdup(next_line + 1);
	free(save);
	return (next_str);
}

static char	*all_free(char *s1, char *s2)
{
	free(s1);
	free(s2);
	return (NULL);
}

static char	*line_read(int fd, char *save)
{
	char	*read_buff;
	char	*str;
	size_t	len_read;

	if (!save)
		save = ft_strdup("");
	len_read = 1;
	read_buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!read_buff)
		return (NULL);
	while (len_read > 0 && (!ft_strchr(save, '\n')))
	{
		len_read = read(fd, read_buff, BUFFER_SIZE);
		if (len_read == (size_t) - 1)
			return (all_free(read_buff, save));
		read_buff[len_read] = '\0';
		str = ft_strjoin(save, read_buff);
		if (!str)
			return (all_free(read_buff, save));
		free(save);
		save = str;
	}
	free(read_buff);
	return (save);
}

char	*get_next_line(int fd)
{
	static char	*save;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	save = line_read(fd, save);
	if (!save)
		return (NULL);
	line = line_extracting(save);
	save = line_update(save);
	return (line);
}

// #include <fcntl.h>
// #include <stdio.h>

// int	main(void)
// {
// 	int		fd;
// 	char	*line;

// 	fd = open("test.txt", O_RDONLY);
// 	if (fd < 0)
// 	{
// 		perror("Error fichier");
// 		return (1);
// 	}
// 	while ((line = get_next_line(fd)) != NULL)
// 	{
// 		printf("%s", line);
// 		free(line);
// 	}
// 	close(fd);
// 	return (0);
// }
// #include <stdio.h>

// int    main(int argc, char *av[])
// {
//     int        fd;
//     char    *line;

//     if (argc != 2)
//         return (write(2, "no file\n", 8));
//     fd = open(av[1], O_RDONLY);
//     if (fd == -1)
//     {
//         write(2, "Cannot read file.\n", 18);
//         return (1);
//     }
//     line = get_next_line(fd);
//     while (line != NULL)
//     {
//         printf("%s", line);
//         free(line);
//         line = get_next_line(fd);
//     }
//     close(fd);
//     return (0);
// }

/*test pour stdin*/
// int    main(void)
// {
//     int        fd = 0;
//     char    *line;

//     line = get_next_line(fd);
//     while (line != NULL)
//     {
//         printf("GNL : %s", line);
//         free(line);
//         line = get_next_line(fd);
//     }
//     return (0);
// }

// //	echo "Bonjour\nVoici un test\nTroisième ligne" > test.txt
