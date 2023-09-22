/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beyildir <beyildir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 15:34:49 by meacar            #+#    #+#             */
/*   Updated: 2023/07/18 20:16:17 by beyildir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_chain	*new_list(char *str, enum e_ttype type)
{
	t_chain	*new_chain;

	new_chain = ft_calloc(sizeof(t_chain), 1);
	new_chain->type = type;
	new_chain->str = str;
	new_chain->prev = NULL;
	new_chain->next = NULL;
	return (new_chain);
}

int	add_list(t_chain **chain, t_chain *new_chain)
{
	t_chain	*curr;

	curr = *chain;
	if (!curr)
		*chain = new_chain;
	else
	{
		while (curr->next != NULL)
			curr = curr->next;
		curr->next = new_chain;
		new_chain->prev = curr;
	}
	return (ft_strlen(new_chain->str));
}

void	listing(char *input)
{
	while (*input)
	{
		if (!ft_strncmp(input, ">>", 2))
			input += add_list(&g_bm.chain, new_list(ft_strdup(">>"), \
			RED_APPEND));
		else if (!ft_strncmp(input, "<<", 2))
			input += add_list(&g_bm.chain, new_list(ft_strdup("<<"), \
			HERE_DOC));
		else if (!ft_strncmp(input, "|", 1))
			input += add_list(&g_bm.chain, new_list(ft_strdup("|"), \
			PIPE));
		else if (!ft_strncmp(input, "<", 1))
			input += add_list(&g_bm.chain, new_list(ft_strdup("<"), \
			RED_INPUT));
		else if (!ft_strncmp(input, ">", 1))
			input += add_list(&g_bm.chain, new_list(ft_strdup(">"), \
			RED_OUTPUT));
		else
			str_listing(&input);
	}
}
