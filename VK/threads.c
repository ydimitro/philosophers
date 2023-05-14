/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydimitro <ydimitro@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 18:21:10 by ydimitro          #+#    #+#             */
/*   Updated: 2023/05/14 23:47:52 by ydimitro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

//wait and join them together to main thread
static void join_threats(pthread_t *threats, int i)
{
	while(i >= 0)
	{
		pthread_join(threats[i], NULL);
		i--;
	}
	free(threats);
}

void	start_threads(t_all *all)
{
	pthread_t	*threats;
	t_philo		*philosopher;
	int			i;
	long long	time;
	
	philosopher = all->philosophers;
	threats = malloc(sizeof(pthread_t) * all->nbr_philosophers);
	if(threats == NULL)
		return ;
	time = timestamp_in_ms();
	i = 0;
	while(philosopher)
	{
		philosopher->last_meal = time;
		philosopher->start_time	= time;
		//save, attributes, call routine, give the routine a philo
		//death==stop
		if(pthread_create(&threats[i], NULL, &routine, philosopher) != 0)
		{
			pthread_mutex_lock(&(all->mutex_death->mutex)); //locked the mutex, everybody else has to wait
			all->mutex_death->value = true;
			pthread_mutex_unlock(&(all->mutex_death->mutex));
			break;
		}
		philosopher = philosopher->next;
		i++;
	}
	if (philosopher == NULL)
		i--;
	join_threats(threats, i);
}

bool wait_for_mutex(t_mutex *mutex, t_mutex *death)
{
	bool	check_death;
	
	check_death = true;
	while(check_death)
	{
		//check until it is not printing and print yourself
		pthread_mutex_lock(&(mutex->mutex));
		if(mutex->value == false)
		{
			mutex->value = true;
			pthread_mutex_unlock(&(mutex->mutex));
			break;
		}
		pthread_mutex_unlock(&(mutex->mutex));
		pthread_mutex_lock(&(death->mutex));
		check_death = death->value;
		pthread_mutex_unlock(&(death->mutex));
	}
	return check_death;
}
