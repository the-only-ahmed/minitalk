/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/07 19:35:43 by ael-kadh          #+#    #+#             */
/*   Updated: 2014/02/09 19:44:22 by ycribier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <signal.h>
# include "libft.h"

typedef struct			s_client
{
	int					pid;
	int					current_bit;
	char				*message;
	char				str[8];
	struct s_client		*next;
}						t_client;

/*
**	Client
*/

void		char_to_binary_str(char c, char *str);

/*
**	Server
*/

# define MESSAGE_SIZE	1024

char		binary_str_to_char(char *str);
void		client_del(t_client *client);
t_client	*choose_client(pid_t pid);

void		print_pid(void);
char		*ft_realloc(char *str, int size);

/*
**		DEBUG
*/

# define RED		"31"
# define GREEN		"32"
# define YELLOW		"33"
# define BLUE		"34"
# define PINK		"35"
# define GRBL		"36"
# define GREY		"37"
# define NO			"0"
# define C(X)		"\033["X"m"

#endif /* !MINITALK_H */
