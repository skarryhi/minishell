/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarry <skarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 18:38:41 by skarry            #+#    #+#             */
/*   Updated: 2020/10/20 18:02:27 by skarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_commands	*create_one_lst(t_commands *lst, int t)
{
	t_commands	*new;

	new = (t_commands *)malloc(sizeof(t_commands));
	if (t == 1)
		lst->redir = new;
	if (t == 2)
		lst->pipe = new;
	if (t == 3)
		lst->next = new;
	return (new);
}

void		add_lst(char *line, t_commands *cmd, size_t point, size_t end_cmd)
{
	t_commands	*pipe;
	t_commands	*next;
	t_commands	*redir;
	t_commands	*new;

	pipe = cmd;
	next = cmd;
	redir = cmd;
	new = cmd;
	while (new)
	{
		new = NULL;
		if (line[point - 1] == '>' || line[point - 1] == '<')
		{
			new = create_one_lst(redir, 1);
			redir = new;
		}
		if (line[point - 1] == '|')
		{
			new = create_one_lst(pipe, 2);
			redir = new;
			pipe = new;
		}
		if (line[point - 1] == ';')
		{
			new = create_one_lst(next, 3);
			redir = new;
			next = new;
			pipe = new;
		}
		if (new)
			write_data(new, &point, &end_cmd, line);
	}
}