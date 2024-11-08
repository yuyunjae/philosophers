/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyu <yuyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:30:09 by yuyu              #+#    #+#             */
/*   Updated: 2024/11/08 22:32:43 by yuyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
		usleep(100);
	}
	return (0);
}

static int	thread_init(t_philo *philo)
{
	pthread_mutex_lock(&philo->env->start_mutex);
	pthread_mutex_unlock(&philo->env->start_mutex);
	philo->eat_time = philo->env->start_time;
	if (philo->env->must_eat_count == 0 || check_die(philo))
		return (1);
	println(philo, philo->id, "is thinking");
	if (philo->id % 2 == 0)
	{
		usleep(500);
		ft_sleep(philo, philo->env->time_to_eat >> 1);
	}
	else if (philo->env->philo_num % 2
		&& philo->id == philo->env->philo_num)
	{
		usleep(500);
		ft_sleep(philo, philo->env->time_to_eat);
	}
	if (check_die(philo))
		return (1);
	return (0);
}

static void	free_thread(t_env *env, t_philo	*philo)
{
	int	index;

	index = -1;
	while (++index < env->philo_num)
		pthread_join(philo[index].thread_id, NULL);
}

void	*thread_do(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (thread_init(philo))
		return (0);
	while (!check_die(philo))
	{
		if (ft_eat(philo))
			return (0);
		println(philo, philo->id, "is sleeping");
		if (ft_sleep(philo, philo->env->time_to_sleep))
			return (0);
		println(philo, philo->id, "is thinking");
	}
	return (0);
}

int	philo(t_env *env)
{
	t_philo	*philo;
	int		i;

	i = -1;
	philo = (t_philo *)malloc(sizeof(t_philo) * (env->philo_num));
	if (!philo)
		return (1);
	memset(philo, 0, sizeof(t_philo) * env->philo_num);
	pthread_mutex_lock(&env->start_mutex);
	while (++i < env->philo_num)
	{
		philo[i].env = env;
		philo[i].id = i + 1;
		pthread_create(&philo[i].thread_id, NULL, thread_do, &philo[i]);
	env->start_time = return_time(env);
	}
	pthread_mutex_unlock(&env->start_mutex);
	free_thread(env, philo);
	free(philo);
	return (0);
}
