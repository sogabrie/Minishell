#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	l;
	char	*ptr;

	l = ft_strlen(s) + 1;
	ptr = (char *)malloc(l);
	if (!ptr)
		return (0);
	ft_strlcpy(ptr, s, l);
	return (ptr);
}
