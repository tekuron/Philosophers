/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danz <danz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 18:29:54 by danz              #+#    #+#             */
/*   Updated: 2026/01/27 22:26:32 by danz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	cleanup(t_philo *args)
{
	sem_close(args->fork_sem);
	sem_unlink("/fk_z_1");
	sem_close(args->print_sem);
	sem_unlink("/pt_z_1");
}

int	main(int argc, char **argv)
{
	t_philo	args;
	int		*pids;

	if (args_init(argc, argv, &args))
	{
		printf("Usage: philo number_of_philosophers time_to_die time_to_eat");
		printf(" time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
		return (1);
	}
	pids = malloc(sizeof(int) * args.nop);
	philo_create(pids, &args);
	wait_for_eos(pids, args.nop);
	free(pids);
	cleanup(&args);
}
