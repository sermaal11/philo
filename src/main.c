/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergio <sergio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 13:29:31 by sergio            #+#    #+#             */
/*   Updated: 2025/01/16 11:12:38 by sergio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include <stdio.h>
#include <pthread.h>

int	main(int argc, char **argv)
{
	t_program		program;
	t_philo			*philo;
	pthread_mutex_t	*forks;

	if (ft_parsing(argc, argv, &program))
		return (1);
	if (ft_mem_alloc(&program, &philo, &forks))
		return (1);
	ft_init(&program, &philo, &forks);
	ft_thread_create(&program, forks);
	ft_destroy_all(NULL, &program, forks);
	free(philo);
	philo = NULL;
	free(forks);
	forks = NULL;
	return (0);
}
