/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkorsako <pkorsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 15:03:42 by pkorsako          #+#    #+#             */
/*   Updated: 2023/02/10 20:34:51 by pkorsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	save_args(char **argv, int argc, t_philo *philo)
{
	if (argc >= 5 && argc <= 6)
	{
		philo->args.philo_nbr = atoi(argv[0]);
		philo->args.time_to_die = atoi(argv[1]);
		philo->args.time_to_eat = atoi(argv[2]);
		philo->args.time_to_sleep = atoi(argv[3]);
	}
	if (argc == 6)
		philo->args.nbr_philo_must_eat = atoi(argv[4]);
	printf("how_much to eat :%d\t", philo->args.nbr_philo_must_eat);
}

/*t_philo	*set_philo(t_philo *philo)
{
	philo->philosophers = malloc(sizeof(pthread_t) * philo->args.philo_nbr);
	return (philo);
}*/

void	get_ready(t_philo *philo, int philo_id)
{
	if (philo->args.philo_nbr % 2 == 0)
	{
		philo->fork[philo_id - 1] = USED;
		philo->fork[philo_id] = USED;
	}
}

int main(int argc, char *argv[])
{
	t_philo		philo;
	int philo_nbr;
	
	philo.ready_for_start = 0;
	save_args(&argv[1], argc, &philo);
	int i = philo.args.philo_nbr + 1;
	philo_nbr = i - 1;
	printf("taille du tableau mutex :%d\t", i);
	philo.philosophers = malloc(sizeof(pthread_t) * i);
	philo.fork = malloc(sizeof(int) * i + 1);
	philo.fork_mutex = malloc(sizeof(pthread_mutex_t) * i + 1);
	if (!philo.fork_mutex || !philo.fork || !philo.philosophers)
	{
		write(1, "malloc error\n", 14);
		exit (1);
	}
	memset(philo.fork, FREE, philo.args.philo_nbr);
	while(i-- > 0)
	{
		printf("mutex declaration i :%d\n", i);
		pthread_mutex_init(&philo.fork_mutex[i], NULL);
	}
	philo.fork[philo.args.philo_nbr - 1] = -1;
	printf("philo.args.nbr befor while :%d\tphilo_nbr :%d\ti:%d\n", philo.args.philo_nbr, philo_nbr, i);
	while(++i < philo_nbr)
	{
		philo.args.philo_nbr = i + 1;
		philo.ready = 0;
		printf("in while philo.args.nbr :%d\ti :%d\n", philo.args.philo_nbr, i);
		pthread_create(&philo.philosophers[i], NULL, thread_routine, &philo);
		get_ready(&philo, philo.args.philo_nbr);
		while (philo.ready == 0)
		{}
	}
	philo.ready_for_start = 1;
	sleep(1);
	write(1, "main stoped\n", 13);
}