#include "../include/cub3d.h"

#define WINDOW_WIDTH 2048
#define WINDOW_HEIGHT 1024
#define MOVEMENT_SPEED 20
#define ROTATION_SPEED 0.1
#define TILE_SIZE 64
#define TEXTURE_SIZE 64
#define ROWS 16
#define COLS 16
#define PLAYER_SIZE 10
#define PLAYER_COLOR 0xFF0000
#include "/Users/aajaanan/Desktop/project/Textures/wall1.ppm"
#include "/Users/aajaanan/Desktop/project/Textures/wall2.ppm"
#include "/Users/aajaanan/Desktop/project/Textures/wall3.ppm"
#include "/Users/aajaanan/Desktop/project/Textures/wall4.ppm"
#include "/Users/aajaanan/Desktop/project/Textures/wall5.ppm"
#include "/Users/aajaanan/Desktop/project/Textures/wall6.ppm"
#include "/Users/aajaanan/Desktop/project/Textures/wall7.ppm"
#include "/Users/aajaanan/Desktop/project/Textures/wall8.ppm"
#include "/Users/aajaanan/Desktop/project/Textures/wall9.ppm"





char	*map[] = {
	"1111111111111111",
	"1000000000000001",
	"1000111111110001",
	"1000000000000001",
	"1000000000000001",
	"1000000000000001",
	"1000000000000001",
	"1000000100000001",
	"1000000000000001",
	"1000000000000001",
	"1000000100000001",
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
	camera->resolution = 1048;
}

void	init_img(t_params *params)
{
	params->img.width = WINDOW_WIDTH;
	params->img.height = WINDOW_HEIGHT;
	params->img.img = mlx_new_image(params->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	params->img.addr = mlx_get_data_addr(params->img.img, &params->img.bits_per_pixel, &params->img.size_line, &params->img.endian);
	params->img.bpp = params->img.bits_per_pixel / 8;
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
			// mlx_pixel_put(params->mlx, params->win, col * TILE_SIZE + j, row * TILE_SIZE + i, color);
			mlx_pixel_put_img(params->mlx, &params->img, col * (TILE_SIZE) + j, row * (TILE_SIZE) + i, color);
			
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
			// mlx_pixel_put(params->mlx, params->win, x + j, y + i, PLAYER_COLOR);
			mlx_pixel_put_img(params->mlx, &params->img, x + j, y + i, PLAYER_COLOR);
		}
	}
}



// Ray Casting Algorithm

// Calculate Horizontal Intersection

double	calculate_distance(double x1, double y1, double x2, double y2)
{
	if ((int)x2 == -1 && (int)y2 == -1)
	{
		// printf("Error: No intersection\n");
		return (INT_MAX);
	}
	return (sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)));
}

t_fpoint	horizontal_ray_intersection(t_params *params, double angle)
{
	t_fpoint	ray;
	float		y_step;
	float		x_step;
	t_point		index;

	ray.x = -1;
	ray.y = -1;
	// if (angle == 0 || angle == M_PI)
	// 	return (ray);
	if (angle == 0 || angle == M_PI || angle == 2 * M_PI)
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
	float inv_tan_angle = 1.0 / tan(angle);
	ray.x = params->player.x + (ray.y - params->player.y) * inv_tan_angle;
	x_step = y_step * inv_tan_angle;
	while (1)
	{
		index.x = (int)ray.x / TILE_SIZE;
		index.y = (int)ray.y / TILE_SIZE;
		if (index.x < 0 || index.x >= COLS || index.y < 0 || index.y >= ROWS)
		{
			ray.x = -1;
			ray.y = -1;
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

	ray.x = -1;
	ray.y = -1;
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
	float tan_angle = tan(angle);
	ray.y = params->player.y + (ray.x - params->player.x) * tan_angle;
	y_step = x_step * tan_angle;
	while (1)
	{
		index.x = (int)ray.x / TILE_SIZE;
		index.y = (int)ray.y / TILE_SIZE;
		if (index.x < 0 || index.x >= COLS || index.y < 0 || index.y >= ROWS)
		{
			ray.x = -1;
			ray.y = -1;
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
		ray.color = 0x7752FE;
		ray.hit = HORIZONTAL;
	}
	else
	{
		ray.x = vertical.x;
		ray.y = vertical.y;
		ray.distance = vertical_distance;
		ray.color = 0x8E8FFA;
		ray.hit = VERTICAL;
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

	double angle = params->player.direction - (player_FOV / 2);
	for (int column = 0; column < num_columns; column++)
	{
		double ray_angle = angle + (column * column_increment);
		if (ray_angle < 0)
			ray_angle += 2 * M_PI;
		else if (ray_angle > 2 * M_PI)
			ray_angle -= 2 * M_PI;
		t_ray ray = ray_intersection(params, ray_angle);
		double distance = ray.distance * cos(ray_angle - params->player.direction);
		// double wall_height = (WINDOW_HEIGHT / distance);
		double wall_height = (WINDOW_HEIGHT * TILE_SIZE) / distance;
		double wall_width = column_width;
		int half_width = WINDOW_WIDTH / 2;
		double wall_x = half_width + column * column_width;
		double wall_y = (WINDOW_HEIGHT / 2) - (wall_height / 2);
	
		draw_line_img(params, init_point(wall_x, wall_y), init_point(wall_x, wall_y + wall_height), ray.color);
		
		if (ray.hit == HORIZONTAL)
			draw_line_img(params, init_point(params->player.x, params->player.y), init_point(ray.x, ray.y), 0x00F0AF);
		else
			draw_line_img(params, init_point(params->player.x, params->player.y), init_point(ray.x, ray.y), 0xE0F0AF);
		
		
		// Render the wall textures
		// double texture_x, texture_y;
		// int	*wall_image;
		// if (ray.hit == HORIZONTAL)
		// {
		// 	texture_x = (int)ray.x % TILE_SIZE;
		// 	if (ray.direction > M_PI)
		// 		texture_x = TILE_SIZE - texture_x - 1;
		// 	// wall_image = wall5;

		// 	// wall1 for north wall2 for south
		// 	int mx = (int)(ray.x) / TILE_SIZE;
		// 	int my = (int)(ray.y - 0.00001) / TILE_SIZE;
		// 	if (map[my][mx] == '1') // south
		// 		wall_image = wall2;
		// 	else
		// 		wall_image = wall1;
		// }
		// else
		// {
		// 	texture_x = (int)ray.y % TILE_SIZE;
		// 	if (ray.direction > M_PI / 2 && ray.direction < 3 * M_PI / 2)
		// 		texture_x = TILE_SIZE - texture_x - 1;
		// 	// wall_image = wall3;
		// 	// wall3 for east wall4 for west
		// 	int mx = (int)(ray.x - 0.00001) / TILE_SIZE;
		// 	int my = (int)ray.y / TILE_SIZE;
		// 	if (map[my][mx] == '1') // west
		// 		wall_image = wall8;
		// 	else
		// 		wall_image = wall5;
		// }
		

		// double texture_step = TEXTURE_SIZE / wall_height;
		// double texture_position = 0;
		// for (int y = 0; y < wall_height; y++)
		// {
		// 	texture_y = (int)texture_position & (TEXTURE_SIZE - 1);
		// 	int pixel = ((int)texture_y * TEXTURE_SIZE + (int)texture_x) * 3;
		// 	// check for valid index
		// 	if (pixel < 0 || pixel > (TEXTURE_SIZE * TEXTURE_SIZE * 3 - 3))
		// 	{
		// 		// printf("Error: Invalid pixel index: %d\n", pixel);
		// 		continue;
		// 	}

		// 	int red = wall_image[pixel];
		// 	int green = wall_image[pixel + 1];
		// 	int blue = wall_image[pixel + 2];
			

		// 	// Shading
        //     // double shading_factor = 1.0 - (distance / 1024.0);
        //     // shading_factor = (shading_factor < 0.0) ? 0.0 : shading_factor;

        //     // // Apply shading to the texture color
        //     // red = (int)(red * shading_factor);
        //     // green = (int)(green * shading_factor);
        //     // blue = (int)(blue * shading_factor);

        //     int hex_color = (red << 16) | (green << 8) | blue;
			
		// 	// mlx_pixel_put(params->mlx, params->win, wall_x, wall_y + y, hex_color);
		// 	mlx_pixel_put_img(params->mlx, &params->img, wall_x, wall_y + y, hex_color);
		// 	texture_position += texture_step;
		// }

		// // draw ground
		draw_line_img(params, init_point(wall_x, wall_y + wall_height), init_point(wall_x, WINDOW_HEIGHT), 0xF5F5F5);

		// // draw ceiling
		draw_line_img(params, init_point(wall_x, 0), init_point(wall_x, wall_y), 0xC2D9FF);
	}
}

void	empty_cast_rays(t_params *params)
{
	int		num_columns;
	double	player_FOV;
	double	column_width;
	double	column_increment;

	num_columns = params->camera.resolution;
	player_FOV = M_PI / 3;
	column_width = WINDOW_WIDTH / num_columns;
	column_increment = player_FOV / num_columns;

	double angle = params->player.direction - (player_FOV / 2);
	for (int column = 0; column < num_columns; column++)
	{
		double ray_angle = angle + (column * column_increment);
		if (ray_angle < 0)
			ray_angle += 2 * M_PI;
		else if (ray_angle > 2 * M_PI)
			ray_angle -= 2 * M_PI;
		t_ray ray = ray_intersection(params, ray_angle);
		double distance = ray.distance * cos(ray_angle - params->player.direction);
		// double wall_height = (WINDOW_HEIGHT / distance);
		double wall_height = (WINDOW_HEIGHT * TILE_SIZE) / distance;
		double wall_width = column_width;
		int half_width = WINDOW_WIDTH / 2;
		double wall_x = half_width + column * column_width;
		double wall_y = (WINDOW_HEIGHT / 2) - (wall_height / 2);
	
		draw_line_img(params, init_point(params->player.x, params->player.y), init_point(ray.x, ray.y), 0x000000);
	}
}

int	key_press(int keycode, t_params *params)
{
	if (keycode == 15)
	{
		// cast_rays(params);
	}
	if (keycode == 53)
	{
		mlx_clear_window(params->mlx, params->win);
		mlx_destroy_window(params->mlx, params->win);
		exit(0);
	}
	if (keycode == 13)
	{
		empty_cast_rays(params);
		params->player.x += params->player.dx;
		params->player.y += params->player.dy;
		cast_rays(params);
	}
	else if (keycode == 1)
	{
		empty_cast_rays(params);
		params->player.x -= params->player.dx;
		params->player.y -= params->player.dy;
		cast_rays(params);
	}
	else if (keycode == 0)
	{
		empty_cast_rays(params);
		params->player.direction -= ROTATION_SPEED;
		normalize_direction(&params->player.direction);
		params->player.dx = cos(params->player.direction) * MOVEMENT_SPEED;
		params->player.dy = sin(params->player.direction) * MOVEMENT_SPEED;
		cast_rays(params);
	}
	else if (keycode == 2)
	{
		empty_cast_rays(params);
		params->player.direction += ROTATION_SPEED;
		normalize_direction(&params->player.direction);
		params->player.dx = cos(params->player.direction) * MOVEMENT_SPEED;
		params->player.dy = sin(params->player.direction) * MOVEMENT_SPEED;
		cast_rays(params);
	}
	return (0);
}

int	update_window(t_params *params)
{
	// cast_rays(params);

	draw_player(params);
	draw_line_img(params, init_point(params->player.x, params->player.y), init_point(params->player.x + params->player.dx, params->player.y + params->player.dy), 0xF0000F);
	draw_map(params);
	// cast_rays(params);
	mlx_put_image_to_window(params->mlx, params->win, params->img.img, 0, 0);
	return (0);
}

int main(void)
{
	t_params	params;

	params.mlx = mlx_init();
	params.win = mlx_new_window(params.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3d");

	init_img(&params);
	init_player(&params.player);
	init_camera(&params.camera);


	

	// draw_line_img(&params, init_point(0, 0), init_point(WINDOW_WIDTH, WINDOW_HEIGHT), 0x00F0AF);

	
	mlx_key_hook(params.win, key_press, &params);
	mlx_loop_hook(params.mlx, update_window, &params);
	mlx_loop(params.mlx);
	return (0);
}