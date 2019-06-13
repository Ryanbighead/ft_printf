/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 08:54:40 by rhutchin          #+#    #+#             */
/*   Updated: 2019/06/13 20:34:13 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "ft_printf.h"

int	checktype(const char *fmt, va_list ap)
{
	if (fmt[1] == '%')
		ft_putchar('%');
	if (fmt[1] == 'd' || fmt[1] == 'i') //<------------------------------------ I need to do some junk here to make octal do things. Hex kinda just works but I have no idea....
			ft_putnbr(va_arg(ap, int));
	if (fmt[1] == 'u')//<------------------------------------------------------ I am not sure of wtf should happen here.... it works but does not !work when a !unsigned-int is passed.
		ft_putnbr(va_arg(ap, unsigned int));
//	if (fmt[1] == 'f' || fmt[1] == 'F')
//		----------------------------------------------------------------------- double in normal (fixed-point) notation. f and F only differs in how the strings for an infinite number
//																				or NaN are printed (inf, infinity and nan for f; INF, INFINITY and NAN for F). 
//	if (fmt[1] == 'e' || fmt[1] == 'E')
//		----------------------------------------------------------------------- double value in standard form ([-]d.ddd e[+/-]ddd). An E conversion uses the letter E (rather than e) to
//																				introduce the exponent. The exponent always contains at least two digits; if the value is zero, the
//																				exponent is 00. In Windows, the exponent contains three digits by default, e.g. 1.5e002, but this can be
//																				altered by Microsoft-specific _set_output_format function. 
//	if (fmt[1] == 'g' || fmt[1] == 'G')
//		----------------------------------------------------------------------- double in either normal or exponential notation, whichever is more appropriate for its magnitude. g uses
//																				lower-case letters, G uses upper-case letters. This type differs slightly from fixed-point notation in that
//																				insignificant zeroes to the right of the decimal point are not included. Also, the decimal point is not
//																				included on whole numbers. 
	if (fmt[1] == 'x' || fmt[1] == 'X')
	{
		char	*tmp;

		tmp = ft_itoa_base((long)va_arg(ap, unsigned int), 16);
		if(fmt[1] == 'X')
			ft_putstr(ft_strtoupper(tmp));
		else
			ft_putstr(tmp);
	}
	if (fmt[1] == 'o')
		ft_putstr(ft_itoa_base((long)va_arg(ap, unsigned int), 8));
	if (fmt[1] == 's')
		ft_putstr(va_arg(ap, char *));
	if (fmt[1] == 'c')
		ft_putchar(va_arg(ap, int));
	if (fmt[1] == 'p')
		ft_putstr(ft_strjoin("0x", ft_itoa_base((long)va_arg(ap, void*), 16)));
	if (fmt[1] == 'a' || fmt[1] == 'A')
		{
			char	*tmp;
			
			tmp = ft_strjoin("0x", ft_itoa_base((long)va_arg(ap, double), 16));
			if (fmt[1] == 'A')
				ft_putstr(ft_strtoupper(tmp));
			else
				ft_putstr(tmp);
		}
//		----------------------------------------------------------------------- double in hexadecimal notation, starting with 0x or 0X. a uses lower-case letters, A uses upper-case
//																				letters.[4][5] (C++11 iostreams have a hexfloat that works the same). 
	return (1);
}

int	paramchecker(const char *fmt, va_list ap)
{
	int	i;
	//i = checkflags(); ------------------------------------------------------- Check the flags and do the things.
	//i = checkwidth(); ------------------------------------------------------- Check total printable width and do stuff.
	//i = checklength(); ------------------------------------------------------ Check the.... man, things happen here.
	i = checktype(fmt, ap);
	return(i);
}

int	ft_printf(const char *fmt, ...)
{
	int	i;
	va_list	ap;

	i = 0;
	va_start(ap, fmt);
	while (fmt[i] != '\0')
	{
		if (fmt[i] != '%')
			ft_putchar(fmt[i]);
		if (fmt[i] == '%')
			{
				if (fmt[i + 1] == 'n')//--------------------------------------- You need to have a re-think about printed character tracking...
				{
					int *ptr;
					
					ptr = va_arg(ap, int*);
					*ptr = i;
				}
				i += paramchecker(&fmt[i], ap);
			}
		i++;
	}
	va_end(ap);
	return (0);
}
/************************************************************************************/
/*************************************THE MAIN***************************************/
/************************************************************************************/
int	main(void)
{
	char 			c = 'A';
	char			*i = "String";
	unsigned int	n = 873544224;
	double			d = 873544224;

	printf("\n\n   printf prints |%p|-|%c|-|%s|-|%%|-|%X|-|%o|-|%A|\n\n", &i, c, i, n, n, d);
	ft_printf("ft_printf prints |%p|-|%c|-|%s|-|%%|-|%X|-|%o|-|%A|\n\n", &i, c, i, n, n, d);
	return (0);
}