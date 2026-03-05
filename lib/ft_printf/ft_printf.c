/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecherb <mlecherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 11:23:19 by mlecherb          #+#    #+#             */
/*   Updated: 2021/10/27 16:43:53 by mlecherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// Ce fichier doit permettre de recupere les %.. dans la string de printf
// Et de le envoyer dans une fonction qui les traitent.

static int	g_count = 0;

void	ft_putchar(char c)
{
	write(1, &c, 1);
	g_count++;
}

void	ft_putnbr(int nb)
{
	unsigned int	n;

	if (nb < 0)
	{
		ft_putchar('-');
		nb *= -1;
	}
	n = (unsigned int)nb;
	if (n / 10)
		ft_putnbr(n / 10);
	ft_putchar((n % 10) + '0');
}

void	ft_det(char c, va_list va)
{
	if (c == 'c')
		ft_putchar(va_arg(va, int));
	if (c == 's')
		ft_putstr(va_arg(va, char *));
	if (c == 'p')
	{
		ft_putstr("0x");
		ft_putnbr_base(va_arg(va, unsigned long long int), "0123456789abcdef");
	}
	if (c == 'd')
		ft_putnbr(va_arg(va, int));
	if (c == 'i')
		ft_putnbr(va_arg(va, int));
	if (c == 'u')
		ft_putnbru(va_arg(va, unsigned int));
	if (c == 'x')
		ft_putnbr_base(va_arg(va, unsigned int), "0123456789abcdef");
	if (c == '%')
		ft_putchar('%');
}

int	ft_printf(const char *str, ...)
{
	int		i;
	va_list	va;

	va_start(va, str);
	g_count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			i++;
			ft_det(str[i], va);
		}
		else
			ft_putchar(str[i]);
		i++;
	}
	va_end(va);
	return (g_count);
}
