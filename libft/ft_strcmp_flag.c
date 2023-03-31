#include "libft.h"

int	ft_strcmp_flag(char *str1, char *str2, int flag)
{
	size_t	i;

	i = 0;
	while (str1[i] != '\0' && str2[i] != '\0')
	{
		if (str1[i] - str2[i] != 0)
			return (1);
		i++;
	}
	if (flag == 1 && str1[i + 1] == '\0' && str2[i] == '\0')
		return (0);
	if (str1[i] == '\0' && str2[i] == '\0')
		return (0);
	return (1);
}
