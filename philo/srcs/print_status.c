/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpouchep <bpouchep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 14:45:36 by bpouchep          #+#    #+#             */
/*   Updated: 2022/03/22 14:45:37 by bpouchep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

// Print a string on the file descriptor fd
int	print_fd(char *str, int fd)
{
	int	i;

	i = 0;
	while (str[i])
		write(fd, &str[i++], 1);
	return (i);
}

// Print an integer on STDOUT
int	ft_putnbr(int n)
{
	long int	nb;
	char		*base_dec;
	int			i;

	nb = n;
	base_dec = "0123456789";
	i = 0;
	if ((nb >= 0) && (nb <= 9))
		i = write(1, &base_dec[nb], 1);
	else
	{
		ft_putnbr(nb / 10);
		i = write(1, &base_dec[nb % 10], 1);
	}
	return (i);
}

// Print the timestamp and the ID of the philosopher
void	print_timestamp(t_philo *philo)
{
	size_t	timestamp;

	timestamp = get_time() - philo->rules->init_time;
	ft_putnbr(timestamp);
	write(1, " ", 1);
	ft_putnbr(philo->id);
}

// Print timestamp X status
// Use a mutex to avoid the print of 2 status at the same time
void	print_status(t_philo *philo, int status)
{
	pthread_mutex_lock(&philo->rules->print_status);
	if (status == THREAD_FAILED)
		write(2, "Error, pthread_create() failed\n", 31);
	else if (!philo->rules->dead && !philo->rules->everybody_ate)
	{
		print_timestamp(philo);
		if (status == FORK && !philo->rules->dead)
			write(1, " has taken a fork\n", 18);
		else if (status == EAT && !philo->rules->dead)
		{
			philo->last_meal = get_time();
			philo->eat_counter++;
			write(1, " is eating\n", 11);
		}
		else if (status == SLEEP && !philo->rules->dead)
			write(1, " is sleeping\n", 13);
		else if (status == THINK && !philo->rules->dead)
			write(1, " is thinking\n", 13);
		else if (status == DIED && !philo->rules->dead)
			write(1, " died\n", 6);
	}
	pthread_mutex_unlock(&philo->rules->print_status);
}
