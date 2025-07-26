/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acennadi <acennadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 15:19:20 by acennadi          #+#    #+#             */
/*   Updated: 2025/07/26 16:21:29 by acennadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

void philo_init(t_configuration *data)
{
    int i;
    t_phios *fork;
    
    i = 0;
    fork = malloc(sizeof(pthread_mutex_t) * data->number_of_philosophers);
    if (!fork)
        t_clean(fork);
    while (i < data->number_of_philosophers) {
        pthread_mutex_init(&data->forks[i], NULL);
        i++;
    }
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
