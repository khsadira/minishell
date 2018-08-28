/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 10:20:32 by khsadira          #+#    #+#             */
/*   Updated: 2017/11/23 11:03:26 by khsadira         ###   ########.fr       */
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

char				**ft_treat_line2(char const *str, char const c)
{
	char		**tab;
	char		*word;
	int		i;
	int		j;
	int		a;
	int		len;

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
