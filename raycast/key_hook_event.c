/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook_event.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangylee <sangylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 19:17:34 by sangylee          #+#    #+#             */
/*   Updated: 2024/03/10 15:34:55 by sangylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

extern int	g_worldmap[24][24];

static void	move_front_back(int key, t_screen *s)
{
	if (key == KEY_W)
	{
		if (!g_worldmap[
				(int)(s->pos.x + s->dir.x * s->movespeed)][(int)(s->pos.y)])
			s->pos.x += s->dir.x * s->movespeed;
		if (!g_worldmap[
				(int)(s->pos.x)][(int)(s->pos.y + s->dir.y * s->movespeed)])
			s->pos.y += s->dir.y * s->movespeed;
	}
	else if (key == KEY_S)
	{
		if (!g_worldmap[
				(int)(s->pos.x - s->dir.x * s->movespeed)][(int)(s->pos.y)])
			s->pos.x -= s->dir.x * s->movespeed;
		if (!g_worldmap[
				(int)(s->pos.x)][(int)(s->pos.y - s->dir.y * s->movespeed)])
			s->pos.y -= s->dir.y * s->movespeed;
	}
}

static void	move_left_right(int key, t_screen *s)
{
	if (key == KEY_D)
	{
		if (!g_worldmap[
				(int)(s->pos.x + s->plane.x * s->movespeed)][(int)(s->pos.y)])
			s->pos.x += s->plane.x * s->movespeed;
		if (!g_worldmap[
				(int)(s->pos.x)][(int)(s->pos.y + s->plane.y * s->movespeed)])
			s->pos.y += s->plane.y * s->movespeed;
	}
	else if (key == KEY_A)
	{
		if (!g_worldmap[
				(int)(s->pos.x - s->plane.x * s->movespeed)][(int)(s->pos.y)])
			s->pos.x -= s->plane.x * s->movespeed;
		if (!g_worldmap[
				(int)(s->pos.x)][(int)(s->pos.y - s->plane.y * s->movespeed)])
			s->pos.y -= s->plane.y * s->movespeed;
	}
}

static void	rot_left_right(int key, t_screen *s)
{
	if (key == KEY_AR_R)
	{
		s->dir = vec_rot(s->dir, -s->rotspeed);
		s->plane = vec_rot(s->plane, -s->rotspeed);
	}
	if (key == KEY_AR_L)
	{
		s->dir = vec_rot(s->dir, s->rotspeed);
		s->plane = vec_rot(s->plane, s->rotspeed);
	}
}

int	key_press(int key, t_screen *s)
{
	if (key == KEY_W)
		s->move.key_w = 1;
	if (key == KEY_S)
		s->move.key_s = 1;
	if (key == KEY_A)
		s->move.key_a = 1;
	if (key == KEY_D)
		s->move.key_d = 1;
	if (key == KEY_AR_R)
		s->move.key_arr_r = 1;
	if (key == KEY_AR_L)
		s->move.key_arr_l = 1;
	if (key == KEY_ESC || key == 65307)
		exit (0);
	return (0);
}

int	key_release(int key, t_screen *s)
{
	if (key == KEY_W)
		s->move.key_w = 0;
	if (key == KEY_S)
		s->move.key_s = 0;
	if (key == KEY_A)
		s->move.key_a = 0;
	if (key == KEY_D)
		s->move.key_d = 0;
	if (key == KEY_AR_R)
		s->move.key_arr_r = 0;
	if (key == KEY_AR_L)
		s->move.key_arr_l = 0;
	if (key == KEY_ESC || key == 65307)
		exit (0);
	return (0);
}

int	key_hook_event(int key, t_screen *s)
{
	if (key == KEY_W)
		move_front_back(key, s);
	if (key == KEY_S)
		move_front_back(key, s);
	if (key == KEY_A)
		move_left_right(key, s);
	if (key == KEY_D)
		move_left_right(key, s);
	if (key == KEY_AR_R)
		rot_left_right(key, s);
	if (key == KEY_AR_L)
		rot_left_right(key, s);
	if (key == KEY_ESC || key == 65307)
		destory_hook_event(s);
	mlx_clear_window(s->mlx, s->win);
	main_loop(s);
	return (0);
}

int	destory_hook_event(t_screen *s)
{
	mlx_destroy_window(s->mlx, s->win);
	exit(0);
}
