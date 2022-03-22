/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpouchep <bpouchep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 14:45:40 by bpouchep          #+#    #+#             */
/*   Updated: 2022/03/22 14:45:41 by bpouchep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

// A custom usleep function
void	custom_sleep(t_game *rules, size_t time)
{
	size_t	start_time;

	if (!rules->dead && !rules->everybody_ate)
	{
		start_time = get_time();
		while (get_time() < start_time + time)
			usleep(500);
	}
	return ;
}

// Take the forks when they are available and wait t_to_eat,
// Print status and use mutex
void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork);
	print_status(philo, FORK);
	if (philo->rules->nb_philo == 1)
	{
		custom_sleep(philo->rules, philo->rules->t_die);
		print_status(philo, DIED);
		pthread_mutex_unlock(&philo->fork);
		philo->rules->dead = 1;
		return ;
	}
	pthread_mutex_lock(&philo->r_philo->fork);
	print_status(philo, FORK);
	print_status(philo, EAT);
	custom_sleep(philo->rules, philo->rules->t_eat);
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->r_philo->fork);
	return ;
}

// The function called by the threads, will not end until there is a dead
// or if everybody eaten number_of_times_each_philosopher_must_eat
void	*routine(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	if (philo->id % 2 == 0)
		custom_sleep(philo->rules, 100);
	while (!philo->rules->dead && !philo->rules->everybody_ate)
	{
		eat(philo);
		print_status(philo, SLEEP);
		custom_sleep(philo->rules, philo->rules->t_sleep);
		print_status(philo, THINK);
	}
	return (NULL);
}
