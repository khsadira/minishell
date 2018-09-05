/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 10:20:32 by khsadira          #+#    #+#             */
/*   Updated: 2018/09/05 15:48:53 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int				nb_words(char const *str, char const c)
{
	int	i;
	int	nb;

	i = 0;
	nb = 1;
	while (str[i] && str[i] == ' ')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] == '"')
		{
			i++;
			while (str[i] && str[i] != '"')
				i++;
			i++;
		}
		else if (str[i] == '\'')
		{
			i++;
			while (str[i] && str[i] != '\'')
				i++;
			i++;
		}
		else if (str[i] == ' ')
		{
			nb++;
			while (str[i] && str[i] == ' ')
				i++;
		}
		else
			i++;
	}
	return (nb);
}

static char		*get_env(t_env *env, char *comp)
{
	char	*path;

	path = NULL;
	while (env)
	{
		if (ft_strequ(env->name, comp))
		{
			path = ft_strdup(env->arg);
			return (path);
		}
		env = env->next;
	}
	return (NULL);
}

static const char			*new_word(char const *str)
{
	char		*word;
	int			i;
	char		c;
	int			j;

	c = 0;
	i = 0;
	if (*str != ' ' || *str != '\'' || *str != '"')
		while (str[i] && ((*str != ' ' || *str != '\'' || *str != '"')))
			i++;
	else
	{
		c = *str;
		str++;
		while (str && *str != c)
			str++;
	}
	return (str);
}

static const char			*next_word(char const *str, char const c)
{
	while (*str && (*str == c))
	{
		str++;
		if (*str == c)
			return (str);
	}
	return (str);
}
/*
char				**ft_treat_line2(char const *str, char const c, t_env *env)
{
	char	**tab;
	char	*word;
	int		i;

	i = 0;
	if (!str)
		return (NULL);
	if (!(tab = (char **)malloc(sizeof(char *) * (nb_words(str, c) + 1))))
		return (NULL);
	while (*str)
	{
		str = next_word(str, c);
		printf("str = %s\n", str);
		if (*str)
		{
			word = new_word(str);
			printf("word = %s\n", word);
			tab[i++] = word;
			i++;
			str = str + ft_strlen(word);
		}
	}
	tab[i] = 0;
	return (tab);
}
*/
char				**ft_treat_line2(char const *str, char const c, t_env *env)
{
	char		**tab;
	char		*word;
	int		i;
	int		j;
	int		a;
	int		len;
	char		*path;
	char	*tmp;

	len = ft_strlen(str);
	a = 0;
	j = 0;
	i = 0;
	tab = NULL;
	if (str == NULL)
		return (NULL);
	if (!(tab = (char **)malloc(sizeof(char *) * (nb_words(str, c) + 1))))
		return (NULL);
	while (str[i])
	{
		if (str[i] && str[i] == '"')
		{
			j = i++;
			j++;
			while (str[i] && str[i] != '"')
				i++;
			tab[a++] = ft_strsub(str, j, i++ - j);
		}
		else if (str[i] && str[i] == '\'')
		{
			j = i++;
			j++;
			while (str[i] && str[i] != '\'')
				i++;
			tab[a++] = ft_strsub(str, j, i++ - j);
		}
		else if (str[i] && str[i - 1] && str[i - 1] == ' ' && str[i] == '~' && str[i + 1] && str[i + 1] == '/')
		{
			i += 2;
			tab[a++] = get_env(env, "HOME");
		}
		else if (str[i] == '#')
			while (str[i] && str[i] != ' ')
				i++;
		else if (str[i] == '$')
		{
			j = i;
			while (str[j] != ' ')
				j++;
			tab[a++] = get_env(env, (ft_strsub(str, i + 1, j - i)));
		}
		else if (str[i] && str[i] != c)
		{
			while (str[i] && str[i] == c)
				i++;
			j = i++;
			while (str[i] && str[i] != c)
				i++;
			if (j != i)
				tab[a++] = ft_strsub(str, j, i - j);
		}
		else
			i++;
	}
	tab[a] = 0;
	return (tab);
}
