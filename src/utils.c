/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergio <sergio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 11:39:04 by sergio            #+#    #+#             */
/*   Updated: 2025/01/15 14:35:40 by sergio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_atoi(char *str)
{
	long	result;

	result = 0;
	while (*str)
	{
		result = result * 10 + (*str++ - 48);
		if (result >= INT_MAX / 10 && (*str - '0' > 7))
			return (-1);
	}
	return (result);
}

int	ft_mem_alloc(t_program *pgm, t_philo **philo, pthread_mutex_t **forks)
{
	*philo = malloc(sizeof(t_philo) * pgm->total_philos);
	if (!*philo)
	{
		printf("Error: Failed to allocate memory in ('philo').\n");
		free(*philo);
		*philo = NULL;
		return (1);
	}
	*forks = malloc(sizeof(pthread_mutex_t) * pgm->total_philos);
	if (!*forks)
	{
		printf("Error: Failed to allocate memory in ('forks').\n");
		free(*forks);
		*forks = NULL;
		return (1);
	}
	return (0);
}

size_t	ft_get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_strlen(char *str)
{
	int	i;

	if (str == NULL)
		return (0);
	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

void	ft_print_message(char *str, t_philo *philo, int id)
{
	size_t	time;

	pthread_mutex_lock(philo->write_lock);
	time = ft_get_current_time() - philo->start_time;
	if (!ft_dead_loop(philo))
		printf("%zu %d %s\n", time, id, str);
	pthread_mutex_unlock(philo->write_lock);
}
