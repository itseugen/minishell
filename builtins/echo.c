/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:23:40 by eweiberl          #+#    #+#             */
/*   Updated: 2023/10/18 13:45:34 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int	builtin_echo(char)
//! For echo: go through original string
//!(from after "echo " till you find a pipe or sum that would stop echo)
//!Use write as printf buffer managment causes issues