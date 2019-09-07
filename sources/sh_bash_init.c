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

//while init done
static t_graph  *done_init(void)
{
    t_graph *script;

    script = (t_graph *)malloc((sizeof(t_graph)));
    script->type = done_tk;
    script->patt = "done_";
    script->forward = NULL;
    script->left = NULL;
    script->right = NULL;
    script->next = NULL;
    return (script);
}

static t_graph  *expr_init(t_graph *tk)
{
    t_graph *script;

    script = (t_graph *)malloc((sizeof(t_graph)));
    script->type = expr_tk;
    script->patt = "~";
    script->forward = done_init();
    script->left = tk;
    script->right = NULL;
    script->next = NULL;
    return (script);
}

static t_graph     *do_init(t_graph *tk)
{
    t_graph *script;

    script = (t_graph *)malloc((sizeof(t_graph)));
    script->type = do_tk;
    script->patt = "do_";
    script->forward = expr_init(tk);
    script->left = tk;
    script->right = NULL;
    script->next = NULL;
    return (script);
}

static t_graph  *condition_init(t_graph *whiletk)
{
    t_graph *script;

    script = (t_graph *)malloc((sizeof(t_graph)));
    script->type = expr_tk;
    script->patt = "[~]^";
    script->forward = do_init(whiletk);
    script->left = NULL;
    script->right = NULL;
    script->next = NULL;
    return (script);
}

static void     whiletk_init(t_graph *script)
{
    script->type = while_tk;
    script->patt = "while_";
    script->forward = condition_init(script);
    script->left = NULL;
    script->right = NULL;
    script->next = NULL;
}

t_graph  *while_script_in(void)
{
    t_graph *script;

    script = (t_graph *)malloc((sizeof(t_graph)));
    whiletk_init(script);
    return (script);
}
// while init

// for init done

static t_graph  *prexpr_init(t_graph *tk)
{
    t_graph *script;

    script = (t_graph *)malloc((sizeof(t_graph)));
    script->type = expr_tk;
    script->patt = "~";
    script->forward = do_init(tk);
    script->left = NULL;
    script->right = NULL;
    script->next = NULL;
    return (script);
}

static t_graph    *in_init(t_graph *fortk)
{
    t_graph *script;

    script = (t_graph *)malloc((sizeof(t_graph)));
    script->type = in_tk;
    script->patt = "in_";
    script->forward = prexpr_init(fortk);
    script->left = NULL;
    script->right = NULL;
    script->next = NULL;
    return (script);
}

static t_graph    *inexpr_init(t_graph *fortk)
{
    t_graph *script;

    script = (t_graph *)malloc((sizeof(t_graph)));
    script->type = expr_tk;
    script->patt = "!in";
    script->forward = in_init(fortk);
    script->left = NULL;
    script->right = NULL;
    script->next = NULL;
    return (script);
}

static t_graph    *forexpr_init(t_graph *fortk)
{
    t_graph *script;

    script = (t_graph *)malloc((sizeof(t_graph)));
    script->type = expr_tk;
    script->patt = "((~))^";
    script->forward = do_init(fortk);
    script->left = NULL;
    script->right = NULL;
    script->next = NULL;
    return (script);
}

static void     fortk_init(t_graph *script)
{
    script->type = for_tk;
    script->patt = "for_";
    script->left = inexpr_init(script);
    script->forward = forexpr_init(script);
    script->right = NULL;
    script->next = NULL;
}

t_graph  *for_script_in(void)
{
    t_graph *script;

    script = (t_graph *)malloc((sizeof(t_graph)));
    fortk_init(script);
    return (script);
}
// for init

// until init done
static void     *untiltk_init(t_graph *script)
{
    script->type = until_tk;
    script->patt = "until_";
    script->forward = condition_init(script);
    script->left = NULL;
    script->right = NULL;
    script->next = NULL;
}

t_graph  *until_script_in(void)
{
    t_graph *script;

    script = (t_graph *)malloc((sizeof(t_graph)));
    untiltk_init(script);
    return (script);
}
// until init

// if init done
static t_graph  *elsetk_init(t_graph *expr)
{
    t_graph *script;

    script = (t_graph *)malloc((sizeof(t_graph)));
    script->type = else_tk;
    script->patt = "else_";
    script->forward = expr;
    script->left = NULL;
    script->right = NULL;
    script->next = NULL;
    return (script);
}

static t_graph  *fitk_init(void)
{
    t_graph *script;

    script = (t_graph *)malloc((sizeof(t_graph)));
    script->type = fi_tk;
    script->patt = "fi_";
    script->forward = NULL;
    script->left = NULL;
    script->right = NULL;
    script->next = NULL;
    return (script);
}

static t_graph  *exprtk2_init(void)
{
    t_graph *script;

    script = (t_graph *)malloc((sizeof(t_graph)));
    script->type = expr_tk;
    script->patt = "~";
    script->forward = fitk_init();
    script->left = elsetk_init(script);
    script->forward->left = script->left;
    script->right = NULL;
    script->next = NULL;
    return (script);
}

static t_graph  *thentk_init(void)
{
    t_graph *script;

    script = (t_graph *)malloc((sizeof(t_graph)));
    script->type = then_tk;
    script->patt = "then_";
    script->forward = exprtk2_init();
    script->left = NULL;
    script->right = NULL;
    script->next = NULL;
    return (script);
}

static t_graph  *exprtk1_init(void)
{
    t_graph *script;

    script = (t_graph *)malloc((sizeof(t_graph)));
    script->type = expr_tk;
    script->patt = "[~]^";
    script->forward = thentk_init();
    script->left = NULL;
    script->right = NULL;
    script->next = NULL;
    return (script);
}

static void     iftk_init(t_graph *script)
{
    script->type = if_tk;
    script->patt = "if_";
    script->forward = exprtk1_init();
    script->left = NULL;
    script->right = NULL;
}

t_graph  *if_script_in(void)
{
    t_graph *script;

    script = (t_graph *)malloc((sizeof(t_graph)));
    iftk_init(script);
    return (script);
}
// if init