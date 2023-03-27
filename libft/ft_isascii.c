#include "libft.h"

int	ft_isascii(int a )
{
	if (a > -1 && a < 128)
		return (1);
	else
		return (0);
}
