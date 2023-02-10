/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkorsako <pkorsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 15:03:48 by pkorsako          #+#    #+#             */
/*   Updated: 2023/02/10 20:35:04 by pkorsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>

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
	int				ready;
	int				ready_for_start;
	t_args			args;
	pthread_t		*philosophers;
	int				*fork;
	pthread_mutex_t	*fork_mutex;
}	t_philo;

int		ft_usleep(t_philo *philo, int philo_id);
int		eat(t_philo *philo, int philo_id);
void	*thread_routine(void *philosopher);
void	die(int philo_id);
int		think(t_philo *philo, int philo_id);
int		sleeping(t_philo *philo, int philo_id);
int		 can_eat(t_philo *philo, int philo_id);
void	get_ready(t_philo *philo, int philo_id);

#endif
