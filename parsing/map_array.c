/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_array.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmechaly <gmechaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 17:56:05 by rdalal            #+#    #+#             */
/*   Updated: 2025/07/29 01:03:57 by gmechaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_list	*add_lines_check(int fd)
{
	char	*trimmed;
	char	*line;
	t_list	*lines;

	lines = NULL;
	line = get_next_line(fd);
	while (line)
	{
		if (valid_map(line))
		{
			trimmed = ft_strtrim(line, "\n");
			ft_lstadd_back(&lines, ft_lstnew(trimmed));
		}
		free(line);
		line = get_next_line(fd);
	}
	return (lines);
}

static void	free_list(t_list *lines)
{
	t_list	*temp;

	while (lines)
	{
		temp = lines->next;
		free(lines->content);
		free(lines);
		lines = temp;
	}
}

void	free_map_array(char **map)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

char	**create_map_array(int fd)
{
	t_list	*temp;
	char	**map;
	t_list	*lines;
	int		i;

	lines = add_lines_check(fd);
	if (!lines)
		return (NULL);
	map = malloc(sizeof(char *) * (ft_lstsize(lines) + 1));
	if (!map)
		return (free_list(lines), NULL);
	i = 0;
	while (lines)
	{
		map[i++] = lines->content;
		temp = lines->next;
		free(lines);
		lines = temp;
	}
	map[i] = NULL;
	return (map);
}
