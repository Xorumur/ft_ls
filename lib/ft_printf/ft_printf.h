/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecherb <mlecherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 15:53:48 by mlecherb          #+#    #+#             */
/*   Updated: 2021/10/27 16:39:51 by mlecherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

void	ft_putchar(char c);
int		ft_strlen(char *str);
void	ft_putnbru(unsigned int nb);
void	ft_putnbr_base(unsigned long long int nbr, char *base);
void	ft_putstr(char *str);
void	ft_putnbr(int nb);
int		ft_printf(const char *str, ...);

#endif