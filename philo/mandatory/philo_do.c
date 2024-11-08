/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_do.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyu <yuyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:30:46 by yuyu              #+#    #+#             */
/*   Updated: 2024/11/08 22:05:57 by yuyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	change_fork(t_philo *philo, int fork_index, bool val)
{
	pthread_mutex_lock(&philo->env->fork_mutex[fork_index]);
	philo->env->fork_arr[fork_index] = val;
	pthread_mutex_unlock(&philo->env->fork_mutex[fork_index]);
}

static int	get_one_fork(t_philo *philo, int fork_index)
{
	pthread_mutex_lock(&philo->env->fork_mutex[fork_index]);
	if (!philo->env->fork_arr[fork_index])
		philo->env->fork_arr[fork_index] = true;
	else
	{
		pthread_mutex_unlock(&philo->env->fork_mutex[fork_index]);
		return (0);
	}
	pthread_mutex_unlock(&philo->env->fork_mutex[fork_index]);
	return (1);
}

static int	get_fork(t_philo *philo, int left_fork, int right_fork)
{
	while (!get_one_fork(philo, left_fork))
	{
		if (check_die(philo))
			return (1);
		usleep(100);
	}
	println(philo, philo->id, "has taken a fork");
	while (!get_one_fork(philo, right_fork))
	{
		if (check_die(philo))
			return (1);
		usleep(100);
	}
	println(philo, philo->id, "has taken a fork");
	return (0);
}

static void	put_down_fork(t_philo *philo, int left_fork, int right_fork)
{
	change_fork(philo, right_fork, false);
	change_fork(philo, left_fork, false);
}

int	ft_eat(t_philo *philo)
{
	if (get_fork(philo, philo->id - 1, philo->id % philo->env->philo_num))
		return (1);
	if (check_die(philo))
		return (1);
	philo->eat_time = return_time(philo->env);
	println(philo, philo->id, "is eating");
	philo->eat_count++;
	if (ft_sleep(philo, philo->env->time_to_eat))
		return (1);
	if (philo->env->must_eat_count >= 0
		&& philo->env->must_eat_count == philo->eat_count)
	{
		pthread_mutex_lock(&philo->env->eat_cnt_mutex);
		philo->env->must_eat_remain--;
		if (philo->env->must_eat_remain <= 0)
			change_check_end(philo->env);
		pthread_mutex_unlock(&philo->env->eat_cnt_mutex);
	}
	put_down_fork(philo, philo->id - 1, philo->id % philo->env->philo_num);
	return (0);
}
