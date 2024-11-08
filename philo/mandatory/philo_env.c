/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyu <yuyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 15:24:39 by yuyu              #+#    #+#             */
/*   Updated: 2024/11/08 18:54:41 by yuyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_mutex(t_env *env, int mutex_index)
{
	int	i;

	i = -1;
	if (mutex_index > 1)
	{
		pthread_mutex_destroy(&env->print_mutex);
		if (mutex_index > 2)
		{
			pthread_mutex_destroy(&env->env_mutex);
			if (mutex_index > 3)
			{
				pthread_mutex_destroy(&env->start_mutex);
				if (mutex_index > 4)
				{
					pthread_mutex_destroy(&env->eat_cnt_mutex);
					while (++i < mutex_index - 6)
						pthread_mutex_destroy(&env->fork_mutex[i]);
					if (env->fork_mutex)
						free(env->fork_mutex);
				}
			}
		}
	}
}

static int	make_mutex(t_env *env)
{
	int	i;

	i = -1;
	if (pthread_mutex_init(&env->print_mutex, NULL))
		return (1);
	if (pthread_mutex_init(&env->env_mutex, NULL))
		return (2);
	if (pthread_mutex_init(&env->start_mutex, NULL))
		return (3);
	if (pthread_mutex_init(&env->eat_cnt_mutex, NULL))
		return (4);
	env->fork_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* env->philo_num);
	if (!env->fork_mutex)
		return (5);
	while (++i < env->philo_num)
	{
		if (pthread_mutex_init(&env->fork_mutex[i], NULL))
			return (6 + i);
	}
	return (0);
}

int	env_setting(int argc, char **argv, char **envp, t_env *env)
{
	int	return_index;

	memset(env, 0, sizeof(t_env));
	env->philo_num = ft_atoi(argv[1]);
	env->time_to_die = ft_atoi(argv[2]);
	env->time_to_eat = ft_atoi(argv[3]);
	env->time_to_sleep = ft_atoi(argv[4]);
	env->must_eat_count = -1;
	env->must_eat_remain = env->philo_num;
	if (argc == 6)
		env->must_eat_count = ft_atoi(argv[5]);
	else
		env->must_eat_count = -1;
	env->fork_arr = (bool *)malloc(sizeof(bool) * env->philo_num);
	if (!env->fork_arr)
		return (1);
	memset(env->fork_arr, 0, sizeof(bool) * env->philo_num);
	return_index = make_mutex(env);
	if (return_index)
	{
		free(env->fork_arr);
		free_mutex(env, return_index);
		return (1);
	}
	return (0);
}
