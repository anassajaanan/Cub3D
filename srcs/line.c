#include "../include/cub3d.h"



void	dda(t_params *params, t_point p1, t_point p2, int color) // Digital differential analyzer Algorithm
{
	int			i;
	t_fpoint	p;
	int			steps;
	t_point		delta;
	t_fpoint	increment;

	i = 0;
	p.x = p1.x;
	p.y = p1.y;
	delta.x = p2.x - p1.x;
	delta.y = p2.y - p1.y;
	steps = fmax(abs(delta.x), abs(delta.y));
	increment.x = delta.x / (float)steps;
	increment.y = delta.y / (float)steps;
	while (i < steps)
	{
		mlx_pixel_put(params->mlx, params->win, round(p.x), round(p.y), color);
		p.x += increment.x;
		p.y += increment.y;
		i++;
	}
}

static void	init_bresenham_params(t_point p1, t_point p2, t_point *delta, t_point *sign)
{
	delta->x = abs(p2.x - p1.x);
	delta->y = -abs(p2.y - p1.y);
	if (p1.x < p2.x)
		sign->x = 1;
	else
		sign->x = -1;
	if (p1.y < p2.y)
		sign->y = 1;
	else
		sign->y = -1;
}

static void	bresenham(t_params *params, t_point p1, t_point p2, int color) // Bresenham's line algorithm
{
	t_point	delta;
	t_point	sign;
	int		err;
	int		e2;

	init_bresenham_params(p1, p2, &delta, &sign);
	err = delta.x + delta.y;
	while (1)
	{
		mlx_pixel_put(params->mlx, params->win, p1.x, p1.y, color);
		if (p1.x == p2.x && p1.y == p2.y)
			break ;
		e2 = 2 * err;
		if (e2 >= delta.y)
		{
			err += delta.y;
			p1.x += sign.x;
		}
		if (e2 <= delta.x)
		{
			err += delta.x;
			p1.y += sign.y;
		}
	}
}

void	draw_line(t_params *params, t_point p1, t_point p2, int color)
{
	// dda(params, p1, p2, color);
	bresenham(params, p1, p2, color);
}

// draw line on the image
void	draw_line_img(t_params *params, t_point p1, t_point p2, int color)
{
	t_point	delta;
	t_point	sign;
	int		err;
	int		e2;

	init_bresenham_params(p1, p2, &delta, &sign);
	err = delta.x + delta.y;
	while (1)
	{
		// mlx_pixel_put(params->mlx, params->win, p1.x, p1.y, color);
		mlx_pixel_put_img(params->mlx, &params->window_img, p1.x, p1.y, color);
		if (p1.x == p2.x && p1.y == p2.y)
			break ;
		e2 = 2 * err;
		if (e2 >= delta.y)
		{
			err += delta.y;
			p1.x += sign.x;
		}
		if (e2 <= delta.x)
		{
			err += delta.x;
			p1.y += sign.y;
		}
	}
}