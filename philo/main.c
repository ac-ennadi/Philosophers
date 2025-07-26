/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acennadi <acennadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 15:19:20 by acennadi          #+#    #+#             */
/*   Updated: 2025/07/26 14:44:43 by acennadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	int				status;
	t_configuration	data;

	status = philo_parcer(ac, av, &data);
	if (!status)
		return (0);
	printf("Test skip Parcing!, and this is the result of the data\n");
	printf("this is the result of struct: \n%d\n%d\n%d\n%d\n%d\n",
		data.number_of_philosophers, data.time_to_die, data.time_to_eat,
		data.time_to_sleep, data.number_of_times_each_philosopher_must_eat);
	return (0);
}
