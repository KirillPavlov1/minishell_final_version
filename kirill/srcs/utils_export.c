#include "../minishell.h"

int	check_var_validity(char *argument)
{
	if (!ft_strchr(argument, '='))
		return (fail("Please add variable with \"=\"", 0));
	if ((!(ft_isalpha(argument[0])) && argument[0] != '_'))
	{
		printf("export: '%s': not a valid identifier\n", argument);
		return (0);
	}
	return (1);
}

void	sort_array_2x(char **array)
{
	int		i;
	int		j;
	char	*temp;
	char	*temp_2;
	int		count;

	count = count_envp(array);
	i = 0;
	while (array[i] != NULL)
	{
		j = count - 1;
		while (j > i)
		{
			if (ft_strncmp(array[j - 1], array[j],
					(ft_strlen(array[0]) + 1)) > 0)
			{
				temp = array[j - 1];
				array[j - 1] = array[j];
				array[j] = temp;
			}
			j--;
		}
		i++;
	}
}

void	print_arr_2x(char **array)
{
	int			i;

	i = 0;
	while (array[i] != NULL)
	{
		printf("%s\n", array[i]);
		i++;
	}
}