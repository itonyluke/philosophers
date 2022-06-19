#include "../include/philosophers.h"

int	error_exit(const char *str_error)
{
	printf("%s\n", str_error);
	return (1);
}

size_t	time_has_passed(size_t begin_time)
{
	size_t				time_passed;
	struct timeval		t;
	int					error_check;

	error_check = gettimeofday(&t, NULL);
	if (error_check != 0)
		error_exit("\033[91mgettimeofday failed\033[0m\n");
	time_passed = (t.tv_sec * 1000 + t.tv_usec / 1000) - begin_time;
	return (time_passed);
}

void	usleep_for_a_while(size_t sleep_in_ms)
{
	size_t	finish_time_in_ms;

	finish_time_in_ms = time_has_passed(0) + sleep_in_ms;
	while (time_has_passed(0) < finish_time_in_ms)
		usleep(100);
}

static int	ternary_operator(int condition, int true, int false)
{
	if (condition)
		return (true);
	return (false);
}

int	ft_atoi(const char *str)
{
	unsigned long	num;
	int				sign;
	int				i;

	num = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\r' || str[i] == '\v' || str[i] == '\f')
		i++;
	if (((str[i] == '+') || (str[i] == '-')) && (str[i++] == '-'))
		sign = -1;
	if (!(str[i] >= '0' && str[i] <= '9'))
		return (0);
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + str[i] - '0';
		if ((num > 2147483647 && sign == 1)
			|| (num > 2147483648 && sign == -1))
			return (ternary_operator(sign == 1, -1, 0));
		i++;
	}
	return (sign * num);
}
