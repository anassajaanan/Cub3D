#include "../include/cub3d.h"



void	dda(t_params *params, t_point p1, t_point p2, int color)
{
	int				i;
	t_float_point	p;
	int				steps;
	t_point			delta;
	t_float_point	increment;

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