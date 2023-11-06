/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 03:43:28 by aajaanan          #+#    #+#             */
/*   Updated: 2023/11/06 03:43:48 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_map_infos(t_map_infos *map_infos)
{
	map_infos->south_texture.path = NULL;
	map_infos->north_texture.path = NULL;
	map_infos->west_texture.path = NULL;
	map_infos->east_texture.path = NULL;

	map_infos->parsed_color_count = 0;
	map_infos->parsed_texture_count = 0;
}
