/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beyildir <beyildir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 15:35:35 by meacar            #+#    #+#             */
/*   Updated: 2023/07/18 20:16:17 by beyildir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_paths(void)
{
	char	*path;

	if (g_bm.paths)
		free_array(g_bm.paths);
	path = get_env("PATH");
	if (!(*path))
		g_bm.paths = NULL;
	else
		g_bm.paths = ft_split(path, ':');
	free(path);
}
