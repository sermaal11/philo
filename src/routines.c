/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergio <sergio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:28:20 by sergio            #+#    #+#             */
/*   Updated: 2025/01/16 11:15:19 by sergio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	ft_print_message("has taken a fork", philo, philo->id);
	if (philo->total_philos == 1)
	{
		ft_usleep(philo->time_to_die);
		pthread_mutex_unlock(philo->r_fork);
		return ;
	}
	pthread_mutex_lock(philo->l_fork);
	ft_print_message("has taken a fork", philo, philo->id);
	philo->eating = 1;
	ft_print_message("is eating", philo, philo->id);
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = ft_get_current_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meal_lock);
	ft_usleep(philo->time_to_eat);
	philo->eating = 0;
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	ft_dream(t_philo *philo)
{
	ft_print_message("is sleeping", philo, philo->id);
	ft_usleep(philo->time_to_sleep);
}

void	ft_think(t_philo *philo)
{
	ft_print_message("is thinking", philo, philo->id);
}
