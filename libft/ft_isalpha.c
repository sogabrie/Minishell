#include "libft.h"

int	ft_isalpha(int a )
{
	if ((a > 64 && a < 91) || (a > 96 && a < 123))
		return (1);
	else
		return (0);
}
