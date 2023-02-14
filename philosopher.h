/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkorsako <pkorsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 15:03:48 by pkorsako          #+#    #+#             */
/*   Updated: 2023/02/14 04:21:03 by pkorsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <sys/time.h>

#define FREE 1
#define USED 0

typedef struct s_args
{
	int	philo_nbr;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	nbr_philo_must_eat;
}	t_args;

typedef struct s_philo
{
	long int		start_time;
	int				ready;
	int				ready_for_start;
	t_args			args;
	pthread_t		*philosophers;
	int				*fork;
	pthread_mutex_t	*fork_mutex;
	int				dead;
}	t_philo;

int		ft_usleep(t_philo *philo, int philo_id);
int		eat(t_philo *philo, int philo_id);
void	*thread_routine(void *philosopher);
void	die(t_philo *philo, int philo_id);
int		think(const t_philo *philo, int philo_id);
int		sleeping(const t_philo *philo, int philo_id);
int		can_eat(const t_philo *philo, int philo_id);
void	get_ready(t_philo *philo, int philo_id);
long int	get_time();

#endif
