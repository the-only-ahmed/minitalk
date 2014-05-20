/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/09 19:21:21 by ycribier          #+#    #+#             */
/*   Updated: 2014/02/09 19:47:10 by ycribier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	print_pid(void)
{
	static int		i = 0;

	if (!i)
	{
		i++;
		ft_putstr(C(RED)"Server started.\nPID : "C(GREEN));
	}
	else
		ft_putstr(C(RED)"Server PID : "C(GREEN));
	ft_putnbr(getpid());
	ft_putendl(C(NO));
}

char	*ft_realloc(char *str, int size)
{
	char	*tmp;

	tmp = str;
	str = (char *)malloc(sizeof(char) * (size + 1));
	ft_bzero(str, size + 1);
	str = ft_strcpy(str, tmp);
	free(tmp);
	return (str);
}
