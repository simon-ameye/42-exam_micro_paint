/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_micro_paint.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 19:12:00 by sameye            #+#    #+#             */
/*   Updated: 2022/01/04 16:31:47 by sameye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>

typedef struct s_rectangle
{
	char type;
	float x;
	float y;
	float width;
	float height;
	char color;
} t_rectangle;

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

void fill_back(t_drawing *draw)
{
	int i;
	int j;

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

int is_in_rect(float i, float j, float x, float y, float w, float h)
{
	if (i < x || i > x + w || j < y || j > y + h)
		return (0);
	if (i - x < 1 && i - x >= 0)
		return (2);
	if (j - y < 1 && j - y >= 0)
		return (2);
	if (x + w - i < 1 && x + w - i >= 0)
		return (2);
	if (y + h - j < 1 && y + h - j >= 0)
		return (2);
	return (1);
}

void switch_val(t_drawing *draw, t_rectangle *rect, int i, int j)
{
	int type;

	type = is_in_rect((float)i, (float)j, rect->x, rect->y, rect->width, rect->height);
	if (rect->type == 'r' && type == 2)
		draw->matrix[i + j * draw->width] = rect->color;
	if (rect->type == 'R' && (type == 2 || type == 1))
		draw->matrix[i + j * draw->width] = rect->color;
}

void threat_rect(t_drawing *draw, t_rectangle *rect)
{
	int i;
	int j;

	j = 0;
	while (j < draw->height)
	{
		i = 0;
		while (i < draw->width)
		{
			switch_val(draw, rect, i, j);
			i++;
		}
		j++;
	}
}

int ft_exec(FILE *file)
{
	int res;
	t_rectangle rect;
	t_drawing draw;

	if (fscanf(file, "%d %d %c\n", &draw.width, &draw.height, &draw.c) != 3)
		return (1);
	if (draw.width <= 0 || draw.width > 300 || draw.height <= 0 || draw.height > 300)
		return (1);
	draw.matrix = malloc(sizeof(char) * draw.height * draw.width);
	if (!draw.matrix)
		return (1);

	fill_back(&draw);
	res = 6;
	while (1)
	{
		res = fscanf(file, "%c %f %f %f %f %c\n", &rect.type, &rect.x, &rect.y, &rect.width, &rect.height, &rect.color);
		if (res != 6)
			break ;
		if (rect.type != 'r' && rect.type != 'R')
			return (1);
		if (rect.width <= 0.0 || rect.height <= 0.0)
			return (1);
		threat_rect(&draw, &rect);
	}
	if (res != EOF)
	{
		free(draw.matrix);
		return (1);
	}
	ft_print(&draw);
	free(draw.matrix);
	return (0);
}

int main(int ac, char **av)
{
	FILE *file;

	if (ac != 2)
	{
		ft_putstr("Error: argument\n");
		return (1);
	}
	file = fopen(av[1], "r");
	if (!file)
	{
		ft_putstr("Error: Operation file corrupted\n");
		return (1);
	}
	if (ft_exec(file))
	{
		ft_putstr("Error: Operation file corrupted\n");
		return (1);
	}

	return (0);
}
