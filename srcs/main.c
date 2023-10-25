#include "../include/cub3d.h"

#define WINDOW_WIDTH 2048
#define WINDOW_HEIGHT 1024
#define MOVEMENT_SPEED 25
#define ROTATION_SPEED 0.1
#define TILE_SIZE 64
#define ROWS 16
#define COLS 16
#define PLAYER_SIZE 10
#define PLAYER_COLOR 0xFF0000

char	*map[16] = {
	"1111111111111111",
	"1000000000000001",
	"1000000000000001",
	"1000000000000001",
	"1000000000000001",
	"1000000000000001",
	"1000000000000001",
	"1000000100000001",
	"1000000000000001",
	"1000000000000001",
	"1000000000000001",
	"1000000000000001",
	"1000000000000001",
	"1000000000000001",
	"1000000000000001",
	"1111111111111111"
};

void	init_player(t_player *player)
{
	player->x = 100;
	player->y = 100;
	player->direction = 0;
	player->dx = cos(player->direction) * MOVEMENT_SPEED;
	player->dy = sin(player->direction) * MOVEMENT_SPEED;
}

void	init_camera(t_camera *camera)
{
	camera->resolution = 640;
	camera->focal_length = 0.8;
	camera->range = 16;
}

void	normalize_direction(double *direction)
{
	if (*direction < 0)
		*direction += 2 * M_PI;
	if (*direction > 2 * M_PI)
		*direction -= 2 * M_PI;
}

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

void	draw_player(t_params *params)
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



// Ray Casting Algorithm

// Calculate Horizontal Intersection

double	calculate_distance(double x1, double y1, double x2, double y2)
{
	return (sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)));
}

t_fpoint	horizontal_ray_intersection(t_params *params, double angle)
{
	t_fpoint	ray;
	float		y_step;
	float		x_step;
	t_point		index;

	ray.x = INT_MAX;
	ray.y = INT_MAX;
	if (angle == 0 || angle == M_PI)
		return (ray);
	else if (angle > 0 && angle < M_PI) // looking Down
	{
		ray.y = (((int)params->player.y / TILE_SIZE) * TILE_SIZE) + TILE_SIZE;
		y_step = TILE_SIZE;
	}
	else // looking Up
	{
		ray.y = (((int)params->player.y / TILE_SIZE) * TILE_SIZE) - 0.0001;
		y_step = -TILE_SIZE;
	}
	ray.x = params->player.x + (ray.y - params->player.y) / tan(angle);
	x_step = y_step / tan(angle);
	while (1)
	{
		index.x = (int)ray.x / TILE_SIZE;
		index.y = (int)ray.y / TILE_SIZE;
		if (index.x < 0 || index.x >= COLS || index.y < 0 || index.y >= ROWS)
		{
			ray.x = INT_MAX;
			ray.y = INT_MAX;
			return (ray);
		}
		if (map[index.y][index.x] == '1')
			break;
		ray.x += x_step;
		ray.y += y_step;
	}
	return (ray);
}

t_fpoint	vertical_ray_intersection(t_params *params, double angle)
{
	t_fpoint	ray;
	float		y_step;
	float		x_step;
	t_point		index;

	ray.x = INT_MAX;
	ray.y = INT_MAX;
	if (angle == M_PI / 2 || angle == 3 * M_PI / 2)
		return (ray);
	else if (angle > M_PI / 2 && angle < 3 * M_PI / 2) // looking Left
	{
		ray.x = (((int)params->player.x / TILE_SIZE) * TILE_SIZE) - 0.0001;
		x_step = -TILE_SIZE;
	}
	else // looking Right
	{
		ray.x = (((int)params->player.x / TILE_SIZE) * TILE_SIZE) + TILE_SIZE;
		x_step = TILE_SIZE;
	}
	ray.y = params->player.y + (ray.x - params->player.x) * tan(angle);
	y_step = x_step * tan(angle);
	while (1)
	{
		index.x = (int)ray.x / TILE_SIZE;
		index.y = (int)ray.y / TILE_SIZE;
		if (index.x < 0 || index.x >= COLS || index.y < 0 || index.y >= ROWS)
		{
			ray.x = INT_MAX;
			ray.y = INT_MAX;
			return (ray);
		}
		if (map[index.y][index.x] == '1')
			break;
		ray.x += x_step;
		ray.y += y_step;
	}
	return (ray);
}

t_ray	ray_intersection(t_params *params, double angle)
{
	t_ray		ray;
	t_fpoint	horizontal;
	t_fpoint	vertical;
	double		horizontal_distance;
	double		vertical_distance;

	ray.direction = angle;
	horizontal = horizontal_ray_intersection(params, angle);
	vertical = vertical_ray_intersection(params, angle);
	horizontal_distance = calculate_distance(params->player.x, params->player.y, horizontal.x, horizontal.y);
	vertical_distance = calculate_distance(params->player.x, params->player.y, vertical.x, vertical.y);
	if (horizontal_distance < vertical_distance)
	{
		ray.x = horizontal.x;
		ray.y = horizontal.y;
		ray.distance = horizontal_distance;
	}
	else
	{
		ray.x = vertical.x;
		ray.y = vertical.y;
		ray.distance = vertical_distance;
	}
	return (ray);
}

void	cast_rays(t_params *params)
{
	int		num_columns;
	double	player_FOV;
	double	column_width;
	double	column_increment;

	num_columns = params->camera.resolution;
	player_FOV = M_PI / 3;
	column_width = WINDOW_WIDTH / num_columns;
	column_increment = player_FOV / num_columns;

	for (int column = 0; column < num_columns; column++)
	{
		double ray_angle = params->player.direction - (player_FOV / 2) + (column * column_increment);
		t_ray ray = ray_intersection(params, ray_angle);
		double distance = ray.distance * cos(ray_angle - params->player.direction);
		// double wall_height = (WINDOW_HEIGHT / distance);
		double wall_height = (WINDOW_HEIGHT * TILE_SIZE) / distance;
		double wall_width = column_width;
		int half_width = WINDOW_WIDTH / 2;
		double wall_x = half_width + column * column_width;
		double wall_y = (WINDOW_HEIGHT / 2) - (wall_height / 2);
		draw_line(params, init_point(wall_x, wall_y), init_point(wall_x, wall_y + wall_height), 0xFF00FF);
	}
}

void	clear_screen(t_params *params)
{
	int half_width = WINDOW_WIDTH / 2;

	for (int i = 0; i < WINDOW_HEIGHT; i++)
	{
		for (int j = 0; j < WINDOW_WIDTH; j++)
		{
			mlx_pixel_put(params->mlx, params->win, half_width + j, i, 0x000000);
		}
	}
}

int	key_press(int keycode, t_params *params)
{
	if (keycode == 15)
	{
		clear_screen(params);
		cast_rays(params);
	}
	if (keycode == 53)
	{
		mlx_clear_window(params->mlx, params->win);
		mlx_destroy_window(params->mlx, params->win);
		exit(0);
	}
	if (keycode == 13)
	{
		params->player.x += params->player.dx;
		params->player.y += params->player.dy;
	}
	else if (keycode == 1)
	{
		params->player.x -= params->player.dx;
		params->player.y -= params->player.dy;
	}
	else if (keycode == 0)
	{
		params->player.direction -= ROTATION_SPEED;
		normalize_direction(&params->player.direction);
		params->player.dx = cos(params->player.direction) * MOVEMENT_SPEED;
		params->player.dy = sin(params->player.direction) * MOVEMENT_SPEED;
	}
	else if (keycode == 2)
	{
		params->player.direction += ROTATION_SPEED;
		normalize_direction(&params->player.direction);
		params->player.dx = cos(params->player.direction) * MOVEMENT_SPEED;
		params->player.dy = sin(params->player.direction) * MOVEMENT_SPEED;
	}
	return (0);
}

int	update_window(t_params *params)
{
	draw_player(params);
	draw_line(params, init_point(params->player.x, params->player.y), init_point(params->player.x + params->player.dx, params->player.y + params->player.dy), 0xF0000F);
	return (0);
}

int main(void)
{
	t_params	params;

	params.mlx = mlx_init();
	params.win = mlx_new_window(params.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3d");

	init_player(&params.player);
	init_camera(&params.camera);

	draw_map(&params);

	mlx_key_hook(params.win, key_press, &params);
	mlx_loop_hook(params.mlx, update_window, &params);
	mlx_loop(params.mlx);
	return (0);
}