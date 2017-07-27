/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalcort <sbalcort@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/16 19:08:55 by sbalcort          #+#    #+#             */
/*   Updated: 2017/07/19 15:54:23 by sbalcort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void	set_values(t_env *env)
{
	env->pts->scale = SCALE;
	env->pts->rotx = ROTX;
	env->pts->roty = ROTY;
	env->pts->rotz = ROTZ;
	env->pts->color = COLOR;
	center_map(env);
}

int		usage(int ac, char **av)
{
	ft_putstr("Usage : ");
	if (ac != 2)
		ft_putstr(av[0]);
	else if (av[1])
		ft_putstr(av[1]);
	ft_putstr(" <filename> [ case_size z_size ]\n");
	return (0);
}

int		no_file(char *str)
{
	ft_putstr("No file ");
	ft_putstr(str);
	ft_putstr("\n");
	return (0);
}

int		invalid_map(void)
{
	ft_putstr("Invalid map read. Exiting.");
	return (0);
}

int		main(int argc, char **argv)
{
	t_env	*env;
	t_pts	*pts;
	t_drw	*drw;
	int		fd;

	drw = (t_drw*)malloc(sizeof(t_drw));
	pts = (t_pts*)malloc(sizeof(t_pts));
	env = (t_env*)malloc(sizeof(t_env));
	env->pts = pts;
	pts->drw = drw;
	if (argc != 2 || !filetype(argv[1]))
		return (usage(argc, argv));
	if ((fd = open(argv[1], O_RDONLY)) < 0)
		return (no_file(argv[1]));
	if (fdf_read(fd, env) < 0)
		return (invalid_map());
	set_values(env);
	env->mlx = mlx_init();
	env->window = mlx_new_window(env->mlx, WIN_X, WIN_Y, argv[1]);
	draw_wireframe(env);
	mlx_mouse_hook(env->window, &fdf_mouse_hook, env);
	mlx_hook(env->window, 2, 0, &key_hook, env);
	mlx_expose_hook(env->window, &fdf_expose_hook, env);
	mlx_loop(env->mlx);
	return (0);
}
