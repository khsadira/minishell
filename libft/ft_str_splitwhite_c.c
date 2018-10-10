/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_splitwhite_c.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 14:29:26 by khsadira          #+#    #+#             */
/*   Updated: 2018/10/10 15:13:36 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_str_splitwhite_c(char *str)
{
	int		i;
	int		j;
	char	*ret;
	char	*join;

	j = 0;
	ret = NULL;
	join = NULL;
	i = 0;
	while (str[i])
	{
		if (!(str[i] < 33 || str[i] > 126) ||
			str[i] == '\t' || str[i] == ' ')
		{
			if (str[i] == '\t' || str[i] == ' ')
			{
				ft_putendl("ici");
				join = ft_strdup(" ");
			}
			else
				join = ft_strsub(str, i, 1);
			ret = ft_strfjoin(&ret, join);
			ft_strdel(&join);
		}
		i++;
	}
	ft_strdel(&str);
	return (str);
}
