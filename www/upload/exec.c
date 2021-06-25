/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blorin <blorin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 19:44:36 by blorin            #+#    #+#             */
/*   Updated: 2021/01/10 14:24:29 by blorin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			exec4(t_cmd *cmd, t_exec *exec, t_env *env)
{
	pipe(exec->p);
	exec->built = is_builtin(cmd);
	if (exec->built == 0 && (g_sig = 1))
	{
		env->is_fork = 1;
		if ((exec->pid = fork()) == -1)
			return (0);
	}
	else
		env->is_fork = 0;
	return (1);
}

void		exec3(t_cmd *cmd, t_exec *exec, t_env *env)
{
	int status;

	status = 0;
	if (exec->built > 0)
	{
		if (cmd->out == 3)
			dup2(cmd->fd, 1);
		else if (cmd->next != NULL)
			dup2(exec->p[1], 1);
		find_builtin(cmd, env);
	}
	dup2(exec->cpy, 1);
	close(exec->cpy);
	waitpid(exec->pid, &status, WUNTRACED);
	if (env->is_fork == 1)
	{
		if (WIFEXITED(status))
			g_ret = WEXITSTATUS(status);
	}
	close(exec->p[1]);
	exec->fd_in = exec->p[0];
	exec->built = 0;
}

void		exec2(t_cmd *cmd, t_exec *exec, t_env *env)
{
	exec->cpy = dup(1);
	exec->i = 0;
	if (cmd->in == 3)
		dup2(cmd->fd_in, 0);
	else
		dup2(exec->fd_in, 0);
	if (cmd->out == 3)
		dup2(cmd->fd, 1);
	else if (cmd->next != NULL)
		dup2(exec->p[1], 1);
	close(exec->p[0]);
	execve(cmd->split[0], cmd->split, env->env_tab);
	create_path(env, cmd);
	while (cmd->newpath[exec->i])
		execve(cmd->newpath[exec->i++], cmd->split, env->env_tab);
	dup2(exec->cpy, 1);
	ft_printf("command not found : %s\n", cmd->split[0]);
	exit(127);
}

t_exec		*init_exec(void)
{
	t_exec *exec;

	if (!(exec = malloc(sizeof(t_exec))))
		return (NULL);
	exec->i = 0;
	exec->built = 0;
	exec->fd_in = 0;
	exec->pid = 0;
	exec->cpy = 0;
	return (exec);
}

int			exec(t_env *env)
{
	t_exec	*exec;
	t_cmd	*cmd;

	if (env->ex > 0)
		return (0);
	exec = init_exec();
	cmd = env->cmd;
	while (cmd)
	{
		if (exec4(cmd, exec, env) == 0)
			return (0);
		exec->cpy = dup(1);
		if (exec->pid == 0 && exec->built == 0)
			exec2(cmd, exec, env);
		else
			exec3(cmd, exec, env);
		cmd = cmd->next;
		g_sig = 0;
	}
	free(exec);
	return (0);
}

