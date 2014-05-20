/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decoding.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/08 12:27:53 by ycribier          #+#    #+#             */
/*   Updated: 2014/02/09 19:26:59 by ycribier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

char	ft_pow(char c, int p)
{
	char	res;

	res = 1;
	while (p > 0)
	{
		res *= c;
		p--;
	}
	return (res);
}

char	binary_str_to_char(char *str)
{
	int		i;
	int		j;
	char	c;

	i = 6;
	j = 0;
	c = 0;
	while (i >= 0)
	{
		c += (str[i] - 48) * ft_pow(2, j);
		j++;
		i--;
	}
	return (c);
}
