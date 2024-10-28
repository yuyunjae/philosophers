/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyu <yuyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 18:56:54 by yuyu              #+#    #+#             */
/*   Updated: 2024/10/28 21:26:17 by yuyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	destroy_mutex_arr(pthread_mutex_t *fork_mutex, int last_index)
{
	int	i;

	i = -1;
	while (++i <= last_index)
	{
		pthread_mutex_destroy(&fork_mutex[i]);
	}
	free(fork_mutex);
	return (1);
}

int	make_mutex(t_env *env) // 미완 - mutex 더 추가해야함... 정리 함 해야할듯.
{
	int	i;

	i = -1;
	if (pthread_mutex_init(&env->print_mutex, NULL))
		return (1);
	if (pthread_mutex_init(&env->env_mutex, NULL))
	{
		pthread_mutex_destroy(&env->print_mutex);
		return (1);
	}
	env->fork_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
		* env->philo_num);
	if (!env->fork_mutex)
		return (1);
	while (++i < env->philo_num)
	{
		if (pthread_mutex_init(&env->fork_mutex[i], NULL))
		{
			pthread_mutex_destroy(&env->print_mutex);
			pthread_mutex_destroy(&env->env_mutex);
			return (destroy_mutex_arr(env->fork_mutex, i - 1));
		}
	}
	return(0);
}

int env_setting(int argc, char **argv, char **envp, t_env *env)
{
	memset(env, 0, sizeof(t_env));
	env->philo_num = ft_atoi(argv[1]);
	env->time_to_die = ft_atoi(argv[2]);
	env->time_to_eat = ft_atoi(argv[3]);
	env->time_to_sleep = ft_atoi(argv[4]);
	env->must_eat_count = -1;
	if (argc == 6)
		env->must_eat_count = ft_atoi(argv[5]);
	if (make_mutex(&env))
		return (1);
	return (0);
}

// int	eat_time(t_philo *philo)
// {
//		philo->eat_time = return_time
// }

int thread_do(t_philo *philo)
{
	pthread_mutex_lock(&philo->env->env_mutex);
	if (eat_time(philo))
		return (1);
	pthread_mutex_unlock(&philo->env->env_mutex);
	struct timeval a;
}

int	philo(t_env *env)
{
	t_philo *philo;
	int		i;

	i = -1;
	philo = (t_philo *)malloc(sizeof(t_philo) * (env->philo_num));
	if (!philo)
		return (1);
	memset(philo, 0, sizeof(t_philo) * env->philo_num);
	pthread_mutex_lock(&env->env_mutex);
	while(++i < env->philo_num)
	{
		philo[i].env = env;
		pthread_create(philo[i].thread_id, NULL, thread_do, &philo[i]);
	}
	pthread_mutex_unlock(&env->env_mutex);
	// thread join으로 기다려야 할듯?
	// + free해줄거 해주기.
	return (0);
}

int main(int argc, char **argv, char **envp)
{
	t_env	env;

	if (argc == 5 || argc == 6)
	{
		if (env_setting(argc, argv, envp, &env))
			return (1);
	}
	else
		return (1);
	philo(&env);
	// free_env(env);
}
