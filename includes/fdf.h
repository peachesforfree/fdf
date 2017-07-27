/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalcort <sbalcort@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/16 19:10:34 by sbalcort          #+#    #+#             */
/*   Updated: 2017/07/19 15:51:01 by sbalcort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <stdio.h>

# include "../libs/libft/libft.h"
# include "../libs/minilibx/mlx.h"

# define WIN_X 1800
# define WIN_Y 1200
# define SCALE 10
# define ROTX 0.5
# define ROTY 0.5
# define ROTZ 0.3
# define COLOR 0xFFF457

typedef struct	s_drw
{
	int			dx;
	int			dy;
	int			sx;
	int			sy;
	int			err;
	int			e2;

}				t_drw;

typedef struct	s_pts
{
	int			x0;
	int			y0;
	int			z0;
	int			x1;
	int			y1;
	int			z1;
	int			scale;
	int			xtrans;
	int			ytrans;
	int			color;
	int			clrtru;
	float		rotx;
	float		roty;
	float		rotz;
	t_drw		*drw;
}				t_pts;

typedef struct	s_env
{
	void		*mlx;
	void		*window;
	void		*image;
	int			color;
	int			**map;
	int			map_h;
	int			map_w;
	t_pts		*pts;
}				t_env;

int				key_hook(int keycode, t_env *env);
void			reinit(t_env *env);
int				fdf_read(int fd, t_env *env);
void			draw_wireframe(t_env *env);
void			draw_line(t_env *env);
void			shear(t_pts *pts);
void			set_pts_trans(int x, int y, t_env *env, int num);
void			end_fdf(t_env *env);
int				fdf_expose_hook(t_env *env);
int				fdf_mouse_hook(int button, int x, int y, t_env *env);
void			center_map(t_env *env);
void			put_strings(t_env *env);
int				filetype(char *str);
int				usage(int ac, char **av);

#endif
