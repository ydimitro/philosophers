/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydimitro <ydimitro@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 13:46:22 by ydimitro          #+#    #+#             */
/*   Updated: 2023/05/15 09:21:26 by ydimitro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*create_philo(t_input *input, t_mutex *death, t_mutex *print)
{
	t_philo	*philosopher;

	philosopher = malloc(sizeof(t_philo));
	if (philosopher == NULL)
		return (NULL);
	philosopher->time_eat = input->time_eat;
	philosopher->time_sleep = input->time_sleep;
	philosopher->time_die = input->time_die;
	philosopher->cycles_left = input->nbr_cycles;
	philosopher->nbr_philos = input->nbr_philos;
	philosopher->a_death = death;
	philosopher->is_printing = print;
	philosopher->fork_left = NULL;
	philosopher->fork_right = NULL;
	philosopher->pid = 0;
	philosopher->is_alive = true;
	philosopher->last_meal = 0;
	philosopher->start_time = 0;
	philosopher->next = NULL;
	return (philosopher);
}

t_philo	*create_all_philos(t_input *input,
		t_mutex *death, t_mutex *print, t_mutex *cycles)
{
	int		i;
	t_philo	*storage;
	t_philo	*last;

	storage = create_philo(input, death, print);
	if (storage == NULL)
		return (NULL);
	last = storage;
	last->cycles_fullfilled = cycles;
	i = 1;
	while (i < input->nbr_philos)
	{
		last->next = create_philo(input, death, print);
		if (last->next == NULL)
		{
			destroy_all_philos(storage);
			return (NULL);
		}
		last = last->next;
		last->pid = i;
		last->cycles_fullfilled = cycles;
		i++;
	}
	return (storage);
}

void	destroy_all_philos(t_philo *to_destroy)
{
	t_philo	*current;

	current = to_destroy;
	while (current)
	{
		to_destroy = current;
		current = current->next;
		destroy_philo(to_destroy);
	}
}

void	destroy_philo(t_philo *to_destroy)
{
	free(to_destroy);
}
