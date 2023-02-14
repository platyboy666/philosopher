/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkorsako <pkorsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 16:54:17 by pkorsako          #+#    #+#             */
/*   Updated: 2023/02/14 04:49:05 by pkorsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	can_eat(const t_philo *philo, int philo_id)
{
	pthread_mutex_lock(&philo->fork_mutex[philo_id - 1]);
	pthread_mutex_lock(&philo->fork_mutex[philo_id]);
	if (!philo->fork[philo_id - 1] || !philo->fork[philo_id])
	{
		pthread_mutex_unlock(&philo->fork_mutex[philo_id -1]);
		pthread_mutex_unlock(&philo->fork_mutex[philo_id]);
		return (0);
	}
	else
	{
		pthread_mutex_unlock(&philo->fork_mutex[philo_id -1]);
		pthread_mutex_unlock(&philo->fork_mutex[philo_id]);
		return (1);
	}
}

void	just_print(const t_philo *philo, int philo_id, char *action)
{
	printf("%ld philo %d %s\n", (get_time() - philo->start_time), philo_id, action);
}

int	sleeping(const t_philo *philo, int philo_id)
{
	
	printf("at %ld philo %d is sleeping\n", (get_time() - philo->start_time), philo_id);
	usleep(philo->args.time_to_sleep);
	return(1);
}

int	think(const t_philo *philo, int philo_id)
{
//	printf("get time :%ld\tstart time :%ld\n", get_time(), philo->start_time);
	printf("at %ld philo %d is thinking\n", (get_time() - philo->start_time), philo_id);
	return (1);
}

void	die(t_philo *philo, int philo_id)
{
	just_print(philo, philo_id, "just died");
//	printf("at %ld philo %d just died\n", (get_time() - philo->start_time), philo_id);
	pthread_mutex_lock(&philo->fork_mutex[philo->args.philo_nbr]);
	philo->dead = 1;
	pthread_mutex_unlock(&philo->fork_mutex[philo->args.philo_nbr]);
//	exit (1);
}

void	*thread_routine(void *philosopher)
{
	t_philo	*philo = (t_philo *)philosopher;
	int philo_id = philo->args.philo_nbr;
	int	vie;
	int how_much_ate;
	
	how_much_ate = 1;
	vie = 1;
	printf("philo_id :%d\n", philo_id);
	pthread_mutex_lock(&philo->fork_mutex[philo->args.philo_nbr]);
	philo->ready = 1;
	pthread_mutex_unlock(&philo->fork_mutex[philo->args.philo_nbr]);
	while (1)
	{
		pthread_mutex_lock(&philo->fork_mutex[0]);
		if (philo->ready_for_start)
		{
			pthread_mutex_unlock(&philo->fork_mutex[0]);
			break;	
		}
		pthread_mutex_unlock(&philo->fork_mutex[0]);
	}
	while(vie == 1)
	{
		if (philo_id % 2 == 0 && how_much_ate == 1)
			usleep(10);
		eat(philo, philo_id);
		if (how_much_ate++ == philo->args.nbr_philo_must_eat)
			return (NULL);
		sleeping(philo, philo_id);
		think(philo, philo_id);
		vie = ft_usleep(philo, philo_id);
	}
	return (NULL);
}

int	eat(t_philo *philo, int philo_id)
{
	pthread_mutex_lock(&philo->fork_mutex[philo_id - 1]);
	pthread_mutex_lock(&philo->fork_mutex[philo_id]);
	philo->fork[philo_id - 1] = USED;
	philo->fork[philo_id] = USED;
	usleep(philo->args.time_to_eat);
//	just_print(philo, philo_id, "is eating");
	printf("id is :%d\t philo nbr is :%d\n", philo_id, philo->args.philo_nbr);
	pthread_mutex_lock(&philo->fork_mutex[philo->args.philo_nbr]);
	printf("at %ld philo %d is eating\n", (get_time() - philo->start_time), philo_id);
	pthread_mutex_unlock(&philo->fork_mutex[philo->args.philo_nbr]);
	philo->fork[philo_id - 1] = FREE;
	philo->fork[philo_id] = FREE;
	pthread_mutex_unlock(&philo->fork_mutex[philo_id - 1]);
	pthread_mutex_unlock(&philo->fork_mutex[philo_id]);
	return (1);
}

int	ft_usleep(t_philo *philo, int philo_id)
{
	int time;
	int try;

	try = 0;
	time = philo->args.time_to_die % 5;
	while (!can_eat(philo, philo_id))
	{
		usleep(time);
		if (try ++ == 5)
		{
			die(philo, philo_id);
			return (0);
		}
	}
	return (1);
}
