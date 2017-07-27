/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalcort <sbalcort@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/17 18:19:39 by sbalcort          #+#    #+#             */
/*   Updated: 2017/07/19 15:55:21 by sbalcort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	center_map(t_env *env)
{
	if (((WIN_X - env->map_w) / env->map_w) < (
				(WIN_Y - env->map_h) / env->map_h))
		env->pts->scale = (WIN_X - env->map_w) / (int)(env->map_w * 1.8);
	else
		env->pts->scale = (WIN_Y - env->map_h) / (int)(env->map_h * 1.8);
	env->pts->x0 = (env->map_w / 2);
	env->pts->y0 = (env->map_h / 2);
	shear(env->pts);
	env->pts->xtrans = (WIN_X / 2) - (env->pts->x0 * env->pts->scale);
	env->pts->ytrans = (WIN_Y / 2) - (env->pts->y0 * env->pts->scale);
}

void	zeroout(t_env *env)
{
	env->pts->rotx = 0;
	env->pts->roty = 0;
	env->pts->rotz = 0;
}

int		key_hook(int keycode, t_env *env)
{
	if (keycode == 53)
		exit(0);
	if (keycode == 123)
		env->pts->xtrans -= (WIN_Y / 100);
	else if (keycode == 124)
		env->pts->xtrans += (WIN_X / 100);
	else if (keycode == 125)
		env->pts->ytrans += (WIN_Y / 100);
	else if (keycode == 126)
		env->pts->ytrans -= (WIN_Y / 100);
	else if (keycode == 69)
		env->pts->scale += 1;
	else if (keycode == 78)
		env->pts->scale -= 1;
	if (keycode == 49)
		env->pts->clrtru += 1;
	if (keycode == 82)
		zeroout(env);
	if ((env->pts->clrtru % 2) == 1)
		env->pts->color = (env->pts->color * 1297) + 307;
	mlx_clear_window(env->mlx, env->window);
	draw_wireframe(env);
	return (0);
}

int		fdf_mouse_hook(int button, int x, int y, t_env *env)
{
	x = 10;
	y = 10;
	if (button == 4)
		env->pts->roty += .1;
	if (button == 5)
		env->pts->roty -= .1;
	if (button == 6)
		env->pts->rotx += .1;
	if (button == 7)
		env->pts->rotx -= .1;
	if (button == 1)
	{
		env->pts->color *= 1297;
		env->pts->color += 307;
	}
	if ((env->pts->clrtru % 2) == 1)
		env->pts->color = (env->pts->color + 43);
	center_map(env);
	mlx_clear_window(env->mlx, env->window);
	draw_wireframe(env);
	return (0);
}

int		fdf_expose_hook(t_env *env)
{
	draw_wireframe(env);
	return (0);
}
