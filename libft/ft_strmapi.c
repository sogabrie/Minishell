#include "libft.h"

char	*ft_strmapi(char const *s, char (f)(unsigned int, char))
{
	unsigned int	i;
	char			*mas;

	i = 0;
	if (!s || !f)
		return (0);
	mas = ft_strdup(s);
	if (!mas)
		return (0);
	while (mas[i])
	{
		mas[i] = f(i, mas[i]);
		++i;
	}
	return (mas);
}
