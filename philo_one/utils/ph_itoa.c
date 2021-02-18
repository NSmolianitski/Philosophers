/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkentaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 18:01:24 by pkentaur          #+#    #+#             */
/*   Updated: 2021/02/16 18:01:25 by pkentaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	get_num_of_digits(long n)
{
	int		i;

	i = 0;
	if (n < 0)
		++i;
	while (n != 0)
	{
		n /= 10;
		++i;
	}
	return (i);
}

static int	is_min(char *str, long *n, int *i)
{
	if (*n == -9223372036854775807)
	{
		*n = 9223372036854775807;
		str[0] = '-';
		++*i;
		return (1);
	}
	return (0);
}

static char	*fill_str(char *str, long n)
{
	int		i;
	int		min;

	i = 0;
	min = is_min(str, &n, &i);
	if (n < 0)
	{
		str[0] = '-';
		n *= -1;
		++i;
	}
	while (n != 0)
	{
		str[i] = n % 10 + 48;
		n /= 10;
		++i;
	}
	if (min)
		str[1] = '8';
	return (str);
}

static void	reverse_string(char *str, int num_of_digits, long i)
{
	char	c;

	while (i <= num_of_digits)
	{
		c = str[i];
		str[i] = str[num_of_digits];
		str[num_of_digits] = c;
		--num_of_digits;
		++i;
	}
}

char		*ph_itoa(long n)
{
	long	i;
	char	*str;
	int		num_of_digits;

	num_of_digits = get_num_of_digits(n);
	if (n < 0)
		str = (char*)malloc(sizeof(char) * (num_of_digits + 1));
	else
		str = (char*)malloc(sizeof(char) * (num_of_digits + 2));
	if (0 == str)
		return (0);
	if (n == 0)
	{
		str[0] = '0';
		++num_of_digits;
	}
	else
		str = fill_str(str, n);
	str[num_of_digits] = '\0';
	--num_of_digits;
	i = 0;
	if (n < 0)
		i = 1;
	reverse_string(str, num_of_digits, i);
	return (str);
}
