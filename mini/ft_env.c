/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomatoe <atomatoe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 16:26:30 by atomatoe          #+#    #+#             */
/*   Updated: 2020/10/22 11:12:57 by atomatoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_parse_env(t_data *all)
{
	int i;

	i = 0;
	while(all->env[i])
	{
		if(ft_strncmp(all->env[i], "PWD=", 4) == 0)
        {
            all->env_dir = ft_strdup(all->env[i]);
            all->env_dir_i = i;
        }
		if(ft_strncmp(all->env[i], "HOME=", 5) == 0)
            all->env_home_dir = i;
        if(ft_strncmp(all->env[i], "OLDPWD=", 7) == 0)
            all->env_old_dir_i = i;
		if(ft_strncmp(all->env[i], "PATH=", 5) == 0)
            all->env_path_i = i;
		i++;
	}
    all->last_env = i;
}

int ft_creat_env(t_data *all, char **env)
{
	int i;
	int j;

	j = 0;
	i = 0;
	while(env[i])
		i++;
	if(!(all->env = (char **)malloc(sizeof(char*) * (i + 1))))
		return (-1);
	while(j != i)
	{
		all->env[j] = ft_strdup(env[j]);
		j++;
	}
	all->env[j] = NULL;
    ft_parse_env(all);
	return (0);
}