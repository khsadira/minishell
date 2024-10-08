/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_to_tab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 15:40:28 by khsadira          #+#    #+#             */
/*   Updated: 2018/10/02 13:36:34 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static int	ft_env_len(t_env *env)
{
	int	len;

	len = 0;
	while (env)
	{
		len++;
		env = env->next;
	}
	return (len);
}

static char	*ft_to_env(char *name, char *arg)
{
	char	*ret;
	char	*tmp;

	ret = ft_strdup(name);
	tmp = ft_strdup(arg);
	ret = ft_strfjoin(&ret, "=");
	ret = ft_strfjoin(&ret, arg);
	ft_strdel(&tmp);
	return (ret);
}

char		**ft_list_to_env(t_env *env)
{
	char	**ret;
	int		len;
	int		i;

	i = 0;
	if (!(len = ft_env_len(env)))
		return (NULL);
	if (!(ret = (char **)malloc(sizeof(char *) * (len + 1))))
		return (NULL);
	ret[len] = NULL;
	len = 0;
	while (env)
	{
		ret[i] = ft_to_env(env->name, env->arg);
		i++;
		env = env->next;
	}
	return (ret);
}
