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
	if (fscanf(stream, "%d %d %c", &board->width, &board->height, &board->background) != 3)
		return (1);
	if (board->width <= 0 || board->width > 300)
		return (1);
	if (board->height <= 0 || board->height > 300)
		return (1);
	return (0);
}

void print_info(board board, char *canva)
{
	int i;

	i = 0;
	while (i < board.height)
		printf("%.*s\n", board.width, canva + i++ * board.height);
}

int	draw(board board, char *canva, FILE *file)
{
	op op;
	if (fscanf("%c %f %f %f %f %c", op.type, op.x, op.y, op.width, op.height, op.color) != 6)
		return (1);
	if (op.type != 'r' && op.type != 'R')
		return (1);
	if (op.x < 0.000000 || op.y < 0.000000)
		return (1);
	if (op.x > board.)
	return (0);
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
		ft_putstr("Error : Operation file corrupted\n");
		return (1);
	}
	char *canva = calloc(board.width, board.height);
	if (!canva)
		return (ret);
	if (draw(board, canva, stream))
		return (1);
	print_info(board, canva);
	return (0);
}
