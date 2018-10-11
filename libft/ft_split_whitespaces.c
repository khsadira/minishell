/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_whitespaces.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/16 17:46:54 by khsadira          #+#    #+#             */
/*   Updated: 2018/10/11 09:54:24 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

int			nb_word(char *str)
{
	int		nb;
	int		i;

	i = 0;
	nb = 0;
	while (str[i])
	{
		while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t')
			i++;
		if (str[i] == '\0')
			return (nb);
		if (str[i] != ' ' && (str[i + 1] == ' ' || str[i + 1] == '\0'
					|| str[i + 1] == '\t' || str[i + 1] == '\n'))
			nb++;
		i++;
	}
	return (nb);
}

int			ft_strlen_w(char *str)
{
	int		i;

	i = 0;
	while ((str[i] == '\t' || str[i] == '\n' || str[i] == ' ')
			&& str[i] != '\0')
		str++;
	while (!(str[i] == '\t' || str[i] == '\n' || str[i] == ' ')
			&& str[i] != '\0')
		i++;
	return (i);
}

char		**ft_split_whitespaces(char *str)
{
	int		size;
	int		a;
	int		i;
	char	**words;
	char	*word;

	i = 0;
	a = 0;
	size = nb_word(str);
	words = (char**)malloc(sizeof(char*) * (size + 1));
	while (a < size)
	{
		word = (char*)malloc(sizeof(char) * (ft_strlen_w(str) + 1));
		while ((str[0] == '\t' || str[0] == '\n' || str[0] == ' ')
				&& str[0] != '\0')
			str++;
		while (!(str[0] == '\t' || str[0] == '\n' || str[0] == ' ')
				&& str[0] != '\0')
			word[i++] = *str++;
		word[i] = '\0';
		words[a++] = word;
		i = 0;
	}
	words[size] = 0;
	return (words);
}
