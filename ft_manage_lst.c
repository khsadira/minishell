/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_manage_lst.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 15:38:42 by khsadira          #+#    #+#             */
/*   Updated: 2018/10/01 15:39:00 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

t_lst	*ft_addlist(t_lst *list, t_lst *new_ele)
{
	t_lst	*head;

	if (new_ele == NULL)
		return (list);
	if (list == NULL)
		return (new_ele);
	head = list;
	while (list->next)
		list = list->next;
	list->next = new_ele;
	return (head);
}

t_lst	*ft_newele(char *name)
{
	t_lst	*list;

	if (!(list = (t_lst *)malloc(sizeof(t_lst))))
		return (NULL);
	list->path = name;
	list->cmd = NULL;
	list->value = 0;
	list->arg = NULL;
	list->next = NULL;
	return (list);
}

t_env	*ft_addenv(t_env *list, t_env *new_ele)
{
	t_env	*head;

	if (new_ele == NULL)
		return (list);
	if (list == NULL)
		return (new_ele);
	head = list;
	while (list->next)
		list = list->next;
	list->next = new_ele;
	return (head);
}

t_env	*ft_newenv(char *name, char *arg)
{
	t_env	*list;

	if (!(list = (t_env *)malloc(sizeof(t_env))))
		return (NULL);
	list->name = name;
	list->arg = arg;
	list->next = NULL;
	return (list);
}
