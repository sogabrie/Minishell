#include "libft.h"

int	ft_tolower(int a)
{
	if (a > 64 && a < 91)
		return (a + 32);
	return (a);
}
