// Assignment name  : ft_printf
// Expected files   : ft_printf.c
// Allowed functions: malloc, free, write, va_start, va_arg, va_copy, va_end
// --------------------------------------------------------------------------------

// Write a function named `ft_printf` that will mimic the real printf with the following constraints:

// - It will manage only the following conversions: s,d and x

// Your function must be declared as follows:

// int ft_printf(const char *, ... );

// Before you start we advise you to read the `man 3 printf` and the `man va_arg`.
// To test your program compare your results with the true printf.

// Exemples of the function output:

// call: ft_printf("%s\n", "Hello toto");
// out:Hello toto$

// call: ft_printf("Magic %s is %d", "number", 42);
// out:Magic number is 42$

// call: ft_printf("Hexadecimal for %d is %x\n", 42, 42);
// out:Hexadecimal for 42 is 2a$

#include <unistd.h>
#include <stdarg.h>

size_t	g_count;

void	ft_putchar(char c)
{
	g_count += write (1, &c, 1);
}

void	ft_putstr(char *s)
{
	if (s == NULL)
		ft_putstr("(null)");
	while (s && *s)
		ft_putchar(*s++);
}

void	ft_putnbr_base(long nbr, int base)
{
	char	*dec = "0123456789";
	char	*hex = "0123456789abcdef";

	if (nbr < 0)
	{
		nbr = -nbr;
		ft_putchar('-');
	}
	if (nbr >= base)
	{
		ft_putnbr_base(nbr / base, base);
		ft_putnbr_base(nbr % base, base);
	}
	else
	{
		if (base == 10)
			ft_putchar(dec[nbr]);
		else if (base == 16)
			ft_putchar(hex[nbr]);
	}
}

void	ft_convert(char c, va_list arg)
{
	if (c == '%')
		ft_putchar('%');
	else if (c == 's')
		ft_putstr(va_arg(arg, char *));
	else if (c == 'd')
		ft_putnbr_base(va_arg(arg, int), 10);
	else if (c == 'x')
		ft_putnbr_base(va_arg(arg, unsigned int), 16);
}

int	printf(const char **txt, ...)
{
	va_list	arg;

	g_count = 0;
	va_start(arg, txt);
	while (*txt != '\0')
	{
		if (*txt == '%')
		{
			ft_convert(*(++txt), arg);
			if (!(*txt))
				break ;
		}
		else
			ft_putchar(*txt);
		txt++;
	}
	va_end (arg);
	return (g_count);
}
