#include "../include/cub3d.h"

#define WIN_WIDTH 1024
#define WIN_HEIGHT 1024
#define TILE_SIZE 64
#define ROWS 16
#define COLS 16
#define MOVEMENT_SPEED 20
#define PLAYER_SIZE 10
#define PLAYER_COLOR 0xFFFF00
#define PI 3.14159265359
#define DE 0.0174532925
#define ANGLE_ROT 0.1

char	*map[16] = {
	"1111111111111111",
	"1000000000000001",
	"1000011111110001",
	"1000100000001001",
	"1000100000001001",
	"1000000000000001",
	"1000000110000001",
	"1000000110000001",
	"1000000000000001",
	"1000000000000001",
	"1000000000000001",
	"1000100000001001",
	"1000111111111001",
	"1000000000000001",
	"1000000000000001",
	"1111111111111111"
};


void	draw_tile(t_params *params, int col, int row, int color)
{
	for (int i = 0; i < TILE_SIZE - 1; i++)
	{
		for (int j = 0; j < TILE_SIZE - 1; j++)
		{
			mlx_pixel_put(params->mlx, params->win, col * TILE_SIZE + j, row * TILE_SIZE + i, color);
		}
	}
}



void	draw_map(t_params *params)
{
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			if (map[i][j] == '1')
				draw_tile(params, j, i, 0xFFFFFF);
		}
	}
}

void	draw_player_square(t_params *params)
{
	int x;
	int y;

	x = params->player.x - PLAYER_SIZE / 2;
	y = params->player.y - PLAYER_SIZE / 2;
	for (int i = 0; i < PLAYER_SIZE; i++)
	{
		for (int j = 0; j < PLAYER_SIZE; j++)
		{
			mlx_pixel_put(params->mlx, params->win, x + j, y + i, PLAYER_COLOR);
		}
	}
}

void	draw_player(t_params *params)
{
	t_point p1;
	t_point p2;
	t_point	p3;

	p1 = init_point(100, 100);
	p2 = init_point(80, 120);
	p3 = init_point(120, 120);

	draw_line(params, p1, p2, 0xFF0000);
	draw_line(params, p2, p3, 0xFF0000);
	draw_line(params, p3, p1, 0xFF0000);
}

float	distance(float x1, float y1, float x2, float y2)
{
	return (sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) * 0.1));
}

t_float_point	draw_ray_horizontal(t_params *params, float ra)
{
	float			rx;
	float			ry;
	float			yo;
	float			xo;
	t_float_point	p;

	p.x = INT_MAX;
	p.y = INT_MAX; 
	if (ra == 0 || ra == PI)
		return (p);
	else if (ra > 0 && ra < PI) // Looking Down
	{
		ry = (((int)params->player.y / TILE_SIZE) * TILE_SIZE ) + TILE_SIZE;
		rx = params->player.x + (ry - params->player.y) / tan(ra);
		yo = TILE_SIZE;
		xo = (yo / tan(ra));
	}
	else // Looking Up
	{
		ry = ((int)params->player.y / TILE_SIZE) * TILE_SIZE - 0.001;
		rx = params->player.x + (ry - params->player.y) / tan(ra);
		yo = -TILE_SIZE;
		xo = (yo / tan(ra));
	}
	while (1)
	{
		int mx = (int)rx / TILE_SIZE;
		int my = (int)ry / TILE_SIZE;
		if (mx < 0 || my < 0 || mx >= COLS || my >= ROWS)
			return (p);
		if (map[my][mx] == '1')
			break;
		ry += yo;
		rx += xo;
	}
	// draw_line(params, init_point(params->player.x, params->player.y), init_point(rx, ry), 0xFF00FF);
	// printf("The distance to the horizontal line is : %f\n", distance(params->player.x, params->player.y, rx, ry));
	p.x = rx;
	p.y = ry;
	return (p);
}

t_float_point	draw_ray_vertical(t_params *params, float ra)
{
	float			rx;
	float			ry;
	float			xo;
	float			yo;
	t_float_point	p;

	p.x = INT_MAX;
	p.y = INT_MAX;
	if (ra == (PI / 2) || ra == (3 * PI / 2))
		return (p);
	else if (ra < (PI / 2) || ra > (3 * PI / 2)) // Looking Right
	{
		rx = ((int)params->player.x / TILE_SIZE) * TILE_SIZE + TILE_SIZE;
		ry = params->player.y + (rx - params->player.x) * tan(ra);
		xo = TILE_SIZE;
		yo = xo * tan(ra);
	}
	else // Looking Left
	{
		rx = ((int)params->player.x / TILE_SIZE) * TILE_SIZE - 0.0001;
		ry = params->player.y + (rx - params->player.x) * tan(ra);
		xo = -TILE_SIZE;
		yo = xo * tan(ra);
	}
	while (1)
	{
		int mx = (int )rx / TILE_SIZE;
		int my = (int)ry / TILE_SIZE;
		if (mx < 0 || my < 0 || mx >= COLS || my >= ROWS)
			return (p);
		if (map[my][mx] == '1')
			break;
		rx += xo;
		ry += yo;
	}
	// draw_line(params, init_point(params->player.x, params->player.y), init_point(rx, ry), 0x00FFFF);
	// printf("The distance to the vertical line is : %f\n", distance(params->player.x, params->player.y, rx, ry));
	p.x = rx;
	p.y = ry;
	return (p);
}

void	ray_casting(t_params *params)
{
	t_float_point	h;
	t_float_point	v;
	float			h_dis;
	float			v_dis;

	float			angle;

	angle = params->player.angle - (PI / 6);
	if (angle < 0)
		angle += 2 * PI;
	for (int r = 0; r < 30; r++)
	{
		h = draw_ray_horizontal(params, angle);
		v = draw_ray_vertical(params, angle);
		h_dis = distance(params->player.x, params->player.y, h.x, h.y);
		v_dis = distance(params->player.x, params->player.y, v.x, v.y);
		if (h_dis < v_dis)
		{
			draw_line(params, init_point(params->player.x, params->player.y), init_point(h.x, h.y), 0xFF00FF);
		}
		else
		{
			draw_line(params, init_point(params->player.x, params->player.y), init_point(v.x, v.y), 0x00FFFF);
		}
		angle += 2 * DE;
		if (angle > 2 * PI)
			angle -= 2 * PI;
	}
}

int	key_press(int keycode, t_params *params)
{
	if (keycode == 15)
	{
		ray_casting(params);
	}
	// if (keycode == 17)
	// {
	// 	draw_ray_vertical(params);
	// }
	if (keycode == 53)
	{
		mlx_clear_window(params->mlx, params->win);
		mlx_destroy_window(params->mlx, params->win);
		exit(0);
	}
	if (keycode == 13) // Up
	{
		params->player.x += params->player.dx;
		params->player.y += params->player.dy;
	}
	else if (keycode == 1) // Down
	{
		params->player.x -= params->player.dx;
		params->player.y -= params->player.dy;
	}
	else if (keycode == 0) // Left
	{		
		params->player.angle -= ANGLE_ROT;
		if (params->player.angle < 0)
			params->player.angle += 2 * PI;
		params->player.dx = cos(params->player.angle) * MOVEMENT_SPEED;
		params->player.dy = sin(params->player.angle) * MOVEMENT_SPEED;
	}
	else if (keycode == 2)
	{
		params->player.angle += ANGLE_ROT;
		if (params->player.angle > 2 * PI)
			params->player.angle -= 2 * PI;
		params->player.dx = cos(params->player.angle) * MOVEMENT_SPEED;
		params->player.dy = sin(params->player.angle) * MOVEMENT_SPEED;
	}
	return (0);
}

int update_window(t_params *params)
{
	draw_player_square(params);
	draw_line(params, init_point(params->player.x, params->player.y), init_point(params->player.dx + params->player.x, params->player.dy + params->player.y), 0xFF0000);
	// draw_player(&params);


	return (0);
}


int main(void)
{
	t_params	params;

	params.mlx = mlx_init();
	params.win = mlx_new_window(params.mlx, WIN_WIDTH, WIN_HEIGHT, "cub3d");

	// init the player
	params.player.x = 70;
	params.player.y = 70;
	params.player.angle = 0;
	params.player.dx = cos(params.player.angle) * MOVEMENT_SPEED;
	params.player.dy = sin(params.player.angle) * MOVEMENT_SPEED;
	

	draw_map(&params);

	mlx_key_hook(params.win, key_press, &params);
	mlx_loop_hook(params.mlx, update_window, &params);
	mlx_loop(params.mlx);
}