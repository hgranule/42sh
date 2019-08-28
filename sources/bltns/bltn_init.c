/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltn_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnancy <fnancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 18:10:52 by fnancy            #+#    #+#             */
/*   Updated: 2019/08/28 19:53:28 by fnancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bltn.h"

int		bltn_cnt_builtins(void)
{
	return (sizeof(bltns_str) / sizeof(char *));
}

int		bltn_init(ENV *env)
{
	int i;

	i = -1;
	while (++i < bltn_cnt_builtins())
	{
		if ((ft_avl_set(env->builtns, ft_avl_node_cc(bltns_str[i],\
		bltns_func[i], sizeof(bltns_func[i])))) == -1)
			return (-1);
	}
	return (1);
}
