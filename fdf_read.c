/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalcort <sbalcort@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/17 15:20:15 by sbalcort          #+#    #+#             */
/*   Updated: 2017/07/19 14:07:14 by sbalcort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		count_num(char *content)
{
	int i;
	int	num_cnt;

	i = 0;
	num_cnt = 0;
	while (content[i] != '\n')
	{
		while (content[i] == ' ')
			i++;
		if (content[i] == '-')
			i++;
		if (ft_isdigit(content[i]))
			num_cnt++;
		while (ft_isdigit(content[i]))
			i++;
		if (content[i] == ',')
		{
			while (content[i] != ' ' && content[i] != '\n' && content[i] != '-')
				i++;
		}
	}
	return (num_cnt);
}

int		count_new(char *content)
{
	int i;
	int newln;

	newln = 0;
	i = 0;
	while (content[i])
	{
		if (content[i] == '\n' || content[i] == '\0')
			newln++;
		i++;
	}
	return (newln);
}

int		generate_num_arry(t_env *env, char *content)
{
	int	i;
	int	iy;
	int	ix;

	i = 0;
	ix = 0;
	iy = 0;
	while (content[i])
	{
		while (iy < env->map_h)
		{
			while (ix < env->map_w)
			{
				while (ft_isspace(&content[i]))
					i++;
				env->map[iy][ix++] = ft_atoi(&content[i]);
				while (ft_isdigit(content[i]) || content[i] == '-')
					i++;
			}
			ix = 0;
			iy++;
		}
		i++;
	}
	return (0);
}

int		fdf_read(int fd, t_env *env)
{
	char	*content;
	int		i;

	content = (char*)malloc(sizeof(char) * 1);
	i = 0;
	if (!(content = ft_read_alloc(fd)))
		return (-1);
	env->map_h = count_new(content);
	if (env->map_h < 0)
		return (-1);
	env->map_w = count_num(content);
	env->map = ft_2dintarray(env->map_w, env->map_h);
	generate_num_arry(env, content);
	return (0);
}
