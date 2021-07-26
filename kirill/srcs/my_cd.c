#include "../minishell.h"

int			update_pwd(char *old_pwd, char ***envp_cp)
{
	char 		*new_pwd;
	char 		*tmp;

	new_pwd = (char *)malloc(sizeof (char) * 500);
	new_pwd = getcwd(new_pwd, 500);
	if (!(tmp = ft_strjoin("PWD=",new_pwd)))
		return (0);
	set_value_arr_2x(tmp, envp_cp);
	free(tmp);
	if (!(tmp = ft_strjoin("OLDPWD=", old_pwd)))
		return (0);
	set_value_arr_2x(tmp, envp_cp);
	free(tmp);
	free(old_pwd);
	free(new_pwd);
	return (1);
}

char			*get_pwd(char **envp_cp)
{
	char 		*old_pwd;

	if (!(old_pwd = (char *) malloc(sizeof (char ) * 500)))
		return (NULL);
	old_pwd = getcwd(old_pwd, 500);
	return (old_pwd);
}

int				count_arguments(char **argv)
{
	int			res;

	res = 0;
	while(*argv++)
		res++;
	return res;
}

//нужно фришить abs_path
char			*get_absolute_path(char **envp_cp, char *relative_path)
{
	char		*home;
	char		*abs_path;

	abs_path = NULL;
	home = get_value(envp_cp, "HOME");
	abs_path = ft_strjoin(home, relative_path + 1);
	return (abs_path);
}

char			*get_home_path(char **envp_cp)
{
	int			n;
	char		*home_path;

	n = 0;
	while (envp_cp[n] != NULL)
	{
		if (ft_strncmp(envp_cp[n], "HOME=", ft_strlen("HOME=")) == 0)
		{
			home_path = ft_substr(envp_cp[n], 5, 100);
			return (home_path);
		}
		n++;
	}
	return (NULL);
}

int			go_home(char **envp_cp)
{
	int			i;
	char		*home_path;

	home_path = get_home_path(envp_cp);
	if ((i = chdir(home_path)) == -1)
	{
		printf("bash: cd: HOME not set\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int				my_cd(char **argument, char ***envp_cp)
{
	char		*abs_path;
	int			argc;
	char 		*old_pwd;
	int 		i;

	old_pwd = (char *)malloc(sizeof (char) * 500);
	old_pwd = getcwd(old_pwd, 500);
	argc = count_arguments(argument);
	if (argc < 2)
		go_home(*envp_cp);
	else if (argc >= 2 && argument[1] != NULL)
	{
		if (ft_strncmp(argument[1], "~", 2) == 0)
			go_home(*envp_cp);
		else
		{
			if (*(argument[1]) == '~')
			{
				abs_path = get_absolute_path(*envp_cp, argument[1]);
				if ((i = chdir(abs_path)) == -1)
				{
					printf("%s\n", strerror(errno));
					if (abs_path)
						free(abs_path);
					return (EXIT_FAILURE);
				}
			}
			else if ((i = chdir(argument[1])) == -1)
			{
				printf("%s\n", strerror(errno));
				return (EXIT_FAILURE);
			}
		}
	}
	else if (argument[1] == NULL)
		return (EXIT_FAILURE);
	if (!update_pwd(old_pwd, envp_cp))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}