/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoliner <dmoliner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 13:59:01 by dmoliner          #+#    #+#             */
/*   Updated: 2022/09/28 13:59:01 by dmoliner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *nw)
{
	t_list	*temp;

	if (!lst || !nw)
		return ;
	else if (!(*lst))
	{
		*lst = nw;
		return ;
	}
	temp = ft_lstlast(*lst);
	temp->next = &*nw;
}
