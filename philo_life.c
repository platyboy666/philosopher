/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkorsako <pkorsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 16:54:17 by pkorsako          #+#    #+#             */
/*   Updated: 2023/02/10 20:25:55 by pkorsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	can_eat(t_philo *philo, int philo_id)
{
	if (!philo->fork[philo_id - 1] || !philo->fork[philo_id])
		return (0);
	else 
		return (1);
}

int	sleeping(t_philo *philo, int philo_id)
{
	printf("philo %d is sleeping\n", philo_id);
	usleep(philo->args.time_to_sleep);
	return(1);
}

int	think(t_philo *philo, int philo_id)
{
	printf("philo %d is thinking\n", philo_id);
	return (1);
}

void	die(int philo_id)
{
	printf("philo %d just died\n", philo_id);
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
	philo->ready = 1;
//	if (philo_id % 2 == 0)
//		get_ready(philo, philo_id);
	while (!philo->ready_for_start)
	{}
	while(vie == 1)
	{
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
	printf("philo %d is eating\n", philo_id);
	pthread_mutex_lock(&philo->fork_mutex[philo_id - 1]);
	pthread_mutex_lock(&philo->fork_mutex[philo_id]);
	philo->fork[philo_id - 1] = USED;
	philo->fork[philo_id] = USED;
	usleep(philo->args.time_to_eat);
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
			die(philo_id);
			return (0);
		}
	}
	return (1);
}
