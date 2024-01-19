/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangylee <sangylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 17:22:05 by sangylee          #+#    #+#             */
/*   Updated: 2024/01/19 21:48:26 by sangylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	g_worldmap[24][24] = {
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};


void	leak_check(void)
{
	system("leaks cub3D");
}

int	destory_hook_event(t_screen *s)
{
	mlx_destroy_window(s->mlx, s->win);
	exit(1);
}

t_pixel	**init_pixel(int w, int h, t_img *img)
{
	t_pixel	**pixel;
	int		x;
	int		y;

	pixel = (t_pixel **)malloc(sizeof(t_pixel *) * w);
	x = -1;
	while (++x < w)
	{
		pixel[x] = (t_pixel *)malloc(sizeof(t_pixel) * h);
		y = -1;
		while (++y < h)
		{
			pixel[x][y].dist = INF;
			pixel[x][y].color = (unsigned int *)((char *)img->addr
					+ img->size_line * y + img->bits_per_pixel / 8 * x);
		}
	}
	return (pixel);
}

void	init_struct(t_screen *s)
{
	s->w = 640;
	s->h = 480;
	s->mlx = mlx_init();
	s->win = mlx_new_window(s->mlx, s->w, s->h, "cub3D");
	s->img.ptr = mlx_new_image(s->mlx, s->w, s->h);
	s->img.addr = (unsigned int *)mlx_get_data_addr(s->img.ptr,
			&(s->img.bits_per_pixel), &(s->img.size_line), &(s->img.endian));
	s->dist = (s->w / 2) * (1 / tan(FOV / 2));
	s->pixel = init_pixel(s->w, s->h, &s->img);
	//s->ray = (t_ray *)malloc(sizeof(t_ray) * s->w);
	s->origin = vec_new(12, 5);
	s->dir = vec_new(-1, 0);
	s->plane = vec_new(0, 0.66);
	s->movespeed = 0.05;
	s->rotspeed = 0.05;
	s->sin_unit = 0;
	s->cos_unit = 0;
}

int	main_loop(t_screen *s)
{
	int		idx;
	double	camerax;
	t_vec	raydir;
	int		map_x;
	int		map_y;
	double	sidedist_x;
	double	sidedist_y;
	double	deltadist_x;
	double	deltadist_y;
	double	prep_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;

	idx = 0;
	while (idx < s->w)
	{
		hit = 0;
		camerax = 2 * idx / s->w - 1;
		raydir = vec_add(s->dir, vec_mul(s->plane, camerax));
		map_x = (int)s->origin.x;
		map_y = (int)s->origin.y;
		deltadist_x = fabs(1 / raydir.x);
		deltadist_y = fabs(1 / raydir.y);
		if (raydir.x < 0)
		{
			step_x = -1;
			sidedist_x = (s->origin.x - map_x) * deltadist_x;
		}
		else
		{
			step_x = 1;
			sidedist_x = (map_x + 1 - s->origin.x) * deltadist_x;
		}
		if (raydir.y < 0)
		{
			step_y = -1;
			sidedist_y = (s->origin.y - map_y) * deltadist_y;
		}
		else
		{
			step_y = 1;
			sidedist_y = (map_y + 1 - s->origin.y) * deltadist_y;
		}
		while (hit == 0)
		{
			if (sidedist_x < sidedist_y)
			{
				map_x += step_x;
				sidedist_x += deltadist_x;
				side = 0;
			}
			else
			{
				map_y += step_y;
				sidedist_y += deltadist_y;
				side = 1;
			}
			if (g_worldmap[map_x][map_y] > 0) hit = 1;
		}
	}
	return (0);
}

int	key_hook_event(t_screen *s)
{
	return (0);
}

//LINK - Main.c
int	main(void)
{
	t_screen	s;

	atexit(leak_check);
	init_struct(&s);
	mlx_loop_hook(s.mlx, &main_loop, &s);
	mlx_hook(s.win, ON_DESTROY, 0, &destory_hook_event, &s);
	//mlx_hook(s.win, X_EVENT_KEY_PRESS, 0, &key_hook_event, &s);
	mlx_loop(s.mlx);
	return (0);
}
