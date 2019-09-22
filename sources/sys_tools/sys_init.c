/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sys_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgranule <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 09:00:27 by hgranule          #+#    #+#             */
/*   Updated: 2019/09/22 11:06:53 by hgranule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sys_tools/sys_hidden.h"
#include "sys_tools/sys_tools.h"
#include "sys_tools/sys_sh_configs.h"
#include "sys_tools/sys_errors.h"

#include "ft_mem.h"
#include "env.h"

int			sys_var_init(ENV *env)
{
	DSTRING		*val;

	val = dstr_new(SHELL_NAME_STD);
	if ((env_set_variable(SH_VAR_SHNAME, val, env)) <= 0)
		sys_fatal_memerr("MALLOC CALL FAILED!");
	dstr_del(&val);
	return (0);
}

int			sys_init(void)
{
	ft_bzero(sys_pipes, SYS_PIPES_SIZE * sizeof(char));
	return (0);
}
