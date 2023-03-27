#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*pt;

	if (nmemb == SIZE_MAX || size == SIZE_MAX)
		return (0);
	pt = malloc(nmemb * size);
	if (!pt)
		return (0);
	ft_bzero(pt, nmemb * size);
	return (pt);
}
