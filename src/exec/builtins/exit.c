/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   exit.c                                               ┌─┐┌┬┐┌┬┐┌─┐        */
/*                                                        │ │ │  │ │ │        */
/*   By: tblochet <tblochet@student.42.fr>                └─┘ ┴  ┴ └─┘        */
/*                                                        ┌┬┐┌─┐┌┬┐┌─┐        */
/*   Created: 2025/01/15 11:46:19 by jspitz               │││├─┤ │ ├─┤        */
/*   Updated: 2025/03/12 12:39:25 by tblochet             ┴ ┴┴ ┴ ┴ ┴ ┴        */
/*                                                                            */
/* ************************************************************************** */

#include <builtins.h>
#include <pipe_exec.h>

__attribute__((noreturn)) static void	clear_exit(int code)
{
	gc_clear();
	core_set_last_exit(code);
	exit(code);
}

static int	atol_overflow_guard(char *nptr, long *res)
{
	int	sign;
	int	guard;

	sign = 1;
	guard = 0;
	*res = 0;
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		sign -= (*nptr == '-') * 2;
		nptr++;
	}
	while (*nptr && ft_isdigit(*nptr) && !guard)
	{
		*res *= 10;
		guard = __builtin_saddl_overflow(*res, *nptr - '0', res);
		nptr++;
	}
	if (guard)
		return (0);
	return (!(*nptr) || ft_isdigit(*nptr));
}

static bool	check_numeric_value(char *s)
{
	long	res;
	int		guard;

	guard = atol_overflow_guard(s, &res);
	if (!guard)
		ft_dprintf(2, "potishell: %s: numeric arguments required\n", s);
	return (guard);
}

static bool	handle_too_many_arg(char **av)
{
	if (!check_numeric_value(av[1]))
		return (true);
	else
	{
		ft_dprintf(2, "potishell: too many arguments\n");
		core_set_last_exit(1);
		return (false);
	}
}

void	ft_exit(int ac, char **av)
{
	ft_dprintf(2, "exit\n");
	if (ac == 1)
		clear_exit(core()->last_exit);
	if (ac == 2)
	{
		if (!check_numeric_value(av[1]))
			clear_exit(2);
		clear_exit(ft_atoi(av[1]));
	}
	if (handle_too_many_arg(av))
		clear_exit(2);
	else
		core_set_last_exit(1);
}
