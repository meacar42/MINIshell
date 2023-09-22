/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beyildir <beyildir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 15:33:57 by meacar            #+#    #+#             */
/*   Updated: 2023/07/18 20:16:17 by beyildir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_process(void)
{
	t_process	*tmp;
	t_process	*process;

	process = g_bm.process;
	if (!process)
		return ;
	while (process)
	{
		free_array(process->execute);
		free_array(process->redirects);
		tmp = process;
		process = process->next;
		free(tmp);
	}
}

void	free_chain(void)
{
	t_chain		*tmp;
	t_chain		*chain;

	chain = g_bm.chain;
	while (chain)
	{
		free(chain->str);
		chain = chain->next;
	}
	chain = g_bm.chain;
	while (chain)
	{
		tmp = chain;
		chain = chain->next;
		free(tmp);
	}
}

void	free_all(void)
{
	free_chain();
	free_process();
}
