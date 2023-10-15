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

int	handle_keypress(int keycode, t_params *params)
{
	if (keycode == 53)
		exit(0);
	if (keycode == 13)
	{
		draw_line(params, 0x000000);
		clear_player_position(params);
		// params->player_y -= MOVE_SPEED;
		params->player_x += params->player_dx;
		params->player_y += params->player_dy;
	}
	else if (keycode == 0)
	{
		draw_line(params, 0x000000);
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
		clear_player_position(params);
		// params->player_y += MOVE_SPEED;
		params->player_x -= params->player_dx;
		params->player_y -= params->player_dy;
	}
	else if (keycode == 2)
	{
		draw_line(params, 0x000000);
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

int	update_window(t_params *params)
{
	// mlx_clear_window(params->mlx, params->win);
	draw_player(params);
	draw_line(params, 0x0000FF);
	return (0);
}


int main(void)
{
	t_params	params;

	params.mlx = mlx_init();
	params.win = mlx_new_window(params.mlx, WIN_WIDTH, WIN_HEIGHT, "Hello world!");
	
	// params.player_x = WIN_WIDTH / 2 - PLAYER_SIZE / 2;
	// params.player_y = WIN_HEIGHT / 2 - PLAYER_SIZE / 2;
	params.player_x = 300;
	params.player_y = 300;
	params.player_dx = cos(params.player_a) * X;
	params.player_dy = sin(params.player_a) * X;
	params.player_a = 0;


	draw_map(&params);

	mlx_key_hook(params.win, handle_keypress, &params);
	mlx_loop_hook(params.mlx, update_window, &params);

	mlx_loop(params.mlx);
	return (0);
}
