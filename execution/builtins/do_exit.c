#include "minishell.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}
int ft_isnumeric(char *str)
{
	if (!str || !*str)
		return (0);
	if (*str == '+' || *str == '-')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);	
}

int	ft_atoii(char *str)
{
	int		i;
	size_t	result;
	int		sign;

	i = 0;
	result = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (sign * result);
}


void	do_exit(char **args, int *exit_status)
{
	printf("exit\n");
	
	if (!args[1])
		exit(*exit_status);
	
	if (!ft_isnumeric(args[1]))
	{
		printf("minishell: exit: %s: numeric argument required\n", args[1]);
		exit(2);
	}
	
	if (args[2])
	{
		printf("minishell: exit: too many arguments\n");
		*exit_status = EXIT_FAILURE; //deja kaykon fstdlib dakchi 3lach ma7tajinach lih define
		return;
	}

	int n;
	n = ft_atoii(args[1]);
	exit((unsigned char)n);
}
