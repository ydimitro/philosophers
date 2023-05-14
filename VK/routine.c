/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydimitro <ydimitro@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 13:47:19 by ydimitro          #+#    #+#             */
/*   Updated: 2023/05/14 23:50:55 by ydimitro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

void	set_the_table(t_all *all)
{
	int count;
	t_philo	*philosopher;
	
	count = 0;
	philosopher = all->philosophers;
	while(all->forks[count + 1])
	{
		philosopher->fork_left = all->forks[count];
		philosopher->fork_right = all->forks[count + 1];
		count++;
		philosopher = philosopher->next;
	}
	philosopher->fork_left = all->forks[count];
	philosopher->fork_right = all->forks[0];
}

//irragularities with time, reducing the time error to 50 us
static void eat_or_sleep(long long start_time, int waiting, t_philo* philosopher){
	long long current_time;

	current_time = start_time;
	while(current_time - start_time < waiting)
	{
		usleep(50);
		current_time = timestamp_in_ms();
		if(!dead_or_alive(philosopher))
			break;
	}
	if (philosopher->is_alive)
		philosopher->is_alive = true;
}

bool	dead_or_alive(t_philo* philosopher)
{
	long long	current_time;
	bool		died;
	
	pthread_mutex_lock(&(philosopher->a_death->mutex));
	died = philosopher->a_death->value;
	pthread_mutex_unlock(&(philosopher->a_death->mutex));
	if(died)
		philosopher->is_alive = false;
	if(!philosopher->is_alive)
		return false;
	current_time = timestamp_in_ms();
	if(current_time - philosopher->last_meal >= philosopher->time_die)
	{
		philosopher->is_alive = false;
		pthread_mutex_lock(&(philosopher->a_death->mutex));
		died = philosopher->a_death->value;
		philosopher->a_death->value = true;
		pthread_mutex_unlock(&(philosopher->a_death->mutex));
		if (died == false)
			print_death(philosopher, current_time);
		return false;
	}
	return true;
}

void check_fork(t_mutex *fork, bool *check, t_philo *philosopher)
{
	pthread_mutex_lock(&(fork->mutex));
	if (fork->value == false)
	{
		*check = true;
		fork->value = true;
		print_activity(philosopher, timestamp_in_ms(), " has taken a fork");
	}
	pthread_mutex_unlock(&(fork->mutex));
}

void pick_up_forks(t_philo *philosopher)
{
	bool	lcheck;
	bool	rcheck;
	
	lcheck = false;
	rcheck = false;
	while ((lcheck == false || rcheck == false ))
	{
		check_fork(philosopher->fork_left, &lcheck, philosopher);
		check_fork(philosopher->fork_right, &rcheck, philosopher);
		if (dead_or_alive(philosopher) == false)
			break;
	}
}

void put_down_forks(t_philo *philosopher)
{
	pthread_mutex_lock(&(philosopher->fork_left->mutex));
	philosopher->fork_left->value = false;
	pthread_mutex_unlock(&(philosopher->fork_left->mutex));
			
	pthread_mutex_lock(&(philosopher->fork_right->mutex));
	philosopher->fork_right->value = false;
	pthread_mutex_unlock(&(philosopher->fork_right->mutex));
}

void eat(t_philo *philosopher)
{
	long long	current_time;
	
	pick_up_forks(philosopher);
	current_time = timestamp_in_ms();
	print_activity(philosopher, current_time, " is eating");
	philosopher->last_meal = current_time;
	eat_or_sleep(current_time, philosopher->time_eat, philosopher);
	put_down_forks(philosopher);
	philosopher->cycles_left--;
	if (philosopher->cycles_left == 0)
	{
		pthread_mutex_lock(&(philosopher->cycles_fullfilled->mutex));
		philosopher->cycles_fullfilled->value++;
		if (philosopher->cycles_fullfilled->value == philosopher->nbr_philos)
		{
			pthread_mutex_lock(&(philosopher->a_death->mutex));
			philosopher->a_death->value = true;
			pthread_mutex_unlock(&(philosopher->a_death->mutex));
		}
		pthread_mutex_unlock(&(philosopher->cycles_fullfilled->mutex));
	}
}

void *routine(void* philo)
{
	long long	current_time;
	t_philo		*philosopher;
	
	philosopher = (t_philo*) philo;
	current_time = timestamp_in_ms();
	print_activity(philosopher, current_time, " is thinking");
	if (philosopher->pid % 2 == 1)
		usleep(5000);
	while(dead_or_alive(philosopher))
	{
		eat(philosopher);
		if (!philosopher->is_alive)
			return (NULL);
		current_time = timestamp_in_ms();
		print_activity(philosopher, current_time, " is sleeping");
		eat_or_sleep(current_time, philosopher->time_sleep, philosopher);
		current_time = timestamp_in_ms();
		print_activity(philosopher, current_time, " is thinking");
	}
	return (NULL);
}
