/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpouchep <bpouchep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 14:45:15 by bpouchep          #+#    #+#             */
/*   Updated: 2022/03/22 14:45:16 by bpouchep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

// Destroy the mutex and free the malloc
void	clean_exit(t_game *rules, pthread_t *thread_id)
{
	int	i;

	i = -1;
	while (++i < rules->nb_philo)
		pthread_mutex_destroy(&rules->philo[i].fork);
	pthread_mutex_destroy(&rules->check_dead);
	pthread_mutex_destroy(&rules->print_status);
	free(rules->philo);
	rules->philo = NULL;
	if (thread_id)
	{
		free(thread_id);
		thread_id = NULL;
	}
	usleep(1000);
	return ;
}
