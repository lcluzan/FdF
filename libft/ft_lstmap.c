/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcluzan <lcluzan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 14:32:32 by nouillebobb       #+#    #+#             */
/*   Updated: 2024/06/05 10:26:02 by lcluzan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*start;
	t_list	*current;

	if (!lst || !f || !del)
		return (NULL);
	start = NULL;
	while (lst)
	{
		current = ft_lstnew(lst ->content);
		if (!current)
			return (ft_lstclear(&start, del), NULL);
		current->content = (f(current ->content));
		ft_lstadd_back(&start, current);
		lst = lst->next;
	}
	return (start);
}
