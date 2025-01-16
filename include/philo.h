/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergio <sergio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 19:09:39 by sergio            #+#    #+#             */
/*   Updated: 2025/01/15 16:49:17 by sergio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <ctype.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				eating;
	int				meals_eaten;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			start_time;
	size_t			last_meal;
	int				meals_to_do;
	int				total_philos;
	int				*dead;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
}				t_philo;

typedef struct s_program
{
	t_philo			*philo;
	int				total_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_to_do;
	int				dead_flag;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
}				t_program;

// utils.c
int		ft_atoi(char *str);
int		ft_mem_alloc(t_program *pgm, t_philo **philo, pthread_mutex_t **forks);
size_t	ft_get_current_time(void);
int		ft_strlen(char *str);
void	ft_print_message(char *str, t_philo *philo, int id);

// parsing.c
int		ft_parsing(int argc, char **argv, t_program *program);

// init.c
void	ft_init(t_program *program, t_philo **philo, pthread_mutex_t **forks);

// monitor.c
void	*ft_monitor(void *pointer);
int		ft_dead_loop(t_philo *philo);

// threads.c
int		ft_thread_create(t_program *program, pthread_mutex_t *forks);
int		ft_usleep(size_t milliseconds);
void	ft_destroy_all(char *str, t_program *program, pthread_mutex_t *forks);

// routines.c
void	ft_eat(t_philo *philo);
void	ft_dream(t_philo *philo);
void	ft_think(t_philo *philo);

#endif