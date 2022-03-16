#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct s_board
{
	int width;
	int height;
	char background;
}	board;

typedef struct s_op
{
	char type;
	float x;
	float y;
	float width;
	float height;
	char color;
}	op;

void	ft_putchar(char c)
{
	write(1, &c, sizeof(char));
}

void	ft_putstr(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
		ft_putchar(s[i]);
}

int	parse_first_line(board *board, FILE *stream)
{
	if (!stream)
		return (1);
	if (fscanf(stream, "%d %d %c\n", &board->width, &board->height, &board->background) != 3)
		return (1);
	if (board->width <= 0 || board->width > 300)
		return (1);
	if (board->height <= 0 || board->height > 300)
		return (1);
	return (0);
}

int	is_in_rectangle(float x, float y, op op)
{
	if ((((x < op.x) || (op.x + op.width < x)) || (y < op.y)) || (op.y + op.height < y))
		return (0);
	if (((x - op.x < 1.00000000) | ((op.x + op.width) - x < 1.00000000)) ||
		((y - op.y < 1.00000000 || ((op.y + op.height) - y < 1.00000000))))
		return (2);
	return (1);
}

void	print_canva(char **canva, board board)
{
	for (int height = 0; height < board.height; height++)
		ft_putstr(canva[height]);
}

void	draw_one(op op, char **canva, int x, int y)
{
	int is_in = is_in_rectangle((float)x, (float)y, op);
	if (is_in == 2 || (is_in == 1 && op.type == 'R'))
		canva[y][x] = op.color;
}

int	draw(op op, board board, char **canva)
{
	if (((op.width <= 0.00000000) || (op.height <= 0.00000000)) || ((op.type != 'R' && (op.type != 'r'))))
		return (1);
	int i = 0;
	int j = 0;
	while (i < board.width)
	{
		j = 0;
		while (j < board.height)
			draw_one(op, canva, i, j++);
		i++;
	}
	return (0);
}

int	execute(board board, char **canva, FILE *stream)
{
	op op;

	int ret = fscanf(stream, "%c %f %f %f %f %c\n", &op.type, &op.x, &op.y, &op.width, &op.height, &op.color);
	while (ret == 6)
	{
		if (draw(op, board, canva))
			return (1);
		ret = fscanf(stream, "%c %f %f %f %f %c\n", &op.type, &op.x, &op.y, &op.width, &op.height, &op.color);
	}
	if (ret == -1)
	{
		print_canva(canva, board);
		return (0);
	}
	return (1);
}

void	fill_canva(char **canva, board board)
{
	int width = 0;
	int height = 0;

	while (height < board.height)
	{
		width = 0;
		canva[height] = calloc(1, board.width + 1);
		while (width < board.width)
		{
			canva[height][width] = board.background;
			width++;
		}
		canva[height][width] = '\n';
		height++;
	}
}



int	main(int ac, char **av)
{
	if (ac != 2)
	{
		ft_putstr("Error: argument\n");
		return (1);
	}
	board board;
	FILE *stream = fopen(av[1], "r");
	if (parse_first_line(&board, stream))
	{
		ft_putstr("Error: Operation file corrupted\n");
		return (1);
	}
	char **canva = malloc(sizeof(char*) * board.height);
	fill_canva(canva, board);
	if (execute(board, canva, stream))
	{
		ft_putstr("Error: Operation file corrupted\n");
		return (1);
	}
	return (0);
}
