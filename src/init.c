/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarin-a <smarin-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 13:41:59 by sergio            #+#    #+#             */
/*   Updated: 2025/01/28 13:05:05 by smarin-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	ft_init_program(t_program *program, t_philo *philo)
{
	program->dead_flag = 0;
	program->philo = philo;
	if (pthread_mutex_init(&program->write_lock, NULL))
		printf("Error: Initialize mutex write_lock failed.\n");
	if (pthread_mutex_init(&program->dead_lock, NULL))
		printf("Error: Initialize mutex dead_lock failed.\n");
	if (pthread_mutex_init(&program->meal_lock, NULL))
		printf("Error: Initialize mutex meal_lock failed.\n");
}

static void	ft_init_forks(pthread_mutex_t *forks, int total_philos)
{
	int	i;

	i = -1;
	while (++i < total_philos)
	{
		if (pthread_mutex_init(&forks[i], NULL))
			printf("Error: Initialize mutex forks failed.\n");
	}
}

static void	ft_init_philos(t_program *program, t_philo *philo,
		pthread_mutex_t *forks)
{
	int		i;
	size_t	current_time;

	i = -1;
	current_time = ft_get_current_time();
	while (++i < program->total_philos)
	{
		philo[i].id = i + 1;
		philo[i].eating = 0;
		philo[i].meals_eaten = 0;
		philo[i].time_to_die = program->time_to_die;
		philo[i].time_to_eat = program->time_to_eat;
		philo[i].time_to_sleep = program->time_to_sleep;
		philo[i].meals_to_do = program->meals_to_do;
		philo[i].total_philos = program->total_philos;
		philo[i].write_lock = &program->write_lock;
		philo[i].dead_lock = &program->dead_lock;
		philo[i].meal_lock = &program->meal_lock;
		philo[i].dead = &program->dead_flag;
		philo[i].start_time = current_time;
		philo[i].last_meal = current_time;
		philo[i].l_fork = &forks[i];
		philo[i].r_fork = &forks[(i + 1) % program->total_philos];
	}
}

void	ft_init(t_program *program, t_philo **philo, pthread_mutex_t **forks)
{
	ft_init_program(program, *philo);
	ft_init_forks(*forks, program->total_philos);
	ft_init_philos(program, *philo, *forks);
}
