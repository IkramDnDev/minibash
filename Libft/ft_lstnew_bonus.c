/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idahhan <idahhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 18:28:50 by idahhan           #+#    #+#             */
/*   Updated: 2024/11/12 21:04:03 by idahhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new_noeud;

	new_noeud = (t_list *)malloc(sizeof(t_list));
	if (new_noeud == NULL)
		return (NULL);
	new_noeud -> content = content;
	new_noeud -> next = NULL;
	return (new_noeud);
}
