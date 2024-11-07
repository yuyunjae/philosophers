/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyu <yuyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 18:56:54 by yuyu              #+#    #+#             */
/*   Updated: 2024/11/07 22:55:17 by yuyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv, char **envp)
{
	t_env	env;

	if (argc == 5 || argc == 6)
	{
		if (env_setting(argc, argv, envp, &env))
			return (1);
		philo(&env);
		free_mutex(&env, env.philo_num + 6);
		if (env.fork_arr)
			free(env.fork_arr);
		return (0);
	}
	else
		return (1);
}