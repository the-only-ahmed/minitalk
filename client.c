/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/07 19:35:09 by ael-kadh          #+#    #+#             */
/*   Updated: 2014/02/09 19:54:37 by ycribier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int		g_sig;

static void		signal_handler(int sig)
{
	g_sig = sig;
}

static void		send_bit_signal(int pid, char c)
{
	if (c == '0')
	{
		if (kill(pid, SIGUSR1) == -1)
			error_msg_exit(ft_itoa(pid), "No such process.");
	}
	else if (c == '1')
	{
		if (kill(pid, SIGUSR2) == -1)
			error_msg_exit(ft_itoa(pid), "No such process.");
	}
}

static void		send_message_to_pid(int pid, char *message)
{
	int		i;
	int		j;
	int		len;
	char	str[9] = {0};

	len = ft_strlen(message);
	i = 0;
	while (i <= len)
	{
		char_to_binary_str(message[i], str);
		j = 0;
		while (j < 7)
		{
			send_bit_signal(pid, str[j]);
			usleep(1000);
			if (g_sig == SIGUSR1)
				j++;
		}
		i++;
	}
	ft_putstr("finish sending message\n");
}

int				main(int ac, char **av)
{
	int		pid;

	if (ac == 3 && av[2][0])
	{
		g_sig = SIGUSR1;
		signal(SIGUSR1, signal_handler);
		signal(SIGUSR2, signal_handler);
		pid = ft_atoi(av[1]);
		send_message_to_pid(pid, av[2]);
	}
	else
		ft_putendl_fd("usage: ./client [pid server] [message]", 2);
	return (0);
}
