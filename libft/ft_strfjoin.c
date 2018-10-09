#include "libft.h"
#include <stdlib.h>

char			*ft_strfjoin(char **over, char *buff)
{
	int		over_s;
	int		buff_s;
	char	*tmp;

	over_s = 0;
	buff_s = 0;
	if (*over)
		over_s = ft_strlen(*over);
	if (buff)
		buff_s = ft_strlen(buff);
	if (!(tmp = (char*)malloc(sizeof(char) * (buff_s + over_s + 1))))
		return (NULL);
	ft_memcpy(tmp, *over, over_s);
	ft_memcpy(tmp + over_s, buff, buff_s);
	tmp[over_s + buff_s] = '\0';
	free(*over);
	return (tmp);
}

