#include "libft.h"

int	ft_toupper(int a)
{
	if (a > 96 && a < 123)
		return (a - 32);
	return (a);
}
