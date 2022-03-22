/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_end.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpouchep <bpouchep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 14:45:10 by bpouchep          #+#    #+#             */
/*   Updated: 2022/03/22 14:45:12 by bpouchep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

// Compare the number of time each philosopher ate with
// number_of_times_each_philosopher_must_eat
int	check_eat(t_game *rules)
{
	int	philosophers_who_have_all_eat;
	int	i;

	i = 0;
	philosophers_who_have_all_eat = 0;
	pthread_mutex_lock(&rules->check_dead);
	while (i < rules->nb_philo)
	{
		if (rules->philo[i].eat_counter >= rules->must_eat)
			philosophers_who_have_all_eat++;
		i++;
	}
	pthread_mutex_unlock(&rules->check_dead);
	if (philosophers_who_have_all_eat != rules->nb_philo)
		return (0);
	else
	{
		rules->everybody_ate = 1;
		return (1);
	}
}

// If a philosopher don't eat after time_to_die, he'll die.
int	check_rip(t_game *rules)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&rules->check_dead);
	while (i < rules->nb_philo)
	{
		if (get_time() - rules->philo[i].last_meal > (size_t)rules->t_die)
		{
			print_status(&rules->philo[i], DIED);
			rules->dead = 1;
			pthread_mutex_unlock(&rules->check_dead);
			usleep(500);
			return (1);
		}
		i++;
	}
	pthread_mutex_unlock(&rules->check_dead);
	return (0);
}

// Loop ends when there is a dead,
// or when everybody has eaten number_of_times_each_philosopher_must_eat
void	check_end(t_game *rules)
{
	while (1)
	{
		if (check_rip(rules) == 1)
			break ;
		if (rules->must_eat != -1)
			if (check_eat(rules) == 1)
				break ;
	}
}
