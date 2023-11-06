/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 08:41:38 by aajaanan          #+#    #+#             */
/*   Updated: 2023/11/06 09:45:36 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_free(void *ptr)
{
	if (ptr)
		free(ptr);
	ptr = NULL;
}

void	free_split_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		ft_free(array[i]);
		i++;
	}
	ft_free(array);
}

void	free_2D_array(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		ft_free(map[i]);
		i++;
	}
	ft_free(map);
}

void	free_map_infos(t_map_infos *map_infos)
{
	ft_free(map_infos->no_path);
	ft_free(map_infos->so_path);
	ft_free(map_infos->we_path);
	ft_free(map_infos->ea_path);

	free_queue(&map_infos->queue);
}

void	free_and_cleanup(t_params *params)
{
	free_2D_array(params->map.map_data);
	free_map_infos(&params->map_infos);
	if (params->window_img.img)
		mlx_destroy_image(params->mlx, params->window_img.img);
	if (params->win)
		mlx_destroy_window(params->mlx, params->win);
	ft_free(params->mlx);
}