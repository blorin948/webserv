/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blorin <blorin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 16:28:03 by blorin            #+#    #+#             */
/*   Updated: 2021/01/08 14:19:21 by blorin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_home(t_env *env)
{
	int		i;
	int		a;
	t_envir	*envir;

	i = 0;
	a = 0;
	envir = env->envir;
	while (envir)
	{
		if (ft_strcmp(envir->name, "HOME") == 0)
			return (envir->content);
		envir = envir->next;
	}
	return (NULL);
}

int		echo_cmd(t_cmd *cmd)
{
	int i;

	i = 1;
	g_ret = 0;
	while (ft_strcmp(cmd->split[i], "-n") == 0)
		i++;
	while (cmd->split[i])
	{
		ft_putstr_fd(cmd->split[i++], 1);
		if (cmd->split[i])
			ft_putstr_fd(" ", 1);
	}
	if (ft_strcmp(cmd->split[1], "-n") == 0)
		return (1);
	write(1, "\n", 1);
	return (0);
}

int		cd_cmd(t_cmd *cmd, t_env *env)
{
	int i;

	i = 0;
	while (cmd->split[i])
		i++;
	if (i == 1)
	{
		if (chdir(find_home(env)) != 0)
		{
			ft_putstr_fd("home missing\n", 1);
			g_ret = 1;
		}
	}
	if (i > 2 && (g_ret = 1))
		ft_putstr_fd("to much arguments\n", 1);
	if (i == 2)
	{
		if (chdir(cmd->split[1]) != 0 && (g_ret = 1))
		{
			ft_putstr_fd(cmd->split[1], 1);
			ft_putstr_fd(" : No such file or directory\n", 1);
		}
	}
	return (0);
}

