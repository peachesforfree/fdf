/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalcort <sbalcort@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/17 15:05:48 by sbalcort          #+#    #+#             */
/*   Updated: 2017/07/19 15:37:30 by sbalcort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void	draw_segment(t_env *env, t_drw *drw)
{
	while (1)
	{
		mlx_pixel_put(env->mlx, env->window, env->pts->x0 + env->pts->xtrans
				, env->pts->y0 + env->pts->ytrans, env->pts->color);
		if (env->pts->x0 == env->pts->x1 && env->pts->y0 == env->pts->y1)
			break ;
		drw->e2 = drw->err;
		if (drw->e2 > -(drw->dx))
		{
			drw->err -= drw->dy;
			env->pts->x0 += drw->sx;
		}
		if (drw->e2 < drw->dy)
		{
			drw->err += drw->dx;
			env->pts->y0 += drw->sy;
		}
	}
}

void	draw_line(t_env *env)
{
	t_drw	*drw;

	drw = env->pts->drw;
	drw->dx = abs(env->pts->x1 - env->pts->x0);
	drw->sx = env->pts->x0 < env->pts->x1 ? 1 : -1;
	drw->dy = abs(env->pts->y1 - env->pts->y0);
	drw->sy = env->pts->y0 < env->pts->y1 ? 1 : -1;
	drw->err = (drw->dx > drw->dy ? drw->dx : -(drw->dy)) / 2;
	draw_segment(env, drw);
}

void	set_pts_trans(int x, int y, t_env *env, int num)
{
	env->pts->x0 = (x * env->pts->scale);
	env->pts->y0 = (y * env->pts->scale);
	env->pts->z0 = (env->map[y][x] * env->pts->scale);
	if (num == 1)
	{
		env->pts->x1 = (x + 1) * env->pts->scale;
		env->pts->y1 = y * env->pts->scale;
		env->pts->z1 = (env->map[y][x + 1] * env->pts->scale);
	}
	else
	{
		env->pts->y1 = (y - 1) * env->pts->scale;
		env->pts->x1 = x * env->pts->scale;
		env->pts->z1 = (env->map[y - 1][x] * env->pts->scale);
	}
	shear(env->pts);
}

void	shear(t_pts *pts)
{
	int	x0;
	int	x1;

	x0 = pts->x0;
	x1 = pts->x1;
	pts->x0 = (x0 * (cos(pts->rotx) * cos(pts->rotz))) -
	(pts->y0 * (cos(pts->roty) * sin(pts->rotz))) +
	(pts->z0 * sin(pts->roty));
	pts->y0 = (x0 * ((sin(pts->rotx) * sin(pts->roty) * cos(pts->rotz))
	+ (cos(pts->rotx) * sin(pts->rotz))))
	+ (pts->y0 * ((sin(pts->rotz) * sin(pts->rotz) * sin(pts->roty))
	+ (cos(pts->rotx) * cos(pts->rotz))))
	- (pts->z0 * (cos(pts->roty) * sin(pts->rotx)));
	pts->x1 = (x1 * (cos(pts->rotx) * cos(pts->rotz)))
	- (pts->y1 * (cos(pts->roty) * sin(pts->rotz)))
	+ (pts->z1 * sin(pts->roty));
	pts->y1 = (x1 * ((sin(pts->rotx) * sin(pts->roty) * cos(pts->rotz))
	+ (cos(pts->rotx) * sin(pts->rotz))))
	+ (pts->y1 * ((sin(pts->rotz) * sin(pts->rotz) * sin(pts->roty))
	+ (cos(pts->rotx) * cos(pts->rotz))))
	- (pts->z1 * (cos(pts->roty) * sin(pts->rotx)));
}

void	draw_wireframe(t_env *env)
{
	int	ix;
	int	iy;

	iy = 0;
	put_strings(env);
	while (iy < env->map_h - 1)
	{
		ix = 0;
		while (ix < env->map_w)
		{
			if (ix < env->map_w - 1)
			{
				set_pts_trans(ix, iy, env, 1);
				draw_line(env);
			}
			if (iy > 0)
			{
				set_pts_trans(ix, iy, env, -1);
				draw_line(env);
			}
			ix++;
		}
		iy++;
	}
}
