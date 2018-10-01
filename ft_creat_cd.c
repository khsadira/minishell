/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_creat_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/27 13:52:52 by khsadira          #+#    #+#             */
/*   Updated: 2018/10/01 15:47:32 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static char	*ft_lnk(char *path)
{
	char	link[255];
	int		rl;
	char	*ret;
	char	*tmp;

	rl = 0;
	if ((rl = readlink(path, link, 255)))
		link[rl] = '\0';
	tmp = ft_strdup(link);
	ret = ft_strdup("/");
	ret = ft_strfjoin(&ret, tmp);
	free(tmp);
	return (ret);
}

static void	ft_free_into_cd(char **s1, char **s2)
{
	free(*s1);
	free(*s2);
}

char		*ft_creat_cd_lnk(char *str, t_env *env)
{
	char		*ret;
	struct stat	buf;
	char		*path;

	path = NULL;
	if (str[0] != '/')
	{
		path = ft_strdup(ft_search_env("PWD", env));
		path = ft_strfjoin(&path, str);
	}
	else
		path = ft_strdup(str);
	if (lstat(path, &buf))
	{
		free(path);
		return (str);
	}
	if (!S_ISLNK(buf.st_mode))
	{
		free(path);
		return (str);
	}
	ret = ft_lnk(path);
	ft_free_into_cd(&str, &path);
	return (ret);
}
