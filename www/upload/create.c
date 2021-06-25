/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blorin <blorin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 16:27:36 by blorin            #+#    #+#             */
/*   Updated: 2020/12/15 16:27:42 by blorin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd		*create_cmd(t_env *env)
{
	t_cmd *new;
	t_cmd *tmp;

	if (env->cmd == NULL)
	{
		if (!(new = init_cmd()))
			return (0);
		env->cmd = new;
	}
	else
	{
		if (!(new = init_cmd()))
			return (0);
		tmp = env->cmd;
		while (tmp->next)
		{
			tmp = tmp->next;
		}
		tmp->next = new;
		new->prev = tmp;
		new->next = NULL;
	}
	return (new);
}

t_envir		*create_envir(t_env *env)
{
	t_envir *new;
	t_envir *tmp;

	if (env->envir == NULL)
	{
		if (!(new = init_envir()))
			return (0);
		env->envir = new;
	}
	else
	{
		if (!(new = init_envir()))
			return (0);
		tmp = env->envir;
		while (tmp->next)
		{
			tmp = tmp->next;
		}
		tmp->next = new;
		new->prev = tmp;
		new->next = NULL;
	}
	return (new);
}

t_export	*create_export(t_env *env)
{
	t_export *new;
	t_export *tmp;

	if (env->export == NULL)
	{
		if (!(new = init_export()))
			return (0);
		env->export = new;
	}
	else
	{
		if (!(new = init_export()))
			return (0);
		tmp = env->export;
		while (tmp->next)
		{
			tmp = tmp->next;
		}
		tmp->next = new;
		new->prev = tmp;
		new->next = NULL;
	}
	return (new);
}

