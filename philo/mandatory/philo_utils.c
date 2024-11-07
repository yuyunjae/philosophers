/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyu <yuyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 19:26:49 by yuyu              #+#    #+#             */
/*   Updated: 2024/11/07 19:23:58 by yuyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	println(t_philo *philo, int id, char *str)
{
	long long	cur_time;

	pthread_mutex_lock(&philo->env->print_mutex);
	cur_time = return_time(philo->env);
	if (check_end(philo->env))
	{
		pthread_mutex_unlock(&philo->env->print_mutex);
		return ;
	}
	printf("%lld %d %s\n", cur_time - philo->env->start_time, id, str);
	if (!strncmp(str, "is eating", 10))
		philo->eat_time = cur_time;
	else if (!strncmp(str, "died", 5))
		change_check_end(philo->env);
	pthread_mutex_unlock(&philo->env->print_mutex);
}

void	change_check_end(t_env *env)
{
	pthread_mutex_lock(&env->env_mutex);
	env->check_is_end = 1;
	pthread_mutex_unlock(&env->env_mutex);
}

int	check_end(t_env *env)
{
	pthread_mutex_lock(&env->env_mutex);
	if (env->check_is_end)
	{
		pthread_mutex_unlock(&env->env_mutex);
		return (1);
	}
	pthread_mutex_unlock(&env->env_mutex);
	return (0);
}

long long	return_time(t_env *env)
{
	struct timeval	cur_time;

	if (gettimeofday(&cur_time, NULL) == 0)
		return ((long long)cur_time.tv_sec * 1000
			+ (long long)(cur_time.tv_usec / 1000));
	change_check_end(env);
	return (-1);
}

int	check_die(t_philo *philo)
{
	long long	cur_time;

	cur_time = return_time(philo->env);
	if (check_end(philo->env))
		return (1);
	if (philo->env->time_to_die < cur_time - philo->eat_time)
	{
		println(philo, philo->id, "died");
		return (1);
	}
	return (0);
}
