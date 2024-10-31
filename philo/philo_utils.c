/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyu <yuyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 19:26:49 by yuyu              #+#    #+#             */
/*   Updated: 2024/10/31 20:27:50 by yuyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	println(t_env *env, long long cur_time, int id, char *str)
{
	if (check_end(env))
		return ;
	pthread_mutex_lock(&env->print_mutex);
	printf("%lld %d %s\n", cur_time, id, str);
	pthread_mutex_unlock(&env->print_mutex);
}

void	change_check_end(t_env *env)
{
	pthread_mutex_lock(&env->env_mutex);
	env->check_is_end = 1;
	pthread_mutex_unlock(&env->env_mutex);
}

int		check_end(t_env *env)
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

long long return_time(t_philo *philo)
{
	struct timeval	cur_time;

	if (gettimeofday(&cur_time, NULL) != 0)
		return ((long long)cur_time.tv_sec * 1000 + (long long)(cur_time.tv_usec / 1000));
	pthread_mutex_lock(&philo->env->print_mutex);
	if (!check_end(philo->env))
		write(2, "gettimeofday error!\n", 20);
	change_check_end(philo->env);
	pthread_mutex_unlock(&philo->env->print_mutex);
	return (-1);
}

int	check_die(t_philo *philo)
{
	long long	cur_time;

	cur_time = return_time(philo);
	if (check_end(philo->env))  // 이미 끝났다면
		return (1);
	if (philo->env->time_to_die < cur_time - philo->eat_time)
	{
		change_check_end(philo->env);
		println(philo->env, cur_time, philo->philo_id, "died");
		return (1);
	}
	return (0);
}
