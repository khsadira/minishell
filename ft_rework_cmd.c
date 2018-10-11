/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rework_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/10 12:48:47 by khsadira          #+#    #+#             */
/*   Updated: 2018/10/11 09:56:41 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static char	*ft_put_arg_tild(char *arg, int i, t_env *env)
{
	char	*home;
	int		j;
	char	*tmp;
	char	*tmp2;

	j = ft_strlen(arg);
	home = ft_search_env("HOME", env);
	tmp = ft_strsub(arg, 0, i);
	tmp2 = ft_strsub(arg, i + 1, j - (i + 1));
	tmp = ft_strfjoin(&tmp, home);
	tmp = ft_strfjoin(&tmp, tmp2);
	free(arg);
	free(tmp2);
	return (tmp);
}

static char	*ft_put_arg_dol(char *arg, int i, t_env *env)
{
	int		j;
	char	*tmp;
	char	*tmp2;
	char	*name;

	j = i;
	j++;
	while (arg[j] && ((arg[j] >= '0' && arg[j] <= '9') ||
						(arg[j] >= 'a' && arg[j] <= 'z') ||
						(arg[j] >= 'A' && arg[j] <= 'Z')))
		j++;
	tmp = ft_strsub(arg, 0, i);
	tmp2 = ft_strsub(arg, i + 1, j - (i + 1));
	name = ft_search_env(tmp2, env);
	tmp = ft_strfjoin(&tmp, name);
	tmp = ft_strfjoin(&tmp, arg + j);
	free(tmp2);
	free(arg);
	return (tmp);
}

static char	**ft_trimarg(char **str)
{
	int		i;
	char	*tmp;

	i = 0;
	while (str[i])
	{
		tmp = str[i];
		str[i] = ft_strtrim(str[i]);
		free(tmp);
		i++;
	}
	return (str);
}

char		**ft_rework_cmd(char **arg, t_env *env)
{
	int		i;
	int		j;

	i = 0;
	while (arg[i])
	{
		j = 0;
		while (arg[i][j])
		{
			if (arg[i][j] == '$')
				arg[i] = ft_put_arg_dol(arg[i], j, env);
			else if ((ft_strnequ(arg[i] + j, "~", 1) && (!arg[i][j + 1] ||
						arg[i][j + 1] == '/' || arg[i][j + 1] == ' ')
						&& (!arg[i][j - 1] || (arg[i][j - 1] == ' ' ||
											arg[i][j - 1] == '\t'))))
				arg[i] = ft_put_arg_tild(arg[i], j, env);
			j++;
		}
		i++;
	}
	arg = ft_trimarg(arg);
	return (arg);
}
