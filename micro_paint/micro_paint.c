#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct canva
{
	int w;
	int h;
	char c;
	char **canva;
} canva;

typedef struct op
{
	char t;
	float x;
	float y;
	float w;
	float h;
	char c;
} op;

void ft_putstr(char *str)
{
	int i = -1;
	while (str && str[++i])
		write(1, &str[i], 1);
	write(1, "\n", 1);
}

int print_error(char *str)
{
	ft_putstr(str);
	return (1);
}

int print_canva(char **canva)
{
	int i = -1;
	while (canva[++i])
		ft_putstr(canva[i]);
	return (0);
}

int init_canva(FILE *stream, canva *canva)
{
	int i = -1;

	if (fscanf(stream, "%d %d %c\n", &canva->w, &canva->h, &canva->c) != 3)
		return (1);
	if (canva->w <= 0 || canva->w > 300 || canva->h <= 0 || canva->h > 300)
		return (1);
	canva->canva = malloc(sizeof(char*) * (canva->h + 1));
	canva->canva[canva->h] = 0;
	while (++i < canva->h)
	{
		canva->canva[i] = malloc(sizeof(char) * (canva->w + 1));
		canva->canva[i][canva->w] = '\0';
		memset(canva->canva[i], canva->c, canva->w);
	}
	return (0);
}

int is_in_rectangle(op op, int x, int y)
{
	if (x < op.x || x > op.x + op.w || y < op.y || y > op.y + op.h)
		return (0);
	else if (x - op.x < 1 || (op.x + op.w) - x < 1 || y - op.y < 1 || (op.y + op.h) - y < 1)
		return (2);
	else
		return (1);
}

void apply_op(canva *canva, op op)
{
	int is_in;
	for (int j = 0; j < canva->h; j++)
	{
		for (int i = 0; i < canva->w; i++)
		{
			is_in = is_in_rectangle(op, i, j);
			if ((is_in == 1 && op.t == 'R') || is_in == 2)
				canva->canva[j][i] = op.c;
		}
	}
}

int check_op(op op)
{
	if (op.w <= 0 || op.h <= 0 || (op.t != 'R' && op.t != 'r'))
		return (1);
	return (0);
}

int main(int ac, char **av)
{
	if (ac != 2)
		return (print_error("Error: argument"));
	FILE *stream = fopen(av[1], "r");
	int ret;
	canva canva;
	op op;
	if (!stream || init_canva(stream, &canva))
		return (print_error("Error: Operation file corrupted"));
	while (1)
	{
		ret = fscanf(stream, "%c %f %f %f %f %c\n", &op.t, &op.x, &op.y, &op.w, &op.h, &op.c);
		if (ret == -1)
			return (print_canva(canva.canva));
		if (ret == 6 && !check_op(op))
			apply_op(&canva, op);
		else
			break ;
	}
	return (print_error("Error: Operation file corrupted"));
}
