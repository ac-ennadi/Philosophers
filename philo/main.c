/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acennadi <acennadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 15:19:20 by acennadi          #+#    #+#             */
/*   Updated: 2025/07/26 17:01:38 by acennadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *philo_routine(void *arg)
{
    printf("a philo\n");
    return NULL;
}

void philo_init(t_configuration *data)
{
    int i;
    t_phios *philos;
    
    philos = malloc(sizeof(t_phios) * data->number_of_philosophers);
    data->forks = malloc(sizeof(pthread_mutex_t) * data->number_of_philosophers);
    if (!data->forks || !philos)
    {
        t_clean(data->forks);
        t_clean(philos);
    }
    i = 0;
    while (i < data->number_of_philosophers) {
        pthread_mutex_init(&data->forks[i], NULL);
        i++;
    }
    i = 0;
    while (i < data->number_of_philosophers) {
        philos[i].id = i;
        philos[i].config = data;
        philos[i].left_fork = &data->forks[i];
	    philos[i].right_fork = &data->forks[(i + 1) % data->number_of_philosophers];
	    pthread_create(&philos[i].thread, NULL, philo_routine, "");
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
