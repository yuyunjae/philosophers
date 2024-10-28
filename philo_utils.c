/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyu <yuyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 19:26:49 by yuyu              #+#    #+#             */
/*   Updated: 2024/10/28 21:24:16 by yuyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	println(t_env *env, long long cur_time, int id, char *str)
{
	pthread_mutex_lock(&env->print_mutex);
	printf("%lld %d %s\n", cur_time, id, str);
	pthread_mutex_unlock(&env->print_mutex);
}

long long return_time(void)
{
	struct timeval	cur_time;

	if (gettimeofday(&cur_time, NULL) != 0)
		return (cur_time.tv_sec * 1000 + (long long)(cur_time.tv_usec / 1000));
	return (-1);
}

int	check_die(t_philo *philo)
{
	long long	cur_time;

	cur_time = return_time();
	if (cur_time < 0)
		return (1);
	if (philo->env->time_to_die < cur_time - philo->eat_time)
	{
		pthread_mutex_lock(&philo->env->env_mutex);
		philo->env->check_is_end = 1;
		pthread_mutex_unlock(&philo->env->env_mutex);
		println(philo->env, cur_time, philo->philo_id, "died");
		return (1);
	}
	pthread_mutex_lock(&philo->env->env_mutex);
	if (philo->env->check_is_end)
	{
		pthread_mutex_unlock(&philo->env->env_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->env->env_mutex);
	return (0);
}
