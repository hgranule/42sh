/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bomanyte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 00:53:18 by bomanyte          #+#    #+#             */
/*   Updated: 2019/08/19 00:53:23 by bomanyte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_req.h"
#include "sh_token.h"
#include "sh_tokenizer.h"

static char *func_args(char *str, t_stx **tr, t_dlist **tok)
{
    size_t i;

    i = 0;
    str++;
    while (*str && *str != '}')
    {
        while (*str && (*str == ' ' || *str == '\t'))
            str++;
        if (*str == ';')
        {
            make_token(tok, pull_token(str - i, i), expr_tk);
            str = parse_sep(str, tok, tr, 0);
            i = 0;
        }
        if (*str++ != ' ' && *str != '\t')
            i++;
    }
    if (!(*str))
        return (0);
    make_token(tok, pull_token(str - i, i), expr_tk);
    make_token(tok, NULL, fend_tk);
    return (str + 1);
}

static char *get_function(char *str, t_stx **tr, t_dlist **tok)
{
    size_t i;
    char *reg1;
    char *reg2;

    reg1 = "! ";
    reg2 = "{~}";
    i = 0;
    str = parse_empty(str, "", tok);
    if ((*str >= 65 && *str <= 90) || (*str >= 97 && *str <= 122))
    {
//        while (*str && *str != ' ' && *str != '\t')
//        {
//            i++;
//            str++;
//        }
//        if (!(*str))
//            return (0);
        // str = parse_empty(str, reg1, tok);
        if ((i = layer_parse_two(reg1, str)))
        {
            make_token(tok, pull_token(str, i), name_tk);
            str = parse_empty(str + i, reg1, tok);
            if ((layer_parse_two(reg2, str)))
                return (func_args(str, tr, tok));
            else
            {
                str = ft_process_vars(expr_tk, str, "/;/\n", tok);
                make_token(tok, NULL, fend_tk);
                return (parse_sep(str, tok, tr, 0));
            }
        }
    }
    return (str + i);
}

char*   parse_func(char *str, t_dlist **tok, t_stx **tree, short ind)
{
    char *patt0;
    char *patt2;
    char *tmp;

    patt0 = "function_";
    patt2 = "?(~)_";
    //patt1 = "! {~}";
    //patt2 = "^?()^{~}";
    while (*str)
    {
        //tmp = script_pull(patt1, math_tk, str, tree, tok)
        if ((tmp = reg_process(patt0, function_tk, str, tree, tok)) != str && tmp)
            return (get_function(str + 8, tree, tok));
        else if ((layer_parse_two(patt2, str)))
        {
            make_token(tok, NULL, function_tk);
            return (get_function(str, tree, tok));
        }
        str++;
        ind++;
    }
    return (str - ind);
}