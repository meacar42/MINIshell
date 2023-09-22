/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beyildir <beyildir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 15:35:30 by meacar            #+#    #+#             */
/*   Updated: 2023/07/18 20:16:17 by beyildir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_env(char *str)
{
	int		i;
	int		len;
	char	*curr;

	curr = ft_strjoin(str, "=");
	i = -1;
	len = ft_strlen(curr);
	while (g_bm.env[++i])
	{
		if (!ft_strncmp(g_bm.env[i], curr, len))
		{
			free(curr);
			return (ft_strdup(&g_bm.env[i][len]));
		}
	}
	free (curr);
	return (ft_calloc(sizeof(char *), 1));
}
