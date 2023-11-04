/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 07:43:23 by aajaanan          #+#    #+#             */
/*   Updated: 2023/11/04 12:33:30 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <unistd.h>


void	init_map_infos(t_map_infos *map_infos)
{
	map_infos->south_texture.path = NULL;
	map_infos->north_texture.path = NULL;
	map_infos->west_texture.path = NULL;
	map_infos->east_texture.path = NULL;

	map_infos->parsed_color_count = 0;
	map_infos->parsed_texture_count = 0;
}

void	free_map_infos(t_map_infos *map_infos)
{
	ft_free(map_infos->north_texture.path);
	ft_free(map_infos->south_texture.path);
	ft_free(map_infos->west_texture.path);
	ft_free(map_infos->east_texture.path);

	free_queue(&map_infos->map);
}

int main()
{
	t_map_infos	map_infos;
	int ret;
	
	char	map[] = "./map.cub";

	init_map_infos(&map_infos);
	init_queue(&map_infos.map);
	ret = parse_map(map, &map_infos);

	if (ret == SUCCESS)
	{
		printf("NO: %s\n", map_infos.north_texture.path);
		printf("SO: %s\n", map_infos.south_texture.path);
		printf("WE: %s\n", map_infos.west_texture.path);
		printf("EA: %s\n", map_infos.east_texture.path);
		printf("F: %d, %d, %d\n", map_infos.floor_color.red, map_infos.floor_color.green, map_infos.floor_color.blue);
		printf("C: %d, %d, %d\n", map_infos.ceiling_color.red, map_infos.ceiling_color.green, map_infos.ceiling_color.blue);
		printf("Map:\n");
		t_queue_node	*tmp = map_infos.map.front;
		while (tmp)
		{
			printf("%s", tmp->val);
			tmp = tmp->next;
		}
	}


	free_map_infos(&map_infos);
	return (ret);
	
}