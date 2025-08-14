/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_parcer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acennadi <acennadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 13:36:22 by acennadi          #+#    #+#             */
/*   Updated: 2025/08/14 11:26:25 by acennadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	puterror(int errnum, t_configuration *data)
{
	if (errnum == 0)
		printf("Expect: [nu_philo] [t_die] [t_eat] [t_sleep] [opal: mtetct]\n");
	if (errnum == 1)
		printf("Error: all arguments must be positive integers\n");
	if (errnum == 2)
		printf("Error: \n");
	if (errnum == 3)
		printf("0 1 has taken a fork\n%d 1 is died\n", data->time_to_die);
	return (0);
}

int	ft_is_all_digit(char *str)
{
	int	i;

	i = 0;
	if (!str[i])
		return (0);
	if (str[0] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	philo_parcer(int ac, char **av, t_configuration *data)
{
	int	i;

	i = 1;
	if (ac != 6 && ac != 5)
		return (puterror(0, data));
	while (i < ac)
	{
		if (!ft_is_all_digit(av[i]))
			return (puterror(1, data));
		i++;
	}
	data->number_of_philosophers = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->number_of_times_each_philosopher_must_eat = ft_atoi(av[5]);
	else
		data->number_of_times_each_philosopher_must_eat = -1;
	if (data->number_of_philosophers > 200 || data->number_of_philosophers == 0
		|| data->number_of_times_each_philosopher_must_eat == 0)
		return (puterror(2, data));
	if (data->number_of_philosophers == 1)
		return (puterror(3, data));
	return (1);
}
