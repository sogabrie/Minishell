#include "libft.h"

void	*ft_memset(void *a, int c, size_t len)
{
	while (0 < len)
	{
		--len;
		((unsigned char *)a)[len] = c;
	}
	return (a);
}
