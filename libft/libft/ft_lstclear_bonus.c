/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:17:38 by yzheng            #+#    #+#             */
/*   Updated: 2024/11/12 13:49:02 by jingwu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;
	t_list	*next_node;

	if (lst == NULL || *lst == NULL || del == NULL)
		return ;
	temp = *lst;
	while (temp)
	{
		next_node = temp->next;
		del(temp->content);
		free(temp);
		temp = next_node;
	}
	*lst = NULL;
}
