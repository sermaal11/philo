/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarin-a <smarin-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 11:38:17 by sergio            #+#    #+#             */
/*   Updated: 2025/01/29 10:43:15 by smarin-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_destroy_all(char *str, t_program *program, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	if (str)
	{
		write(2, str, ft_strlen(str));
		write(2, "\n", 1);
	}
	pthread_mutex_destroy(&program->write_lock);
	pthread_mutex_destroy(&program->meal_lock);
	pthread_mutex_destroy(&program->dead_lock);
	while (i < program->philo[0].total_philos)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
}

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = ft_get_current_time();
	while ((ft_get_current_time() - start) < milliseconds)
		usleep(500);
	return (0);
}

static void	*ft_philo_routine(void *pointer)
{
	t_philo	*philo;

	philo = (t_philo *)pointer;
	if (philo->id % 2 == 0)
		ft_usleep(philo->time_to_eat);
	while (!ft_dead_loop(philo))
	{
		ft_eat(philo);
		ft_dream(philo);
		ft_think(philo);
	}
	return (pointer);
}

int	ft_thread_create(t_program *program, pthread_mutex_t *forks)
{
	pthread_t	observer;
	int			i;

	if (pthread_create(&observer, NULL, &ft_monitor, program->philo) != 0)
		ft_destroy_all("Thread creation error", program, forks);
	i = 0;
	while (i < program->philo[0].total_philos)
	{
		if (pthread_create(&program->philo[i].thread, NULL, &ft_philo_routine,
				&program->philo[i]) != 0)
			ft_destroy_all("Thread creation error", program, forks);
		i++;
	}
	i = 0;
	if (pthread_join(observer, NULL) != 0)
		ft_destroy_all("Thread join error", program, forks);
	while (i < program->philo[0].total_philos)
	{
		if (pthread_join(program->philo[i].thread, NULL) != 0)
			ft_destroy_all("Thread join error", program, forks);
		i++;
	}
	return (0);
}
