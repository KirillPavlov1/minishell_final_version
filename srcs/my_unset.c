#include "minishell.h"

void            my_unset(t_all *all)
{
    char		**dup;
    char		**dup_var;
    int			i;
    int			j;
    int			count;

    count = count_envp(all->envp_cp.envp_cp);
    dup_var = NULL;
    dup = (char **) malloc(sizeof (char *) * count);
    if ((dup_var = check_arg(all->envp_cp.envp_cp, &all->cmd.argument)))
    {
        i = 0;
        j = 0;
        while (all->envp_cp.envp_cp[i] != NULL)
        {
            if (all->envp_cp.envp_cp[i] == *dup_var) {
                i++;
                continue;
            }
            dup[j] = ft_strdup(all->envp_cp.envp_cp[i]);
            i++;
            j++;
        }
        i = 0;
		while (all->envp_cp.envp_cp[i] != NULL)
		{
			if (all->envp_cp.envp_cp[i])
			{
				free(all->envp_cp.envp_cp[i]);
			}
			i++;
		}
        free(all->envp_cp.envp_cp); // надо зафришить all.envp_cp[i]
        all->envp_cp.envp_cp = dup;
    }
    sort_envp_cp(all->envp_cp.envp_cp);
    print_arr_2x(dup);
}