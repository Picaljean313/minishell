/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:26:44 by anony             #+#    #+#             */
/*   Updated: 2025/03/03 13:58:19 by anony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_UTILS_H
# define FT_PRINTF_UTILS_H

# include "stdarg.h"
# include <stdio.h>
# include <stdint.h>

int		ft_printchar_fd(char c, int fd);
int		ft_printhexnblow_fd(unsigned int i, int fd);
void	ft_printhexup_fd(uintptr_t i, int fd);
int		ft_printhexnbup_fd(unsigned int i, int fd);
int		ft_printnb_fd(int i, int fd);
void	ft_printhexlow_fd(uintptr_t i, int fd);
int		ft_printptr_fd(uintptr_t i, int fd);
int		ft_printstr_fd(char *str, int fd);
int		ft_printunb_fd(unsigned int i, int fd);
void	ft_puthexalower_fd(int i, int fd);
void	ft_puthexaupper_fd(int i, int fd);
int		ft_putarg_fd(char c, va_list args);

#endif