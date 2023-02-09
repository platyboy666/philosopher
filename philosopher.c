/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkorsako <pkorsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 15:03:42 by pkorsako          #+#    #+#             */
/*   Updated: 2023/02/09 15:10:29 by pkorsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	eat(t_philo *philo, int philo_id)
{
	/*if(philo.fork[philo_id + 1] == -1)
	{
		if(philo.fork[philo_id] && philo.fork[0])//ptet pas necessaire
		{
			pthread_mutex_lock(&philo.fork_mutex[philo_id]);
			philo.fork[philo_id - 1] = USED;
			philo.fork[philo_id] = USED;
			pthread_mutex_unlock(&philo.fork_mutex[0]);
			usleep(philo.args.time_to_eat);
			philo.fork[philo_id - 1] = FREE;
			philo.fork[philo_id] = FREE;
		}
	}
	else
	{*/
//		if (philo.fork[philo_id] && philo.fork[philo_id + 1])
//		{
			pthread_mutex_lock(&philo->fork_mutex[philo_id - 1]);
			pthread_mutex_lock(&philo->fork_mutex[philo_id]);
			philo->fork[philo_id - 1] = USED;
			philo->fork[philo_id] = USED;
			usleep(philo->args->time_to_eat);
			philo->fork[philo_id - 1] = FREE;
			philo->fork[philo_id] = FREE;
			pthread_mutex_unlock(&philo->fork_mutex[philo_id - 1]);
			pthread_mutex_unlock(&philo->fork_mutex[philo_id]);
//		}
//	}
	return (1);
}

int	can_eat(t_philo *philo, int philo_id)
{
	if (!philo->fork[philo_id - 1] || !philo->fork[philo_id])
		return (0);
	else 
		return (1);
}

int	sleeping(t_philo *philo, int philo_id)
{
	printf("philo %d is sleeping", philo_id);
	usleep(philo->args->time_to_sleep);
	return(1);
}

int	think(t_philo *philo, int philo_id)
{
	printf("philo %d is thinking", philo_id);
	return (1);
}

void	*thread_routine(void *philosopher)
{
	t_philo	*philo = (t_philo *)philosopher;
	int philo_id = philo->args->philo_nbr + 1;
	int	vie;

	
	vie = 1;
	printf("philo_id :%d\n", philo_id);
	philo->ready = 1;
	while(vie == 1)
	{
		if (!can_eat(philo, philo_id))
			sleeping(philo, philo_id);
		think(philo, philo_id);
		eat(philo, philo_id);
	}
	return (NULL);
}

t_args	save_args(char **argv, int argc)
{
	t_args	args;
	
	if (argc >= 5 && argc <= 6)
	{
		args.philo_nbr = atoi(argv[0]);
		args.time_to_die = atoi(argv[1]);
		args.time_to_eat = atoi(argv[2]);
		args.time_to_sleep = atoi(argv[3]);
	}
	if (argc == 6)
		args.nbr_philo_must_eat = atoi(argv[4]);
	return (args);
}

t_philo	*set_philo(t_philo *philo)
{
	philo->philosophers = malloc(sizeof(pthread_t) * philo->args.philo_nbr);
	return (philo);
}

int main(int argc, char *argv[])
{
	t_philo		philo;

	philo.args = save_args(&argv[1], argc);
	int i = philo.args.philo_nbr;
//	int i = 5;
	printf("taille du tableau mutex :%d\t", i);
//	philo = set_philo(philo);
	philo.philosophers = malloc(sizeof(pthread_t) * i);
	philo.fork = malloc(sizeof(int) * i + 1);
	philo.fork_mutex = malloc(sizeof(pthread_mutex_t) * i);
//	philo.fork_mutex = memset(philo.fork_mutex, USED, sizeof(pthread_mutex_t) * i);
	if (!philo.fork_mutex || !philo.fork || !philo.philosophers)
	{
		write(1, "malloc error\n", 14);
		exit (1);
	}
	while(i-- > 0)
	{
		printf("i :%d\t", i);
		pthread_mutex_init(&philo.fork_mutex[i], NULL);
	}
	memset(philo.fork, FREE, philo.args.philo_nbr);
	philo.fork[philo.args.philo_nbr - 1] = -1;
	while(philo.args.philo_nbr-- > 0)
	{
		philo.ready = 0;
//		printf("philo.nbr :%d\n", philo.args.philo_nbr);
		pthread_create(&philo.philosophers[philo.args.philo_nbr], NULL, thread_routine, &philo);
		while (philo.ready == 0)
		{}
	}
	free(philo.fork);
	free(philo.philosophers);
	free(philo.fork_mutex);
	sleep(1);
}