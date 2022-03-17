#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct canva
{
	int w;
	int h;
	char c;
	char **canva;
}	canva;

typedef struct op
{
	char type;
	float x;
	float y;
	float w;
	float h;
	char c;
}	op;

void ft_putstr(char *str)
{
	int i = -1;
	while (str && str[++i])
		write(1, &str[i], 1);
}

int print_error(char *str)
{
	ft_putstr(str);
	return (1);
}

int print_canva(char **canva)
{
	int i = -1;
	while (canva && canva[++i])
	{
		ft_putstr(canva[i]);
		write(1, "\n", 1);
	}
	return (0);
}

int init_canva(canva *canva, FILE *stream)
{
	int i = -1;

	if (stream && fscanf(stream, "%d %d %c\n", &canva->w, &canva->h, &canva->c) == 3)
	{
		if (canva->w <= 0 || canva->w > 300 || canva->h <= 0 || canva->h > 300)
			return (1);
		canva->canva = malloc(sizeof(char*) * (canva->h + 1));
		canva->canva[canva->h] = 0;
		while (++i < canva->h)
		{
			canva->canva[i] = malloc(sizeof(char) * (canva->w + 1));
			canva->canva[i][canva->w] = 0;
			memset((char*)canva->canva[i], canva->c, canva->w);
		}
		return (0);
	}
	return (1);
}

int is_in_rectangle(op op, int x, int y)
{
	if (y < op.y || y > op.y + op.h || x < op.x || x > op.x + op.w)
		return (0);
	if (y - op.y < 1 || (op.y + op.h) - y < 1 || x - op.x < 1 || (op.x + op.w) - x < 1)
		return (2);
	return (1);
}

void apply_op(canva *canva, op op)
{
	int is_in;

	for (int i = 0; i < canva->h; i++)
	{
		for (int j = 0; j < canva->w; j++)
		{
			is_in = is_in_rectangle(op, j, i);
			if ((is_in == 2 && op.type == 'r') || (is_in && op.type == 'R'))
				canva->canva[i][j] = op.c;
		}
	}
}

int main(int ac, char **av)
{
	canva canva;
	op op;
	int ret;
	if (ac != 2)
		return (print_error("Error: argument\n"));
	FILE *stream = fopen(av[1], "r");
	if (!init_canva(&canva, stream))
	{
		while (1)
		{
			ret = fscanf(stream, "%c %f %f %f %f %c\n", &op.type, &op.x, &op.y, &op.w, &op.h, &op.c);
			if (ret == -1)
				return (print_canva(canva.canva));
			else if (ret != 6 || op.w <= 0 || op.h <= 0 || (op.type != 'r' && op.type != 'R'))
				break ;
			else
				apply_op(&canva, op);
		};
	}
	return (print_error("Error: Operation file corrupted\n"));
}
