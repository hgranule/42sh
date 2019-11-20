/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sys_sigs_dfl_init.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgranule <hgranule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 07:55:01 by hgranule          #+#    #+#             */
/*   Updated: 2019/11/20 07:55:31 by hgranule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>

extern int		g_intr;

void			sighand(int s)
{
	g_intr = s;
}

void			sys_sig_dfl(void)
{
	signal(SIGTTIN, SIG_DFL);
	signal(SIGTTOU, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
}

void			sys_sig_init(void)
{
	signal(SIGINT, sighand);
	signal(SIGQUIT, sighand);
	signal(SIGTSTP, sighand);
	signal(SIGTTOU, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
}
