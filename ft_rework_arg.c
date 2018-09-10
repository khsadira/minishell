/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rework_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/07 12:19:58 by khsadira          #+#    #+#             */
/*   Updated: 2018/09/10 11:52:31 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static char	*ft_push_arg_dol(char *arg, t_env *env)
{
	int		i;
	char	*tmp;

	i = 0;
	while (arg[i] && arg[i] != '/')
		i++;
	while (env)
	{
		if (ft_strnequ(env->name, arg + 1, i))
		{
			tmp = arg;
			arg = ft_strdup(env->arg);
			arg = ft_strfjoin(&arg, tmp + i);
			free(tmp);
			return (arg);
		}
		env = env->next;
	}
	free(arg);
	return (NULL);
}

static char	*ft_push_arg_tild(char *arg, t_env *env)
{
	int		i;
	char	*tmp;

	i = 0;
	while (arg[i] && arg[i] != '/')
		i++;
	if (arg[i - 1] != '/' && arg[i - 1] != '~')
		return (arg);
	while (env)
	{
		if (ft_strequ(env->name, "HOME"))
			break ;
		env = env->next;
	}
	if (env->arg)
	{
		tmp = arg;
		arg = ft_strdup(env->arg);
		arg = ft_strfjoin(&arg, tmp + i);
		free(tmp);
	}
	return (arg);
}

static char	**ft_rearg(char **arg, t_env *env)
{
	int		i;
	int		j;
	char	**tmp;

	j = ft_strdlen(arg) - 1;
	i = 0;
	while (arg[i])
	{
		if (ft_strnequ(arg[i], "$", 1))
		{
			if (!(arg[i] = ft_push_arg_dol(arg[i], env)))
			{
				arg[i] = arg[j];
				arg[j] = NULL;
			}
		}
		else if (ft_strnequ(arg[i], "~", 1))
			arg[i] = ft_push_arg_tild(arg[i], env);
		i++;
	}
	return (arg);
}

t_lst		*ft_rework_arg(t_lst *list, t_env *env)
{
	t_lst	*head;

	head = list;
	while (list)
	{
		list->arg = ft_rearg(list->arg, env);
		list = list->next;
	}
	return (head);
}
