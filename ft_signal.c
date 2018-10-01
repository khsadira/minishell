/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/10 14:13:02 by khsadira          #+#    #+#             */
/*   Updated: 2018/10/01 15:38:25 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static void	sig_handler(int signo)
{
	if (signo == SIGINT)
		return ;
}

void		ft_signal(void)
{
	if (signal(SIGINT, sig_handler) == SIG_ERR)
		return ;
}
