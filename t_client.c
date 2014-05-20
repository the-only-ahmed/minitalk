/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_client.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/07 19:35:09 by ael-kadh          #+#    #+#             */
/*   Updated: 2014/02/09 19:26:54 by ycribier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static t_client		*get_instance(int del)
{
	static t_client		*client = NULL;

	if (!client)
	{
		client = (t_client*)malloc(sizeof(t_client));
		client->pid = -1;
		client->current_bit = 0;
		client->message = NULL;
		ft_bzero(client->str, 8);
		client->next = NULL;
	}
	if (del)
	{
		free(client->message);
		free(client);
		client = NULL;
	}
	return (client);
}

t_client			*choose_client(pid_t pid)
{
	t_client	*client;
	t_client	*tmp;

	client = get_instance(0);
	if (client->pid == -1)
		client->pid = pid;
	while (client->next && client->pid != pid)
		client = client->next;
	if (client->pid != pid)
	{
		tmp = (t_client*)malloc(sizeof(t_client));
		tmp->pid = pid;
		client->message = NULL;
		client->current_bit = 0;
		ft_bzero(client->str, 8);
		tmp->next = NULL;
		client->next = tmp;
		client = client->next;
	}
	return (client);
}

void				client_del(t_client *client)
{
	t_client	*tmp;

	while (client->next)
	{
		if (client->message)
			free(client->message);
		client->message = ft_strdup(client->next->message);
		client->pid = client->next->pid;
		tmp = client;
		client = client->next;
		if (!client->next)
			tmp->next = NULL;
	}
	if (client == get_instance(0))
		client = get_instance(1);
	if (client)
	{
		free(client->message);
		free(client);
	}
	client = NULL;
}

