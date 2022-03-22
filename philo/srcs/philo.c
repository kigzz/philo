/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpouchep <bpouchep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 14:45:32 by bpouchep          #+#    #+#             */
/*   Updated: 2022/03/22 14:45:33 by bpouchep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

// The philo program takes 4 (the 5th is optional) arguments :
// ./philo [nb_philo] [t_die] [t_eat] [t_sleep]
// [optional : number_of_times_each_philosopher_must_eat]
int	main(int argc, char **argv, char **envp)
{
	t_rules	rules;

	if (!*envp)
		return (0);
	if (argc == 5 || argc == 6)
	{
		if (init_rules(&rules, argv, argc))
			create_threads(&rules);
		return (0);
	}
	else
	{
		print_fd("Write something like : ./philo [nb_philo] ", 2);
		print_fd("[time_to_die] [time_to_eat] [time_to_sleep] ", 2);
		print_fd("[option : must_eat]\n", 2);
		return (-1);
	}
}
