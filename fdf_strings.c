/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_strings.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalcort <sbalcort@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/19 15:28:37 by sbalcort          #+#    #+#             */
/*   Updated: 2017/07/19 15:57:56 by sbalcort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	put_strings(t_env *env)
{
	mlx_string_put(env->mlx, env->window, 20, 20, 0xFFFFFF,
			"Use arrow keys to shift: up down left right");
	mlx_string_put(env->mlx, env->window, 20, 35, 0xFFFFFF,
			"Rotate with mouse ball: up, down, left, right");
	mlx_string_put(env->mlx, env->window, 20, 50, 0xFFFFFF,
			"Zoom: - and + on keypad");
	mlx_string_put(env->mlx, env->window, 20, 65, 0XFFFFFF,
			"Press space bar to randomize color");
	mlx_string_put(env->mlx, env->window, 20, 80, 0xFFFFFF,
			"Press 0 on kaypad to reset rotations");
}

int		filetype(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	i--;
	if (str[i] != 'f')
		return (0);
	if (str[--i] != 'd')
		return (0);
	if (str[--i] != 'f')
		return (0);
	if (str[--i] != '.')
		return (0);
	return (1);
}
