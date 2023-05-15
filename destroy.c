/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydimitro <ydimitro@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 17:36:17 by ydimitro          #+#    #+#             */
/*   Updated: 2023/05/15 09:20:20 by ydimitro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutex(t_mutex *mutex)
{
	pthread_mutex_destroy(&mutex->mutex);
	free(mutex);
}

void	destroy_forks(t_mutex **forks)
{
	int	i;

	i = 0;
	while (forks[i])
	{
		destroy_mutex(forks[i]);
		i++;
	}
	free(forks);
}

void	destroy_all(t_all *to_destroy)
{
	if (to_destroy->mutex_death)
		destroy_mutex(to_destroy->mutex_death);
	if (to_destroy->mutex_print)
		destroy_mutex(to_destroy->mutex_print);
	if (to_destroy->forks)
		destroy_forks(to_destroy->forks);
	if (to_destroy->mutex_cycles)
		destroy_mutex(to_destroy->mutex_cycles);
	if (to_destroy->philosophers)
		destroy_all_philos(to_destroy->philosophers);
	free(to_destroy);
}
