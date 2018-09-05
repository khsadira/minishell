/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 10:20:32 by khsadira          #+#    #+#             */
/*   Updated: 2018/09/05 17:24:00 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static const char	*next_word(const char *str, char c)
{
	while (*str && *str == c)
	{
		if (*str == '"')
		{
			str++;
			while (*str && *str != '"')
				str++;
		}
		if (*str == '\'')
		{
			str++;
			while (*str && *str != '\'')
				str++;
		}
		str++;
	}
	return (str);
}

static const char	*next_word_0(const char *str, char c)
{
	while (*str && *str != c)
	{
		if (*str == '"')
		{
			str++;
			while (*str && *str != '"')
				str++;
		}
		if (*str == '\'')
		{
			str++;
			while (*str && *str != '\'')
				str++;
		}
		str++;
	}
	return (str);
}

static int			nb_words(const char *str, char c)
{
	int	i;

	i = 0;
	while (*str)
	{
		str = next_word(str, c);
		if (*str)
		{
			i++;
			str = next_word_0(str, c);
		}
	}
	return (i);
}

static char			**cleantable(char **tab, int i)
{
	int	a;

	a = 0;
	while (a < i)
		free(tab[a]);
	free(tab);
	return (NULL);
}

char				**ft_treat_line(char const *str, char const c)
{
	char		**tab;
	const char	*word;
	int			i;

	i = 0;
	if (str == NULL)
		return (NULL);
	if (!(tab = (char **)malloc(sizeof(char *) * (nb_words(str, c) + 1))))
		return (NULL);
	while (*str)
	{
		str = next_word(str, c);
		if (*str)
		{
			word = next_word_0(str, c);
			tab[i] = ft_strsub(str, 0, word - str);
			if (tab[i] == NULL)
				return (cleantable(tab, i));
			i++;
			str = word;
		}
	}
	tab[i] = 0;
	return (tab);
}
