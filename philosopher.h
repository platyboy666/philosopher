/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkorsako <pkorsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 15:03:48 by pkorsako          #+#    #+#             */
/*   Updated: 2023/02/09 16:07:58 by pkorsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>

int FREE = 1;
int	USED = 0;

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
	t_args			args;
	pthread_t		*philosophers;
	int				*fork;
	pthread_mutex_t	*fork_mutex;
}	t_philo;

#endif
