/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarry <skarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 15:47:44 by skarry            #+#    #+#             */
/*   Updated: 2020/10/17 17:28:57 by skarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*re_malloc(char c, char *w)
{
	char	*v;
	int		i;

	if (!w)
	{
		v = (char *)malloc(2);
		v[0] = c;
		v[1] = '\0';
		return (v);
	}
	v = (char *)malloc(ft_strlen(w) + 1);
	i = -1;
	while (w[++i])
		v[i] = w[i];
	v[i++] = c;
	v[i] = w[i];
	free (w);
	return (v);
}

char	*get_word(char **line)
{
	char	*w;
	int		i;

	i = 0;
	w = NULL;
	while ((*line)[i] == ' ')
		i++;
	while (((*line)[i] != ' ' && (*line)[i]) || (!w && (*line)[i]))
	{
		if ((*line)[i] == '\\')
		{
			w = re_malloc((*line)[i + 1], w);
			i += 2;
		}
		if ((*line)[i] == '\'')
		{
			while ((*line)[i++] && (*line)[i] != '\'')
				w = re_malloc((*line)[i], w);
			if ((*line)[i])
				i++;
		}
		if ((*line)[i] == '\"')
		{
			while ((*line)[i++] && (*line)[i] != '\"')
			{
				if ((*line)[i] == '\\')
				{
					w = re_malloc((*line)[i + 1], w);
					i += 2;
				}
				else
					w = re_malloc((*line)[i], w);
			}
			if ((*line)[i])
				i++;
		}
		while ((*line)[i] && (*line)[i] != ' ' && (*line)[i] != '\\' && (*line)[i] != '\'' && (*line)[i] != '\"')
		{
			w = re_malloc((*line)[i], w);
			i++;
		}
	}
	*line = *line + i;
	return (w);
}

t_list	*line_to_lst(char *line)
{
	t_list	*i_map;
	t_list	*z_map;
	char	*w;

	z_map = NULL;
	while ((w = get_word(&line)))
	{
		i_map = ft_lstnew(w);
		ft_lstadd_back(&z_map, i_map);
	}
	return (z_map);
}

char		**line_to_mas(char *line)
{
	char	**map;
	t_list	*z_map;
	int		size;
	int		i;

	z_map = line_to_lst(line);
	size = ft_lstsize(z_map);
	if (!(map = (char**)malloc(sizeof(char*) * (size + 1))))
		return (0);
	map[size] = NULL;
	i = 0;
	while (size != i)
	{
		map[i] = z_map->content;
		i++;
		z_map = z_map->next;
	}
	return (map);
}
