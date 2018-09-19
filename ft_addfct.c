/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_addfct.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 12:29:31 by khsadira          #+#    #+#             */
/*   Updated: 2018/09/19 12:31:27 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

char	*ft_creat_path(char *path, char *cmd)
{
	char	*ret;

	ret = NULL;
	ret = ft_strjoin(path, "/");
	ret = ft_strfjoin(&ret, cmd);
	return (ret);
}

int		ft_acces(char *cmd, char *path)
{
	if (!ft_strequ(cmd, ".") &&
		!ft_strequ(cmd, "..") &&
		access(path, R_OK || X_OK) == 0)
		return (1);
	return (0);
}
