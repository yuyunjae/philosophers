/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyu <yuyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 19:26:49 by yuyu              #+#    #+#             */
/*   Updated: 2024/11/09 18:02:39 by yuyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	swap_fork(int *left_fork, int *right_fork)
{
	int	temp;

	temp = *left_fork;
	*left_fork = *right_fork;
	*right_fork = temp;
}

int	ft_sleep(t_philo *philo, long long sleep_time)
{
	long long	s_time;
	long long	c_time;

	s_time = return_time(philo->env);
	while (1)
	{
		c_time = return_time(philo->env);
		if (check_die(philo))
			return (1);
		if (c_time - s_time >= sleep_time)
			break ;
		else if (c_time - s_time + 4 < sleep_time)
			usleep(2000);
		usleep(100);
	}
	return (0);
}

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
	if (!ft_strncmp(str, "died", 5))
		change_check_end(philo->env);
	pthread_mutex_unlock(&philo->env->print_mutex);
	if (!ft_strncmp(str, "is eating", 10))
		philo->eat_time = cur_time;
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
