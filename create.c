/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydimitro <ydimitro@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 17:36:20 by ydimitro          #+#    #+#             */
/*   Updated: 2023/05/15 08:01:36 by ydimitro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_mutex	*create_mutex(void)
{
	t_mutex	*mutex;

	mutex = malloc(sizeof(t_mutex));
	if (mutex == NULL)
		return (NULL);
	if (pthread_mutex_init(&mutex->mutex, NULL) != 0)
	{
		free(mutex);
		return (NULL);
	}
	mutex->value = false;
	return (mutex);
}

t_mutex	**create_forks(int nbr_forks)
{
	t_mutex	**forks;
	int		i;

	forks = malloc (sizeof(t_mutex *) * (nbr_forks + 1));
	if (forks == NULL)
		return (NULL);
	i = 0;
	while (i < nbr_forks)
	{
		forks[i] = create_mutex();
		if (forks[i] == NULL)
		{
			destroy_forks(forks);
			return (NULL);
		}
		i++;
	}
	forks[nbr_forks] = NULL;
	return (forks);
}

int	initialize_philosophers(t_all *out, t_input *input)
{
	out->philosophers = create_all_philos(input, out->mutex_death,
			out->mutex_print, out->mutex_cycles);
	if (!out->philosophers)
	{
		destroy_all_philos(out->philosophers);
		return (0);
	}
	return (1);
}

void	extra(t_all *out, t_input *input)
{
	out->mutex_death = NULL;
	out->forks = NULL;
	out->mutex_cycles = NULL;
	out->nbr_philosophers = input->nbr_philos;
	out->nbr_cycles = input->nbr_cycles;
	out->mutex_print = create_mutex();
	out->mutex_death = create_mutex();
	out->mutex_cycles = create_mutex();
	out->forks = create_forks(input->nbr_philos);
}

t_all	*create_all(t_input *input)
{
	t_all	*out;

	out = malloc(sizeof(t_all));
	if (out == NULL)
		return (NULL);
	extra(out, input);
	if (!out->mutex_print || !out->mutex_death
		|| !out->forks || !out->mutex_cycles)
	{
		destroy_all(out);
		return (NULL);
	}
	if (!initialize_philosophers(out, input))
	{
		destroy_all(out);
		return (NULL);
	}
	return (out);
}
