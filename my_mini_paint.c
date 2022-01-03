/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_mini_paint.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 19:12:00 by sameye            #+#    #+#             */
/*   Updated: 2022/01/03 20:16:31 by sameye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

typedef struct s_circle
{
	char type;
	float x;
	float y;
	float radius;
	char c;
} t_circle;

typedef struct s_drawing
{
	int width;
	int height;
	char *matrix;
	char c;
} t_drawing;

void ft_putstr(char *s)
{
	while (*s)
	{
		write(1, s, 1);
		s++;
	}
}

int get_info(FILE *file, t_drawing *draw)
{
	int i;
	int j;

	if (fscanf(file, "%d %d %c", &draw->width, &draw->height, &draw->c) == 3)
	{
		if (draw->width <= 0 || draw->width > 300 || draw->height <= 0 || draw->height > 300)
			return (1);
		draw->matrix = malloc(sizeof(char) * draw->height * draw->width);
		if (!draw->matrix)
			return (1);
		j = 0;
		while (j < draw->height)
		{
			i = 0;
			while (i < draw->width)
			{
				draw->matrix[i + j * draw->width] = draw->c;
				i++;
			}
			j++;
		}
	}
	return (0);
}

void ft_print(t_drawing *draw)
{
	int line;

	line = 0;
	while (line < draw->height)
	{
		write(1, &draw->matrix[line * draw->width], draw->width);
		write(1, "\n", 1);
		line++;
	}

}

int ft_exec(FILE *file)
{
	int res;
	t_circle circle;
	t_drawing draw;

	if (get_info(file, &draw))
		return (1);
	res = 5;

	while (res == 5)
	{
		res = fscanf(file, "%c, %f, %f, %f, %c", circle.type, circle.x, circle.y, circle.radius, circle.c);

	}
	ft_print(&draw);
	free(draw.matrix);
	return (0);
}

int main(int ac, char **av)
{
	FILE *file;

	if (ac == 2)
	{
		file = fopen(av[1], "r");
		if (!file)
			return (0);
		if (!ft_exec(file))
			return (0);
		ft_putstr("Error: Operation file corrupted\n");
	}
	else
		ft_putstr("Error: argument\n");
	return (1);
}