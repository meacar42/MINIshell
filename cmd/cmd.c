/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beyildir <beyildir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 15:33:30 by meacar            #+#    #+#             */
/*   Updated: 2023/07/19 16:51:47 by beyildir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	start_builtin(t_process	*process)
{
	int	in;
	int	out;

	in = dup(0);
	out = dup(1);
	get_all_inputs(process);
	set_all_outputs(process);
	run_builtin(process->execute);
	dup2(in, 0);
	dup2(out, 1);
	close(in);
	close(out);
}

void	pause_cmd(void)
{
	t_process	*process;

	process = g_bm.process;
	close_fd_all();
	while (process)
	{
		if (process->pid != -1)
		{
			waitpid(process->pid, &g_bm.errno, 0);
			g_bm.errno = WEXITSTATUS(g_bm.errno);
		}
		process = process->next;
	}
}

void	start_cmd(void)
{
	t_process	*process;

	process = g_bm.process;
	if (!process)
		return ;
	fill_all_heredoc();
	if (g_bm.fail)
		return (close_fd_all());
	if (is_builtin(*process->execute) && g_bm.process_count == 1)
	{
		start_builtin(process);
		process = process->next;
	}
	while (process)
	{
		run_cmd(process);
		process = process->next;
	}
	pause_cmd();
}
