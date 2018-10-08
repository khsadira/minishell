/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 14:19:27 by khsadira          #+#    #+#             */
/*   Updated: 2018/10/08 14:44:32 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	ft_no_such_file_or_dir(char *name, char *arg)
{
	ft_putstr_fd(name, 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd(": no such file or directory", 2);
}

void	ft_not_dir(char *name, char *arg)
{
	ft_putstr_fd(name, 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd(": not a directory", 2);
}

void	ft_permission_denied(char *name, char *arg)
{
	ft_putstr_fd(name, 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd(": permission denied", 2);
}
