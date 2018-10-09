#include "ft_minishell.h"

int		ft_is_term(void)
{
	struct stat	stbuf;
	if (fstat(STDIN_FILENO, &stbuf) < 0)
		return (0);
	else
		return (S_ISCHR(stbuf.st_mode));
}
