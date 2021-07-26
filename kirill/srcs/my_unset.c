#include "../minishell.h"

int				check_argv(char *argument)
{
	if (ft_strchr(argument, '='))
	{
		printf("bash: unset: `%s': not a valid identifier\n", argument);
		return (1);
	}
	return (0);
}

int				my_unset(char ***envp_cp, char **argument)
{
	char		**dup;
	int			count;
	char		*dup_var;
	int			i;
	int			j;
	int			n;

	dup_var = NULL;

	n = 0;
	while (argument[n] != NULL)
	{
		count = count_envp(*envp_cp);
		dup = (char **) malloc(sizeof (char *) * count);
		if (check_argv(argument[n]))
			return (1);
		if ((dup_var = check_arg(*envp_cp, &argument[n])))
		{
			i = 0;
			j = 0;
			while ((*envp_cp)[i] != NULL)
			{
				if ((*envp_cp)[i] == dup_var) {
					i++;
					continue;
				}
				dup[j] = ft_strdup((*envp_cp)[i]);
				i++;
				j++;
			}
			dup[j] = NULL;
			clear_arr_2x(*envp_cp);
			*envp_cp = dup;
		}
		n++;
	}
	return (EXIT_SUCCESS);
}