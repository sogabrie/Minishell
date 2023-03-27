#include "libft.h"

int	ft_isdigit(int a )
{
	if (a > 47 && a < 58)
		return (1);
	else
		return (0);
}
