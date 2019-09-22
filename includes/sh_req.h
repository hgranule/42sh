/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_req.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgranule <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 01:34:45 by hgranule          #+#    #+#             */
/*   Updated: 2019/09/22 11:07:52 by hgranule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_REQ_H
# define SH_REQ_H

# include "libft.h"
# include "ft_avl_tree.h"
# include "env.h"

int			sys_init(void);
int			sys_var_init(ENV *env);

#endif
