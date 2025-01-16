/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergio <sergio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 13:39:09 by sergio            #+#    #+#             */
/*   Updated: 2024/12/17 09:55:25 by sergio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	ft_check_argc_amount(int argc)
{
	if (!(argc == 5 || argc == 6))
	{
		printf("Error: Expected 5 or 6 arguments\n");
		return (1);
	}
	return (0);
}

static int	ft_check_only_numbers(char *str, int i)
{
	if (*str == '\0')
	{
		printf("Error: Argument %d is void.\n", i);
		return (1);
	}
	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
		{
			printf("Error: ('%s') has invalid character '%c'.\n", str, str[i]);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	ft_assign_and_validate(t_program *pgm, char **argv, int argc)
{
	pgm->total_philos = ft_atoi(argv[1]);
	pgm->time_to_die = ft_atoi(argv[2]);
	pgm->time_to_eat = ft_atoi(argv[3]);
	pgm->time_to_sleep = ft_atoi(argv[4]);
	pgm->meals_to_do = -1;
	if (pgm->total_philos <= 0 || pgm->time_to_die <= 0
		|| pgm->time_to_eat <= 0 || pgm->time_to_sleep <= 0)
	{
		printf("Error: argument 1 to 4 can't be = '0' or > 'INT_MAX'.\n");
		return (1);
	}
	if (argc == 6)
	{
		pgm->meals_to_do = ft_atoi(argv[5]);
		if (pgm->meals_to_do < 0)
		{
			printf("Error: argv[5] can't be > INT_MAX.\n");
			return (1);
		}
	}
	return (0);
}

int	ft_parsing(int argc, char **argv, t_program *program)
{
	int	i;

	if (ft_check_argc_amount(argc))
		return (1);
	i = 1;
	while (i < argc)
	{
		if (ft_check_only_numbers(argv[i], i))
			return (1);
		i++;
	}
	if (ft_assign_and_validate(program, argv, argc))
		return (1);
	return (0);
}
