/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beyildir <beyildir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 15:35:23 by meacar            #+#    #+#             */
/*   Updated: 2023/07/19 21:00:12 by beyildir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_data	g_bm;

void	commit_an_offense(char **env)
{
	g_bm.errno = 0;
	g_bm.paths = NULL;
	g_bm.parent_pid = getpid();
	set_env(env);
	g_bm.user = get_env("USER");
	set_paths();
}

void	start(char *input)
{
	if (!*input)
		return ;
	g_bm.chain = NULL;
	g_bm.process = NULL;
	g_bm.process_count = 0;
	listing(input);
	if (!listing_process())
		return ;
	start_cmd();
	free_process();
}

char	*prompt(void)
{
	char	*str;
	char	*color;

	str = ft_strjoin(g_bm.user, " minishell % ");
	color = ft_strjoin(YELLOW, str);
	free (str);
	return (color);
}

int	main(int ac, char **av, char **env)
{
	char	*input;
	char	*prompter;

	commit_an_offense(env);
	prompter = prompt();
	while (av && ac)
	{
		g_bm.fail = 0;
		signal(SIGINT, &handle_sigint);
		signal(SIGQUIT, SIG_IGN);
		input = readline(prompter);
		handle_exit(input);
		if (g_bm.fail)
		{
			free(input);
			input = malloc(1);
		}
		start(input);
		add_history(input);
		free(input);
	}
	free(prompter);
	exit(g_bm.errno);
}
