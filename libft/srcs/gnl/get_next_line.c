/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmechaly <gmechaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 17:09:22 by gmechaly          #+#    #+#             */
/*   Updated: 2025/07/28 23:42:46 by gmechaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	clean_line(char *line)
{
	int	i;

	i = 0;
	if (line[0] == '\0')
		return ;
	while (line[i] != '\n' && line[i])
		i++;
	if (line[i] == '\n')
		i++;
	line[i] = '\0';
}

void	load_memory(char *memory, char *line)
{
	int		i;

	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	if (line[i] == '\n')
		i++;
	ft_strcpy_gnl(memory, &line[i]);
	clean_line(line);
}

char	*readline(int fd, char *line)
{
	int		bytes_read;
	char	buf[BUFFER_SIZE + 1];

	bytes_read = 1;
	while (bytes_read > 0 && !ft_strchr_gnl(line, '\n'))
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			line [0] = '\0';
			break ;
		}
		buf[bytes_read] = '\0';
		if (bytes_read == 0)
			break ;
		if (bytes_read > 0)
		{
			line = ft_strjoin_gnl(line, buf);
			if (line == NULL)
				return (NULL);
		}
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	memory[BUFFER_SIZE + 1];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
	{
		memory[0] = '\0';
		return (NULL);
	}
	line = malloc(sizeof(char) * (ft_strlen_gnl(memory) + 1));
	if (line == NULL)
		return (free(line), NULL);
	line[0] = '\0';
	ft_strcpy_gnl(line, memory);
	line = readline(fd, line);
	if (line == NULL)
		return (NULL);
	if (ft_strchr_gnl(line, '\n'))
		load_memory(memory, line);
	else
	{
		memory[0] = '\0';
		if (line[0] == '\0')
			return (free(line), NULL);
	}
	return (line);
}

/*int	main(int argc, char **argv)
{
	int		fd;
	char	*c;

	(void) argc;
	fd = open(argv[1], O_RDONLY);
	c = get_next_line(fd);
	while (c != NULL)
	{
		printf("%s", c);
		free(c);
		c = get_next_line(fd);
	}
	return (0);
}

int	main(void)
{
	char *line;
	char *name = "tests/read_error.txt";
	int fd = open(name, O_RDONLY);

	line = get_next_line(fd);
	printf("%s\n", line);
	free(line);
	line = get_next_line(fd);
	printf("%s\n", line);
	free(line);
	line = get_next_line(10);
	printf("%s\n", line);
	free(line);
	close(fd);
	fd = open(name, O_RDONLY);
	line = get_next_line(fd);
	printf("%s\n", line);
	free(line);
	return (0);
}
*/