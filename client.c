/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 23:48:08 by marvin            #+#    #+#             */
/*   Updated: 2022/02/01 23:48:08 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_count;

static int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	output(int signo, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (signo == SIGUSR1 && g_count == 1)
	{
		write(1, "Message successfully delivered!\n", 33);
		exit(EXIT_SUCCESS);
	}
}

void	send_to_server(char *pid, char *str)
{
	int	proc_id;
	int	i;
	int	bytes;

	i = 0;
	proc_id = ft_atoi(pid);
	g_count = ft_strlen(str);
	while (str[i])
	{
		bytes = 7;
		while (bytes >= 0)
		{
			if (str[i] & 1 << bytes)
				kill(proc_id, SIGUSR1);
			else
				kill(proc_id, SIGUSR2);
			bytes--;
			usleep(100);
		}
		i++;
		g_count--;
	}
}

int	main(int argc, char *argv[])
{
	struct sigaction	act;

	act.sa_sigaction = output;
	act.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	if (argc != 3)
	{
		write(1, "Error!\n", 7);
		return (0);
	}
	send_to_server(argv[1], argv[2]);
	pause();
	return (0);
}
