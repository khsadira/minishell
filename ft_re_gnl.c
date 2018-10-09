#include "ft_minishell.h"

int	ft_regnl(char **str)
{
	int	ret;
	char	buff[2];
	int	i;
	int	count;

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
	return (ret);
}
