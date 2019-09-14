/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_calls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgranule <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 09:03:40 by hgranule          #+#    #+#             */
/*   Updated: 2019/09/13 18:15:39 by hgranule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"
#include <stdio.h>

// TODO: NEED TO CHECK FOR ERRORS!!!!!

int			exe_wait_cps(pid_t cpid)
{
	int		statloc;
	int		estatus;
	pid_t	pid;

	while ((pid = waitpid(cpid, &statloc, WUNTRACED)) || 1)
	{
		estatus = WEXITSTATUS(statloc);
		if (WIFEXITED(statloc))
			break ;
		if (WIFSIGNALED(statloc))
			break ;
	}
	while ((pid = waitpid(-1, &statloc, WUNTRACED)) && pid > 0)
	{
		if (WIFEXITED(statloc))
			break ;
		if (WIFSIGNALED(statloc))
			break ;
	}
	return (estatus);
}

int			exe_execute_expr(EXPRESSION *expr, ENV *envr, int *status)
{
	int		(*bltn)(char **, ENV *envr);
	FUNC	*func;
	t_avln	*f_node;

	if ((f_node = ft_avl_search(envr->builtns, expr->args[0])))
	{
		// *BUILTN
		bltn = f_node->content;
		if (expr->ipipe_fds || expr->opipe_fds)
			return (exe_execute_pi_b(expr, envr, bltn));// *RETURNS CPID
		else
			return (exe_execute_b(expr, envr, bltn, status));
			// *RETURNS ZERO if normal
	}
	else if ((f_node = ft_avl_search(envr->funcs, expr->args[0])))
	{
		func = f_node->content; // NEED TO MAKE FUNCTION STRUCTURE
		if (expr->ipipe_fds || expr->opipe_fds)
			return (exe_execute_pi_f(expr, envr, func));
		else
			return (exe_execute_f(expr, envr, func, status));
	}
		return (exe_execute_pi(expr, envr));// *RETURNS CPID
}
