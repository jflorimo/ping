#include <stdio.h>
#include "libft.h"
#include "pingManager.h"

void helpOption()
{
	printf("Usage: ping [-aAbBdDfhLnOqrRUvV] [-c count] [-i interval] [-I interface]\n");
}

int main(int ac, char **av)
{
	(void)ac;
	(void)av;
	if (ac < 2)
		helpOption();
	else
	{
		ping(av[1]);
	}
	return 0;
}
