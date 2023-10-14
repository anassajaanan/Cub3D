#include "../include/cub3d.h"

#define WIN_WIDTH 1024
#define WIN_HEIGHT 512
#define PLAYER_SIZE 20
#define MOVE_SPEED 20
#define MAP_COLS 8
#define MAP_ROWS 8
#define TAIL_SIZE 64




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
	int		player_x;
	int		player_y;
}				t_params;

int	handle_keypress(int keycode, t_params *params)
{
	if (keycode == 53)
		exit(0);
	if (keycode == 13)
		params->player_y -= MOVE_SPEED;
	else if (keycode == 0)
		params->player_x -= MOVE_SPEED;
	else if (keycode == 1)
		params->player_y += MOVE_SPEED;
	else if (keycode == 2)
		params->player_x += MOVE_SPEED;
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
	for (int i = 0; i < TAIL_SIZE; i++)
	{
		for (int j = 0; j < TAIL_SIZE; j++)
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

int	update_window(t_params *params)
{
	// mlx_clear_window(params->mlx, params->win);
	draw_player(params);
	return (0);
}


int main(void)
{
	t_params	params;

	params.mlx = mlx_init();
	params.win = mlx_new_window(params.mlx, WIN_WIDTH, WIN_HEIGHT, "Hello world!");
	
	params.player_x = WIN_WIDTH / 2 - PLAYER_SIZE / 2;
	params.player_y = WIN_HEIGHT / 2 - PLAYER_SIZE / 2;

	draw_map(&params);
	mlx_key_hook(params.win, handle_keypress, &params);
	mlx_loop_hook(params.mlx, update_window, &params);

	mlx_loop(params.mlx);
	return (0);
}
