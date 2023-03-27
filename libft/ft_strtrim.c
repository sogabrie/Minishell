#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t		i;
	char const	*pt;

	pt = s1;
	if (!pt || !set)
		return (0);
	while (*pt && ft_strchr(set, *pt))
		++pt;
	i = ft_strlen(pt);
	--i;
	while (i && ft_strchr(set, pt[i]))
		--i;
	return (ft_substr(pt, 0, i + 1));
}
