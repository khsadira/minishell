#include "ft_minishell.h"

static char	*ask_quote(char *str, int i, char c)
{
	char	*line;

	line = NULL;
	while (1)
	{
		i = 0;
		if (c == '"')
			ft_putstr("dquote> ");
		else if (c == '\'')
			ft_putstr("quote> ");
		if (get_next_line(0, &line) > 0)
		{
			str = ft_strfjoin(&str, "\n");
			str = ft_strfjoin(&str, line);
			while (line[i])
			{
				if (line[i] == c)
				{
					free(line);
					return (str);
				}
				i++;
			}
			free(line);
		}
	}
}

char	*ft_ask_quote(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"')
		{
			i++;
			while (str[i] && str[i] != '"')
				i++;
			i++;
			if (!str[i] && str[i - 1] != '"')
			{
				str = ask_quote(str, i, '"');
				i = 0;
			}
		}
		else if (str[i] == '\'')
		{
			i++;
			while (str[i] && str[i] != '\'')
				i++;
			i++;
			if (!str[i] && str[i - 1] != '\'')
			{
				str = ask_quote(str, i, '\'');
				i = 0;
			}
		}
		else
			i++;
	}
	return (str);
}
