#include "../minishell.h"

int				is_flag(char *argv)
{
	int			i;

	i = 0;
	if ((argv && argv[i] == '-') && (argv[i + 1] == 'n'))
	{
		i++;
		while(argv[i])
		{
			if (argv[i] != 'n')
				return 0;
			i++;
		}
		return 1;
	}
	return 0;
}

int				my_echo(char **argv)
{
	int			flag;
	int			i;

	i = 1;
	if ((flag = is_flag(argv[1]) == 1))
		argv++;
	while(argv[i])
	{
		printf("%s", argv[i]);
		if (argv[i + 1])
			printf(" ");
		i++;
	}
	if (!flag)
		printf("\n");
	return (EXIT_SUCCESS);
}