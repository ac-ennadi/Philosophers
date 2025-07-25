/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acennadi <acennadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 15:19:20 by acennadi          #+#    #+#             */
/*   Updated: 2025/07/25 14:33:13 by acennadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
int ft_is_all_digit(char *str)
{
    int i;

    i = 0;
    if(!str[i])
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

int	ft_atoi(const char *str)
{
	int	res;
	int	sign;
	int	i;

	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	sign = 1;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	res = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - 48);
        if ((res * sign) > INT_MAX || (res * sign) < INT_MIN)
            return (-1);
		i++;
	}
	return (sign * res);
}

int puterror(int errnum)
{
    if (errnum == 0)
        printf("Expect: [num_philo] [t_die] [t_eat] [t_sleep] [optional: must_eat_count]\n");
    if (errnum == 1)
        printf("Error: all arguments must be positive integers\n");
    if (errnum == 2)
        printf("Error: \n");
    return 0;
}
int philo_parcer(int ac, char **av)
{
    int i;
    
    i = 1;
    // 5 or 6 args this is optional
    if (ac != 6 && ac != 5)
        return (puterror(0));
    while (i < ac)
    {
        if (!ft_is_all_digit(av[i]))
            return (puterror(1));
        i++;
    }
    return 1;
}

int main(int ac, char **av)
{
    int status;
    
    status = philo_parcer(ac ,av);
    if (!status)
        return 0;
    printf("Test skip Parcing!\n");
    return 0;
}