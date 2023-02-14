/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkorsako <pkorsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 15:03:42 by pkorsako          #+#    #+#             */
/*   Updated: 2023/02/14 03:47:45 by pkorsako         ###   ########.fr       */
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

long int	get_time()
{
	long int		time;
	struct timeval	current_time;
	
	time = 0;
	gettimeofday(&current_time, NULL);
	time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
//	printf("tv_sec :%ld\ttv_usec :%ld\ttime :%ld\n", current_time.tv_sec * 1000, current_time.tv_usec / 1000, time);
	return (time);
}

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
	philo.dead = 0;
	printf("philo.start_time :%ld\n", philo.start_time);
	save_args(&argv[1], argc, &philo);
	int i = philo.args.philo_nbr + 1;
	philo_nbr = i - 1;
	printf("taille du tableau mutex :%d\t", i);
	philo.philosophers = malloc(sizeof(pthread_t) * i);
	philo.fork = malloc(sizeof(int) * i);
	philo.fork_mutex = malloc(sizeof(pthread_mutex_t) * i);
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
	philo.ready = 0;
	while(++i < philo_nbr)
	{
		philo.args.philo_nbr = i + 1;
		printf("in while philo.args.nbr :%d\ti :%d\n", philo.args.philo_nbr, i);
		pthread_create(&philo.philosophers[i], NULL, thread_routine, &philo);
		get_ready(&philo, philo.args.philo_nbr);
		while (1)
		{
			pthread_mutex_lock(&philo.fork_mutex[philo.args.philo_nbr]);
			if (philo.ready)
			{
				philo.ready = 0;
				pthread_mutex_unlock(&philo.fork_mutex[philo.args.philo_nbr]);
				break;
			}
			pthread_mutex_unlock(&philo.fork_mutex[philo.args.philo_nbr]);
			
		}
	}
	philo.start_time = get_time();
	printf("philo start time :%ld\n", philo.start_time);
	pthread_mutex_lock(&philo.fork_mutex[0]);
	philo.ready_for_start = 1;
	pthread_mutex_unlock(&philo.fork_mutex[0]);
//	while(philo.dead == 0 ||)
//	{}
	sleep(1);
	write(1, "main stoped\n", 13);
}