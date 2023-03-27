#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*nels;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	nels = ft_lstlast(*lst);
	nels->next = new;
}
