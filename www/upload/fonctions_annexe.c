/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonctions_annexe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blorin <blorin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 18:15:58 by blorin            #+#    #+#             */
/*   Updated: 2021/01/10 14:54:25 by blorin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_strcmp(char *str1, char *str2)
{
	int i;

	i = 0;
	if (str1 == NULL || str2 == NULL)
		return (-1);
	if (ft_strlen(str1) != ft_strlen(str2))
		return (-1);
	while (str1[i])
	{
		if (str1[i] != str2[i])
			return (-1);
		i++;
	}
	return (0);
}

int		pass_hook(char *str, int i)
{
	if (str[i] == '\'')
	{
		i++;
		while (str[i] && str[i] != '\'')
			i++;
		if (str[i] == '\'')
			i++;
	}
	else if (str[i] == '"')
	{
		i++;
		while (str[i] && str[i] != '"')
			i++;
		if (str[i] == '"')
			i++;
	}
	return (i);
}

void	count_len(t_cmd *cmd, int i)
{
	int k;
	int tmp;

	i = 0;
	tmp = 0;
	k = 0;
	while (cmd->line[i])
	{
		i = pass_hook(cmd->line, i);
		if (cmd->line[i] == '>' && (cmd->out_len += 1))
		{
			k = count_len2(cmd->line, i);
			tmp = tmp + k;
			i = i + k - 1;
		}
		else if (cmd->line[i] == '<' && (cmd->in_len += 1))
		{
			k = count_len2(cmd->line, i);
			tmp = tmp + k;
			i = i + k - 1;
		}
		if (cmd->line[i] != '\'' && cmd->line[i] != '"')
			i++;
	}
	cmd->len = i - tmp;
}

char	*replace_dollars(char *new)
{
	int a;

	a = 0;
	while (new[a])
	{
		if (new[a] == '"')
			new[a] = '\b';
		else if (new[a] == '\'')
			new[a] = '\e';
		a++;
	}
	return (new);
}

char	**remake(char **tab)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (tab[i])
	{
		while (tab[i][j])
		{
			if (tab[i][j] == '\a')
				tab[i][j] = ' ';
			j++;
		}
		j = 0;
		i++;
	}
	return (tab);
}

