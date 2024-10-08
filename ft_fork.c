/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/10 14:04:26 by khsadira          #+#    #+#             */
/*   Updated: 2018/10/01 15:48:02 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static int		ft_fork(char *path, char **arg, char **env)
{
	pid_t	pid;

	pid = fork();
	signal(SIGINT, ft_sig_handler);
	if (pid == 0)
	{
		execve(path, arg, env);
		return (0);
	}
	else if (pid < 0)
	{
		ft_putendl("Fork failed to create a new process.");
		return (-1);
	}
	wait(&pid);
	return (1);
}

void			ft_exec(t_lst *list, char **env)
{
	int		pid_value;

	pid_value = ft_fork(list->path, list->arg, env);
	if (pid_value != 0 && pid_value != -1 && pid_value != -2)
		list->value = pid_value;
	pid_value = 0;
}
