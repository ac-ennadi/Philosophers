/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acennadi <acennadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 15:19:20 by acennadi          #+#    #+#             */
/*   Updated: 2025/07/26 15:42:20 by acennadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void philo_init(t_configuration *data)
{
    t_phios *fork;
    
    fork = malloc(sizeof(pthread_mutex_t) * fork->config->number_of_philosophers);
    if (!fork)
        t_clean(fork);
}
int	main(int ac, char **av)
{
	int				status;
	t_configuration	data;

	status = philo_parcer(ac, av, &data);
	if (!status)
        return (0);
    philo_init(&data);
	return (0);
}
