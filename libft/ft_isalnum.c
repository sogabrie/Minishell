#include "libft.h"

int	ft_isalnum(int a )
{
	if ((a > 64 && a < 91) || (a > 96 && a < 123) || (a > 47 && a < 58))
		return (1);
	else
		return (0);
}
