/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_end.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyu <yuyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 18:00:46 by yuyu              #+#    #+#             */
/*   Updated: 2024/11/09 18:45:45 by yuyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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

int	check_die(t_philo *philo)
{
	long long	cur_time;

	cur_time = return_time(philo->env);
	if (check_end(philo->env))
		return (1);
	if (philo->env->time_to_die <= cur_time - philo->eat_time)
	{
		println(philo, philo->id, "died");
		return (1);
	}
	return (0);
}
