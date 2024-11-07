/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_do.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyu <yuyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:30:46 by yuyu              #+#    #+#             */
/*   Updated: 2024/11/07 23:16:37 by yuyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_sleep(t_philo *philo, long long sleep_time)
{
	long long	s_time;

	s_time = return_time(philo->env);
	if (check_die(philo))
		return (1);
	usleep(sleep_time * 800);
	while (s_time + sleep_time >= return_time(philo->env))
	{
		if (check_die(philo))
			return (1);
		usleep(100);
	}
	return (0);
}

static int	get_fork(t_philo *philo, int left_fork, int right_fork)
{
	pthread_mutex_lock(&philo->env->fork_mutex[left_fork]);
	if (!philo->env->fork_arr[left_fork])
		philo->env->fork_arr[left_fork] = true;
	else
	{
		pthread_mutex_unlock(&philo->env->fork_mutex[left_fork]);
		return (1);
	}
	pthread_mutex_unlock(&philo->env->fork_mutex[left_fork]);
	pthread_mutex_lock(&philo->env->fork_mutex[right_fork]);
	if (!philo->env->fork_arr[right_fork])
		philo->env->fork_arr[right_fork] = true;
	else
	{
		pthread_mutex_unlock(&philo->env->fork_mutex[right_fork]);
		pthread_mutex_lock(&philo->env->fork_mutex[left_fork]);
		philo->env->fork_arr[left_fork] = false;
		pthread_mutex_unlock(&philo->env->fork_mutex[left_fork]);
		return (1);
	}
	pthread_mutex_unlock(&philo->env->fork_mutex[right_fork]);
	println(philo, philo->id, "has taken a fork");
	println(philo, philo->id, "has taken a fork");
	return (0);
}

static void	put_down_fork(t_philo *philo, int left_fork, int right_fork)
{
	pthread_mutex_lock(&philo->env->fork_mutex[left_fork]);
	philo->env->fork_arr[left_fork] = false;
	pthread_mutex_unlock(&philo->env->fork_mutex[left_fork]);
	pthread_mutex_lock(&philo->env->fork_mutex[right_fork]);
	philo->env->fork_arr[right_fork] = false;
	pthread_mutex_unlock(&philo->env->fork_mutex[right_fork]);
}

int	ft_eat(t_philo *philo)
{
	if (get_fork(philo, philo->id - 1, philo->id % philo->env->philo_num))
	{
		usleep(100);
		return (1);
	}
	if (check_die(philo))
		return (1);
	philo->eat_time = return_time(philo->env);
	println(philo, philo->id, "is eating");
	// must eat check도 넣어야할 ㄷ스...
	if (ft_sleep(philo, philo->env->time_to_eat))
		return (1);
	put_down_fork(philo, philo->id - 1, philo->id % philo->env->philo_num);
	return (check_die(philo));
}
