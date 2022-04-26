/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 23:48:17 by marvin            #+#    #+#             */
/*   Updated: 2022/02/01 23:48:17 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	output_handler(int signo, siginfo_t *info, void *context)
{
	static int	count = 0;
	static int	symb = 0;

	(void)context;
	if (signo == SIGUSR1)
		symb += 1 << (7 - count);
	count++;
	if (count == 8)
	{
		write(1, &symb, 1);
		kill(info->si_pid, SIGUSR1);
		symb = 0;
		count = 0;
	}
}

int	main(void)
{
	int					pid;
	struct sigaction	act;

	pid = getpid();
	ft_putnbr_fd(pid, 1);
	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = output_handler;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	while (1)
		pause();
	return (0);
}
