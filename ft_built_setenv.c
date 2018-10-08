/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built_setenv.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/27 15:00:41 by khsadira          #+#    #+#             */
/*   Updated: 2018/10/08 15:26:35 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

t_env			*ft_setenv_char(char *name, t_env *env)
{
	t_env	*h_env;

	h_env = env;
	while (env)
	{
		if (ft_strequ(env->name, name) == 1)
		{
			if (env->arg)
				free(env->arg);
			env->arg = getcwd(NULL, 0);
			return (h_env);
		}
		env = env->next;
	}
	env = ft_newenv(ft_strdup(name), getcwd(NULL, 0));
	h_env = ft_addenv(h_env, env);
	return (h_env);
}

char			*ft_get_env(t_env *env, char *name)
{
	if (!name)
		return (NULL);
	while (env)
	{
		if (ft_strequ(env->name, name))
			return (env->arg);
		env = env->next;
	}
	return (NULL);
}

t_env			*ft_setenv_c(char *name, char *arg, t_env *env)
{
	t_env	*h_env;

	if (!arg)
		return (env);
	h_env = env;
	while (env)
	{
		if (ft_strequ(env->name, name) == 1)
		{
			ft_strdel(&env->arg);
			env->arg = arg;
			return (h_env);
		}
		env = env->next;
	}
	env = ft_newenv(name, arg);
	h_env = ft_addenv(h_env, env);
	return (h_env);
}

static t_env	*ft_setenv_nullarg(t_lst *list, t_env *env)
{
	t_env	*h_env;

	h_env = env;
	while (env)
	{
		if (ft_strequ(env->name, list->arg[1]))
		{
			free(env->arg);
			env->arg = NULL;
			return (h_env);
		}
		env = env->next;
	}
	env = ft_newenv(ft_strdup(list->arg[1]), NULL);
	h_env = ft_addenv(h_env, env);
	return (h_env);
}

t_env			*ft_setenv(t_lst *list, t_env *l_env)
{
	t_env	*h_env;

	h_env = l_env;
	if (!list->arg[1])
	{
		ft_printenv(h_env);
		return (h_env);
	}
	else if (ft_check_env_error(list))
		return (h_env);
	else if (!list->arg[2])
		return (ft_setenv_nullarg(list, l_env));
	while (l_env)
	{
		if (ft_strequ(l_env->name, list->arg[1]))
		{
			free(l_env->arg);
			l_env->arg = ft_strdup(list->arg[2]);
			return (h_env);
		}
		l_env = l_env->next;
	}
	l_env = ft_newenv(ft_strdup(list->arg[1]), ft_strdup(list->arg[2]));
	h_env = ft_addenv(h_env, l_env);
	return (h_env);
}
