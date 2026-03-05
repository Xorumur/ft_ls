/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecherb <mlecherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 16:12:18 by mlecherb          #+#    #+#             */
/*   Updated: 2021/10/27 16:33:31 by mlecherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

int	main(void)
{
	int ret = printf("Salut a tous %p, j'ai : %i dents\n", "Les amis", 4);
	int ret2 = ft_printf("Salut a tous %p, j'ai : %i dents\n", "Les amis", 4);
	ft_printf("%i\n", ret);
	ft_printf("%i\n", ret2);
	ret = printf("Salut a tous %p, j'ai : %i dents\n", "Les amis", 4);
	ret2 = ft_printf("Salut a tous %p, j'ai : %i dents\n", "Les amis", 4);
	ft_printf("%i\n", ret);
	ft_printf("%i\n", ret2);
	return (0);
}