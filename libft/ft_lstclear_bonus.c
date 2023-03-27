#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*de;

	if (!del || !lst || !*lst)
		return ;
	while (*lst)
	{
		de = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = de;
	}
}
