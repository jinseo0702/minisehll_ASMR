/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enum_mi.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinseo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 09:49:29 by jinseo            #+#    #+#             */
/*   Updated: 2024/12/01 09:52:46 by jinseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef ENUM_MI_H
# define ENUM_MI_H

typedef enum e_builtins_type
{
	BUILT_ECHO,
	BUILT_CD,
	BUILT_PWD,
	BUILT_EXPORT,
	BUILT_UNSET,
	BUILT_ENV,
	BUILT_EXIT,
	BUILT_NOT
}	t_built_type;

typedef enum e_linked_type
{
	LINKED_CON,
	LINKED_NODE
}	t_linked_type;

typedef enum e_insert_type
{
	INSERT_HEAD,
	INSERT_TAIL
}	t_insert_type;

typedef enum e_re_type
{
	T_DLESS,
	T_DGREAT,
	T_LESS,
	T_GREAT
}	t_RDT;

typedef enum e_in_type
{
	T_PIPE,
	T_REDIRECTION,
	T_ARGV,
	T_NULL
}	t_in_type;

typedef enum e_clear_type
{
	LINKED_PCON,
	LINKED_PAN
}	t_clear_type;

typedef enum e_quote_type
{
	QUOTE_DOUBLE,
	QUOTE_SINGLE,
	QUOTE_NONE
}	t_quote_type;

typedef enum e_synerr_type
{
	QUOTE_ERROR = -100,
	SPECIAL_ERROR,
	REDIREC_ERROR
}	t_syerror_type;

typedef enum echo_option
{
	E_NON,
	E_OP,
}	t_echo_option;

#	endif
