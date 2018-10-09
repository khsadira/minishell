/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_manage_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 15:39:33 by khsadira          #+#    #+#             */
/*   Updated: 2018/10/01 15:40:15 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static	char	*ft_return_arg(char *str)
{
	char	*arg;
	int		i;

	arg = NULL;
	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	i++;
	arg = ft_strsub(str, i, ft_strlen(str) - i);
	return (arg);
}

static	char	*ft_return_name(char *str)
{
	char	*name;
	int		j;

	name = NULL;
	j = 0;
	while (str[j] && str[j] != '=')
		j++;
	name = ft_strsub(str, 0, j);
	return (name);
}

char			*ft_search_env(char *str, t_env *env)
{
	while (env)
	{
		if (ft_strequ(env->name, str))
			return (env->arg);
		env = env->next;
	}
	return (NULL);
}

static char		*ft_push_i(char *arg)
{
	int		stock;
	char	*tmp;

	tmp = NULL;
	stock = 0;
	stock = ft_atoi(arg);
	stock++;
	tmp = arg;
	arg = ft_itoa(stock);
	free(tmp);
	return (arg);
}

t_env			*ft_creat_env(char **env, t_env *l_env)
{
	char	*name;
	char	*arg;
	int		i;
	t_env	*new_ele;

	name = NULL;
	arg = NULL;
	l_env = NULL;
	i = 0;
	new_ele = NULL;
	while (env[i])
	{
		name = ft_return_name(env[i]);
		arg = ft_return_arg(env[i]);
		if (ft_strequ(name, "SHLVL"))
			arg = ft_push_i(arg);
		new_ele = ft_newenv(name, arg);
		l_env = ft_addenv(l_env, new_ele);
		i++;
	}
	return (l_env);
}
