#include <unistd.h>

typedef struct
{
	int		fill;
	int		width;
	int		height;
	char	c;
} micro;

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

int	main(int ac, char **av)
{
	int		w;
	int		h;
	char	bg;
	micro micro[10000];

	if (ac != 2)
	{
		ft_putstr("Error: argument\n");
		return (1);
	}

	return (0);
}
