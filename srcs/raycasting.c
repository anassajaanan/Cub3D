/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 10:26:34 by aajaanan          #+#    #+#             */
/*   Updated: 2023/11/06 10:56:04 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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
		if (index.x < 0 || index.x >= params->map.cols || index.y < 0 || index.y >= params->map.rows)
		{
			ray.x = -1;
			ray.y = -1;
			return (ray);
		}
		if (params->map.map_data[index.y][index.x] == '1')
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
		if (index.x < 0 || index.x >= params->map.cols || index.y < 0 || index.y >= params->map.rows)
		{
			ray.x = -1;
			ray.y = -1;
			return (ray);
		}
		if (params->map.map_data[index.y][index.x] == '1')
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
		ray.length = horizontal_distance;
		ray.color = 0x7752FE;
		ray.hit = HORIZONTAL;
	}
	else
	{
		ray.x = vertical.x;
		ray.y = vertical.y;
		ray.length = vertical_distance;
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

	num_columns = RESOLUTION;
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
		double distance = ray.length * cos(ray_angle - params->player.direction);
		// double wall_height = (WINDOW_HEIGHT / distance);
		double wall_height = (WINDOW_HEIGHT * TILE_SIZE) / distance;
		double wall_width = column_width;
		int half_width = 0;
		double wall_x = half_width + column * column_width;
		double wall_y = (WINDOW_HEIGHT / 2) - (wall_height / 2);
	
		
		// if (ray.hit == HORIZONTAL)
		// 	draw_line_img(params, init_point(params->player.x, params->player.y), init_point(ray.x, ray.y), 0x00F0AF);
		// else
		// 	draw_line_img(params, init_point(params->player.x, params->player.y), init_point(ray.x, ray.y), 0xE0F0AF);
		

        /* No textures */
		draw_line_img(params, init_point(wall_x, wall_y), init_point(wall_x, wall_y + wall_height), ray.color);
		// draw_line_img(params, init_point(column * column_width, 0), init_point(column * column_width, WINDOW_WIDTH), 0x000000);


		/* render textures */
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

		// 	// int pixel = ((int)texture_y * TEXTURE_SIZE + (int)texture_x) * 3;
		// 	// // check for valid index
		// 	// if (pixel < 0 || pixel > (TEXTURE_SIZE * TEXTURE_SIZE * 3 - 3))
		// 	// {
		// 	// 	// printf("Error: Invalid pixel index: %d\n", pixel);
		// 	// 	continue;
		// 	// }

		// 	// int red = wall_image[pixel];
		// 	// int green = wall_image[pixel + 1];
		// 	// int blue = wall_image[pixel + 2];
			

		// 	// // Shading
        //     // // double shading_factor = 1.0 - (distance / 1024.0);
        //     // // shading_factor = (shading_factor < 0.0) ? 0.0 : shading_factor;

        //     // // // Apply shading to the texture color
        //     // // red = (int)(red * shading_factor);
        //     // // green = (int)(green * shading_factor);
        //     // // blue = (int)(blue * shading_factor);

        //     // int hex_color = (red << 16) | (green << 8) | blue;

		// 	int pixel_index = ((int)texture_y * TEXTURE_SIZE + (int)texture_x) * params->north_texture.bits_per_pixel / 8;
		// 	int hex_color = *(unsigned int *)(params->north_texture.addr + pixel_index);
			
		// 	// mlx_pixel_put(params->mlx, params->win, wall_x, wall_y + y, hex_color);
		// 	mlx_pixel_put_img(params->mlx, &params->img, wall_x, wall_y + y, hex_color);
		// 	texture_position += texture_step;
		// }

		// // draw ground
		draw_line_img(params, init_point(wall_x, wall_y + wall_height), init_point(wall_x, WINDOW_HEIGHT), params->floor_color);

		// // draw ceiling
		draw_line_img(params, init_point(wall_x, 0), init_point(wall_x, wall_y), params->ceiling_color);
	}
}