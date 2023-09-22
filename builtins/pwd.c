/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beyildir <beyildir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 15:32:16 by meacar            #+#    #+#             */
/*   Updated: 2023/07/18 20:28:02 by beyildir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	builtin_pwd(void)
{
	char	*result;

	result = NULL;
	result = getcwd(result, sizeof(result));
	if (!result)
		perror("minishell ");
	else
		printf("%s\n", result);
	free(result);
	if (!(g_bm.parent_pid == getpid()))
		exit(g_bm.errno);
}
