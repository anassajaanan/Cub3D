#include "../include/cub3d.h"

#define WIN_WIDTH 1024
#define WIN_HEIGHT 512
#define PLAYER_SIZE 20
#define MOVE_SPEED 30
#define MAP_COLS 8
#define MAP_ROWS 8
#define TAIL_SIZE 64
#define pi 3.14159265358
#define X 50
#define DR 0.0174532925

#define P2 pi / 2
#define P3 3 * pi / 2




int		map[] = {
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 0, 1, 0, 0, 0, 0, 1,
	1, 0, 1, 0, 0, 0, 0, 1,
	1, 0, 1, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 1, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 1,
	1, 1, 1, 1, 1, 1, 1, 1
};

typedef struct s_params
{
	void	*mlx;
	void	*win;
	float		player_x;
	float		player_y;
	float		player_dx;
	float		player_dy;
	float		player_a;

}				t_params;

void clear_player_position(t_params *params);
void	draw_line(t_params *params, int color);
void	delete_rays(t_params *params);

int	handle_keypress(int keycode, t_params *params)
{
	if (keycode == 53)
		exit(0);
	if (keycode == 13)
	{
		draw_line(params, 0x000000);
		// delete_rays(params);
		clear_player_position(params);
		// params->player_y -= MOVE_SPEED;
		params->player_x += params->player_dx;
		params->player_y += params->player_dy;
	}
	else if (keycode == 0)
	{
		draw_line(params, 0x000000);
		// delete_rays(params);
		clear_player_position(params);
		// params->player_x -= MOVE_SPEED;
		params->player_a -= 0.1;
		if (params->player_a < 0)
			params->player_a += 2 * pi;
		params->player_dx = cos(params->player_a) * X;
		params->player_dy = sin(params->player_a) * X;
	}
	else if (keycode == 1)
	{
		draw_line(params, 0x000000);
		// delete_rays(params);
		clear_player_position(params);
		// params->player_y += MOVE_SPEED;
		params->player_x -= params->player_dx;
		params->player_y -= params->player_dy;
	}
	else if (keycode == 2)
	{
		draw_line(params, 0x000000);
		// delete_rays(params);
		clear_player_position(params);
		// params->player_x += MOVE_SPEED;
		params->player_a += 0.1;
		if (params->player_a > 2 * pi)
			params->player_a -= 2 * pi;
		params->player_dx = cos(params->player_a) * X;
		params->player_dy = sin(params->player_a) * X;
	}
	return (0);
}

void	draw_player(t_params *params)
{
	for (int i = 0; i < PLAYER_SIZE; i++)
	{
		for (int j = 0; j < PLAYER_SIZE; j++)
		{
			mlx_pixel_put(params->mlx, params->win, params->player_x + i, params->player_y + j, 0xFFFF00);
		}
	}
}

void	draw_map_tail(t_params *params, int col, int row)
{
	int x, y;


	x = col * TAIL_SIZE;
	y = row * TAIL_SIZE;
	for (int i = 0; i < TAIL_SIZE - 1; i++)
	{
		for (int j = 0; j < TAIL_SIZE - 1; j++)
		{
			mlx_pixel_put(params->mlx, params->win, x + i, y + j, 0xFFFFFF);
		}
	}
}

void	draw_map(t_params *params)
{
	int i, j;
	for (i = 0; i < MAP_ROWS; i++)
	{
		for (j = 0; j < MAP_COLS; j++)
		{
			if (map[i * MAP_ROWS + j] == 1)
			{
				draw_map_tail(params, j, i);
			}
		}
	}
}

void clear_player_position(t_params *params)
{
	for (int i = 0; i < PLAYER_SIZE; i++)
    {
        for (int j = 0; j < PLAYER_SIZE; j++)
        {
            mlx_pixel_put(params->mlx, params->win, params->player_x + i, params->player_y + j, 0x000000);
        }
    }
}

void	draw_line(t_params *params, int color)
{
	int	x0 = params->player_x + PLAYER_SIZE / 2;
	int	y0 = params->player_y + PLAYER_SIZE / 2;
	int	x1 = params->player_x + params->player_dx;
	int	y1 = params->player_y + params->player_dy;

	int	dX = abs(x1 - x0);
	int	sX = x0 < x1 ? 1 : -1;
	int	dY = -abs(y1 - y0);
	int	sY = y0 < y1 ? 1 : -1;
	int	err = dX + dY;
	int	e2;

	while (x0 != x1 || y0 != y1)
	{
		mlx_pixel_put(params->mlx, params->win, x0, y0, color); // Set the pixel

		e2 = 2 * err;
		if (e2 >= dY)
		{
			err += dY;
			x0 += sX;
		}
		if (e2 <= dX)
		{
			err += dX;
			y0 += sY;
		}
	}
}

void draw_line1(void *mlx, void *win, int beginX, int beginY, int endX, int endY, int color)
{
	double deltaX = endX - beginX;
	double deltaY = endY - beginY;
	int pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));
	deltaX /= pixels;
	deltaY /= pixels;
	double pixelX = beginX;
	double pixelY = beginY;
	while (pixels)
	{
		mlx_pixel_put(mlx, win, pixelX, pixelY, color);
		pixelX += deltaX;
		pixelY += deltaY;
		--pixels;
	}
}

float dist(float ax, float ay, float bx, float by, float ang)
{
	(void)ang;
	return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}

void	draw_rays(t_params *params)
{
	int	r, mx, my, mp, dof;
	float rx, ry, ra, xo, yo, disT;
	int wall_color;
	
	ra = params->player_a - DR * 30;
	if (ra < 0)
		ra += 2 * pi;
	if (ra > 2 * pi)
		ra -= 2 * pi;
	for (r = 0; r < 30; r++)
	{
		// HORIZONTAL RAY-GRID INTERSECTION CODE
		dof = 0;
		float disH = 1000000, hx = params->player_x, hy = params->player_y;
		float aTan = -1 / tan(ra);
		if (ra > pi)
		{
			ry = (((int)params->player_y >> 6) << 6) - 0.0001;
			rx = (params->player_y - ry) * aTan + params->player_x;
			yo = -64;
			xo = -yo * aTan;
		}
		if (ra < pi)
		{
			ry = (((int)params->player_y >> 6) << 6) + 64;
			rx = (params->player_y - ry) * aTan + params->player_x;
			yo = 64;
			xo = -yo * aTan;
		}
		if (ra == 0 || ra == pi)
		{
			rx = params->player_x;
			ry = params->player_y;
			dof = 8;
		}
		while (dof < 8)
		{
			mx = (int)(rx) >> 6;
			my = (int)(ry) >> 6;
			mp = my * MAP_ROWS + mx;
			if (mp > 0 && mp < MAP_ROWS * MAP_COLS && map[mp] == 1)
			{
				dof = 8;
				hx = rx;
				hy = ry;
				disH = dist(params->player_x, params->player_y, hx, hy, ra); 
			}
			else
			{
				rx += xo;
				ry += yo;
				dof += 1;
			}
		}
		// draw_line1(params->mlx, params->win, params->player_x, params->player_y, rx, ry, 0x008000);

		// VERTICAL RAY-GRID INTERSECTION CODE
		dof = 0;
		float disV = 1000000, vx = params->player_x, vy = params->player_y;
		float nTan = -tan(ra);
		if (ra > P2 && ra < P3) // looking left
		{
			rx = (((int)params->player_x >> 6) << 6) - 0.0001;
			ry = (params->player_x - rx) * nTan + params->player_y;
			xo = -64;
			yo = -xo * nTan;
		}
		if (ra < P2 || ra > P3) // looking right
		{
			rx = (((int)params->player_x >> 6) << 6) + 64;
			ry = (params->player_x - rx) * nTan + params->player_y;
			xo = 64;
			yo = -xo * nTan;
		}
		if (ra == 0 || ra == pi)
		{
			rx = params->player_x;
			ry = params->player_y;
			dof = 8;
		}
		while (dof < 8)
		{
			mx = (int)(rx) >> 6;
			my = (int)(ry) >> 6;
			mp = my * MAP_ROWS + mx;
			if (mp > 0 && mp < MAP_ROWS * MAP_COLS && map[mp] == 1)
			{
				dof = 8;
				vx = rx;
				vy = ry;
				disV = dist(params->player_x, params->player_y, vx, vy, ra);
			}
			else
			{
				rx += xo;
				ry += yo;
				dof += 1;
			}
		}
		if (disV < disH)
		{
			rx = vx;
			ry = vy;
			disT = disV;
			wall_color = 0xE60000;
		}
		if (disH < disV)
		{
			rx = hx;
			ry = hy;
			disT = disH;
			wall_color = 0xb2FF00;
		}
		draw_line1(params->mlx, params->win, params->player_x + PLAYER_SIZE / 2, params->player_y + PLAYER_SIZE / 2, rx, ry, 0xFF0000);
		
		
		// // Draw 3D walls
		// float lineH = (TAIL_SIZE * 320) / disT;
		// if (lineH > 320)
		// 	lineH = 320;
		// float lineO = 160 - lineH / 2;

		// // width is 8
		// for (int i = 0; i < 8; i++)
		// {
		// 	draw_line1(params->mlx, params->win, r * 8 + 530 + i, lineO, r * 8 + 530 + i, lineH + lineO, wall_color);
		// }

		ra += 2 * DR;
		if (ra < 0)
			ra += 2 * pi;
		if (ra > 2 * pi)
			ra -= 2 * pi;
	}

}

void	delete_rays(t_params *params)
{
	int	r, mx, my, mp, dof;
	float rx, ry, ra, xo, yo, disT;
	
	ra = params->player_a - DR * 30;
	if (ra < 0)
		ra += 2 * pi;
	if (ra > 2 * pi)
		ra -= 2 * pi;
	for (r = 0; r < 30; r++)
	{
		// HORIZONTAL RAY-GRID INTERSECTION CODE
		dof = 0;
		float disH = 1000000, hx = params->player_x, hy = params->player_y;
		float aTan = -1 / tan(ra);
		if (ra > pi)
		{
			ry = (((int)params->player_y >> 6) << 6) - 0.0001;
			rx = (params->player_y - ry) * aTan + params->player_x;
			yo = -64;
			xo = -yo * aTan;
		}
		if (ra < pi)
		{
			ry = (((int)params->player_y >> 6) << 6) + 64;
			rx = (params->player_y - ry) * aTan + params->player_x;
			yo = 64;
			xo = -yo * aTan;
		}
		if (ra == 0 || ra == pi)
		{
			rx = params->player_x;
			ry = params->player_y;
			dof = 8;
		}
		while (dof < 8)
		{
			mx = (int)(rx) >> 6;
			my = (int)(ry) >> 6;
			mp = my * MAP_ROWS + mx;
			if (mp > 0 && mp < MAP_ROWS * MAP_COLS && map[mp] == 1)
			{
				dof = 8;
				hx = rx;
				hy = ry;
				disH = dist(params->player_x, params->player_y, hx, hy, ra); 
			}
			else
			{
				rx += xo;
				ry += yo;
				dof += 1;
			}
		}
		// draw_line1(params->mlx, params->win, params->player_x, params->player_y, rx, ry, 0x008000);

		// VERTICAL RAY-GRID INTERSECTION CODE
		dof = 0;
		float disV = 1000000, vx = params->player_x, vy = params->player_y;
		float nTan = -tan(ra);
		if (ra > P2 && ra < P3) // looking left
		{
			rx = (((int)params->player_x >> 6) << 6) - 0.0001;
			ry = (params->player_x - rx) * nTan + params->player_y;
			xo = -64;
			yo = -xo * nTan;
		}
		if (ra < P2 || ra > P3) // looking right
		{
			rx = (((int)params->player_x >> 6) << 6) + 64;
			ry = (params->player_x - rx) * nTan + params->player_y;
			xo = 64;
			yo = -xo * nTan;
		}
		if (ra == 0 || ra == pi)
		{
			rx = params->player_x;
			ry = params->player_y;
			dof = 8;
		}
		while (dof < 8)
		{
			mx = (int)(rx) >> 6;
			my = (int)(ry) >> 6;
			mp = my * MAP_ROWS + mx;
			if (mp > 0 && mp < MAP_ROWS * MAP_COLS && map[mp] == 1)
			{
				dof = 8;
				vx = rx;
				vy = ry;
				disV = dist(params->player_x, params->player_y, vx, vy, ra);
			}
			else
			{
				rx += xo;
				ry += yo;
				dof += 1;
			}
		}
		if (disV < disH)
		{
			rx = vx;
			ry = vy;
			disT = disV;
		}
		if (disH < disV)
		{
			rx = hx;
			ry = hy;
			disT = disH;
		}
		draw_line1(params->mlx, params->win, params->player_x + PLAYER_SIZE / 2, params->player_y + PLAYER_SIZE / 2, rx, ry, 0x000000);
		
		
		// // Draw 3D walls
		// float ca = params->player_a - ra;
		// if (ca < 0)
		// 	ca += 2 * pi;
		// if (ca > 2 * pi)
		// 	ca -= 2 * pi;
		// disT = disT * cos(ca);
		// float lineH = (TAIL_SIZE * 320) / disT;
		// if (lineH > 320)
		// 	lineH = 320;
		// float lineO = 160 - lineH / 2;

		// for (int i = 0; i < 8; i++)
		// {
		// 	draw_line1(params->mlx, params->win, r * 8 + 530 + i, lineO, r * 8 + 530 + i, lineH + lineO, 0x0000F00);
		// }

		ra += 2 * DR;
		if (ra < 0)
			ra += 2 * pi;
		if (ra > 2 * pi)
			ra -= 2 * pi;
	}

}


int	update_window(t_params *params)
{
	// mlx_clear_window(params->mlx, params->win);
	draw_player(params);
	draw_line(params, 0x0000FF);
	draw_rays(params);
	return (0);
}


int main(void)
{
	t_params	params;

	params.mlx = mlx_init();
	params.win = mlx_new_window(params.mlx, WIN_WIDTH, WIN_HEIGHT, "Hello world!");
	
	// params.player_x = WIN_WIDTH / 2 - PLAYER_SIZE / 2;
	// params.player_y = WIN_HEIGHT / 2 - PLAYER_SIZE / 2;
	params.player_x = 220;
	params.player_y = 220;
	params.player_dx = cos(params.player_a) * X;
	params.player_dy = sin(params.player_a) * X;
	params.player_a = 0;


	draw_map(&params);

	mlx_key_hook(params.win, handle_keypress, &params);
	mlx_loop_hook(params.mlx, update_window, &params);

	mlx_loop(params.mlx);
	return (0);
}
