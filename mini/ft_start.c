/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomatoe <atomatoe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 17:13:10 by atomatoe          #+#    #+#             */
/*   Updated: 2020/10/27 13:34:33 by atomatoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void		do_cmd(t_commands *cmd, t_data *all)
{
	int			fd[2];
	t_commands	*pip;
	t_commands	*redir;

	if (cmd->cmd)
	{
		pip = cmd;
		redir = cmd;
		if (pip->pipe)
		{
			pipe(fd);
			dup2(fd[1], 1);
		}
		ft_parse_env(all);
		redirects(redir);//дописать вывод ошибок
		if (ft_compare_str(cmd->cmd, "pwd") == 1)
			ft_give_pwd(cmd);
		else if (ft_compare_str(cmd->cmd, "env") == 1)
			ft_give_env(all);
		else if (ft_compare_str(cmd->cmd, "echo") == 1)
			ft_give_echo(all, cmd);
		else if (ft_compare_str(cmd->cmd, "export") == 1)
			ft_give_export(cmd, all);
		else if (ft_compare_str(cmd->cmd, "unset") == 1)
			ft_give_unset(cmd, all);
		else if (ft_compare_str(cmd->cmd, "cd") == 1)
			ft_give_cd(cmd, all);
		else if (ft_compare_str(cmd->cmd, "exit") == 1)
		{
			write(1, "exit\n", 5);
			exit(ft_atoi(all->error));
		}
		else if (cmd->dir_find == 1)
			ft_give_command(cmd, all);
		else
		{
			ft_putstr(cmd->cmd);
			write(1, ": command not found\n", 20);
			free(all->error);
			all->error = ft_strdup("127");
		}
		pipe_end(pip, all, fd[0], fd[1]);
	}
}

int			ft_start(t_commands *next, t_data *all)
{
	while (next)
	{
		if (!next->invalid)
			do_cmd(next, all);
		next = next->next;
		dup2(all->fd1, 1);
		dup2(all->fd0, 0);
	}
	return (0);
}
