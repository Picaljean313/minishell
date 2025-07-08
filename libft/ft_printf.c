/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 17:38:56 by anony             #+#    #+#             */
/*   Updated: 2025/03/03 14:00:34 by anony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		count;
	int		i;

	count = 0;
	i = 0;
	if (!str)
		return (-1);
	va_start (args, str);
	while (str[i])
	{
		if (str[i] != '%')
		{
			ft_putchar_fd (str[i], 1);
			count++;
			i++;
			continue ;
		}
		if (!str[i + 1])
			return (va_end(args), -1);
		count += ft_putarg_fd (str[i + 1], args);
		i += 2;
	}
	va_end (args);
	return (count);
}
/*
#include <stdio.h>
int main ()
{
	void *p;
	
	printf("c test : %i\n", ft_printf("%c\n", 'c'));
	printf("c printf : %i\n", printf("%c\n", 'c'));
	
	printf("s test : %i\n", ft_printf("%s\n", "coucou"));
	printf("s printf : %i\n", printf("%s\n", "coucou"));

	printf("p test : %i\n", ft_printf("%p\n", p));
	printf("p printf : %i\n", printf("%p\n", p));

	printf("d test : %i\n", ft_printf("%d\n", 12345));
	printf("d printf : %i\n", printf("%d\n", 12345));

	printf("i test : %i\n", ft_printf("%i\n", 12345));
	printf("i printf : %i\n", printf("%i\n", 12345));

	printf("u test : %i\n", ft_printf("%u\n", 12345));
	printf("u printf : %i\n", printf("%u\n", 12345));

	printf("x test : %i\n", ft_printf("%x\n", 1234567));
	printf("x printf : %i\n", printf("%x\n", 1234567));

	printf("X test : %i\n", ft_printf("%X\n", 1234567));
	printf("X printf : %i\n", printf("%X\n", 1234567));

	printf("percent test : %i\n", ft_printf("%%\n"));
	printf("percent printf : %i\n", printf("%%\n"));

	printf("percent seul printf : %i\n", ft_printf("%"));
	printf("percent seul printf : %i\n", printf("%"));

	printf("0 test : %i\n", ft_printf(0));
	printf("0 printf : %i\n", printf(0));

	printf("imin test : %i\n", ft_printf("%i\n", -2147483648));
	printf("imin printf : %i\n", printf("%i\n", -2147483648));

	printf("char vide test : %i\n", ft_printf("%s\n", ""));
	printf("char vide printf : %i\n", printf("%s\n", ""));

	printf("NULL test : %i\n", ft_printf("%p\n", NULL));
	printf("NULL printf : %i\n", printf("%p\n", NULL));

	printf("melange test : %i\n", ft_printf("%s%%
	%c%i%%%p%u\n", "hihi", 'k', 42, p, -42));
	printf("melange printf : %i\n", printf("%s%%
	%c%i%%%p%u\n", "hihi", 'k', 42, p, -42));
  return 0;
}*/
