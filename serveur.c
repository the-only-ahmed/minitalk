/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/07 19:35:09 by ael-kadh          #+#    #+#             */
/*   Updated: 2014/02/09 19:48:38 by ycribier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static char		*recover_message(char c)
{
	static char		*message;
	static int		index = 0;
	static int		factor = 1;

	if (index == 0)
	{
		message = (char *)malloc(sizeof(char) * (MESSAGE_SIZE + 1));
		ft_bzero(message, MESSAGE_SIZE + 1);
	}
	message[index] = c;
	index++;
	if (index >= (MESSAGE_SIZE * factor))
	{
		factor++;
		message = ft_realloc(message, factor * MESSAGE_SIZE);
	}
	if (c == '\0')
	{
		factor = 1;
		index = 0;
	}
	return (message);
}

static void		recover_char(int sig, pid_t pid)
{
	char		c;
	t_client	*client;

	client = choose_client(pid);
	if (sig == SIGUSR1)
		client->str[client->current_bit] = '0';
	else if (sig == SIGUSR2)
		client->str[client->current_bit] = '1';
	client->current_bit++;
	if (client->current_bit == 7)
	{
		client->current_bit = 0;
		client->str[7] = '\0';
		c = binary_str_to_char(client->str);
		client->message = recover_message(c);
		if (c == '\0' && pid)
		{
			ft_putendl(client->message);
			ft_putstr(C(YELLOW)"Client PID : "C(PINK));
			ft_putnbr(pid);
			ft_putendl(C(NO));
			print_pid();
			client_del(client);
		}
	}
}

static void		signal_handler(int sig, siginfo_t *siginfo, void *context)
{
	static pid_t	last_pid = -1;
	pid_t		client_pid;

	(void)context;
	client_pid = siginfo->si_pid;
	if (client_pid == 0)
		kill(last_pid, SIGUSR2);
	else
	{
		recover_char(sig, client_pid);
		kill(client_pid, SIGUSR1);
	}
	last_pid = client_pid;
}

static void		init_sigaction(struct sigaction *si_act)
{
	ft_memset(si_act, 0, sizeof(*si_act));
	si_act->sa_sigaction = signal_handler;
	si_act->sa_flags |= SA_SIGINFO;
	si_act->sa_flags &= ~SA_RESETHAND;
}

int				main(void)
{
	struct sigaction	si_act;

	print_pid();
	init_sigaction(&si_act);
	sigaction(SIGUSR1, &si_act, NULL);
	sigaction(SIGUSR2, &si_act, NULL);
	while (1);
	return (0);
}
