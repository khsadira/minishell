#include "ft_minishell.h"

void	ft_aff_prompt(void)
{
	char	*cwd;
	char	buff[4096 + 1];
	int	i;
	int	len;
	char	*tmp;

	cwd = getcwd(buff, 4096);
	len = ft_strlen(cwd);
	i = len;
	while (i > 0 && cwd[i] != '/')
		i--;
	if (cwd[i] == '/')
		i++;
	tmp = ft_strsub(cwd, i, len - i);
	ft_putstr("\033[0;31m");
	ft_putstr("<");
	ft_putstr(tmp);
	ft_putstr("> ");
	ft_putstr("\033[0m");
	free(tmp);
}
