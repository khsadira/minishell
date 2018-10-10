/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_addfct.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 12:29:31 by khsadira          #+#    #+#             */
/*   Updated: 2018/10/10 09:36:30 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

char		*ft_creat_path(char *path, char *cmd)
{
	char	*ret;

	ret = NULL;
	ret = ft_strjoin(path, "/");
	ret = ft_strfjoin(&ret, cmd);
	return (ret);
}

int			ft_acces(char *cmd, char *path)
{
	if (!ft_strequ(cmd, ".") &&
		!ft_strequ(cmd, "..") &&
		access(path, R_OK || X_OK) == 0)
		return (1);
	return (0);
}

int			ft_is_term(void)
{
	struct stat	stbuf;

	if (fstat(STDIN_FILENO, &stbuf) < 0)
		return (0);
	else
		return (S_ISCHR(stbuf.st_mode));
}

void		ft_aff_prompt(void)
{
	char	*cwd;
	char	buff[4096 + 1];
	int		i;
	int		len;
	char	*tmp;

	tmp = NULL;
	if ((cwd = getcwd(buff, 4096)))
	{
		len = ft_strlen(cwd);
		i = len;
		while (i > 0 && cwd[i] != '/')
			i--;
		if (cwd[i] == '/' && ft_strlen(cwd) != 1)
			i++;
		tmp = ft_strsub(cwd, i, len - i);
	}
	ft_putstr("\033[0;31m");
	ft_putstr("<");
	ft_putstr(tmp);
	ft_putstr("> ");
	ft_putstr("\033[0m");
	free(tmp);
}

int			ft_regnl(char **str)
{
	int		ret;
	char	buff[2];
	int		i;
	int		count;

	buff[0] = 0;
	buff[1] = 0;
	count = 1;
	*str = NULL;
	i = 0;
	while ((ret = read(0, buff, 1)) && !ft_strequ(buff, "\n"))
	{
		buff[ret] = '\0';
		*str = ft_strfjoin(&(*str), buff);
	}
	if (!*str)
		*str = ft_strdup("");
	return (ret);
}
