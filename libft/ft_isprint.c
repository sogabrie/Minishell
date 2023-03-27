#include "libft.h"

int	ft_isprint(int a )
{
	if (a > 31 && a < 127)
		return (1);
	else
		return (0);
}
