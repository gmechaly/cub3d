/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmechaly <gmechaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 18:30:44 by rdalal            #+#    #+#             */
/*   Updated: 2025/07/28 21:45:18 by gmechaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	remove_trailing_newline(char *line)
{
	size_t	len;

	len = ft_strlen(line);
	while (len > 0 && (line[len - 1] == '\n' || \
		line[len - 1] == '\t' || line[len - 1] == '\r'))
	{
		line[len - 1] = '\0';
		len--;
	}
}

int	parse_texture_line(char *line, t_map *map)
{
	char	**tokens;
	char	*clean_path;
	int		result;

	clean_path = NULL;
	if (!line || !map)
		return (-1);
	line = ft_strtrim(line, " \t\n\r");
	tokens = ft_split(line, ' ');
	free(line);
	if (!tokens || !tokens[0] || !tokens[1])
		return (ft_free_split(tokens), -1);
	clean_path = ft_strtrim(tokens[1], " \t\n\r");
	if (!clean_path || clean_path[0] == '\0')
		return (ft_free_split(tokens), free (clean_path), -1);
	result = dup_check(map, tokens[0], clean_path);
	free(clean_path);
	ft_free_split(tokens);
	if (result != 0)
		printf("Error: Invalid texture line\n");
	return (result);
}
