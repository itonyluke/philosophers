#include "../include/philosophers.h"

static int	number_is_positive(char *str)
{
	int	i;

	i = 0;
	if (str != NULL)
	{
		if (str[0] == '-')
			return (0);
		while (str[i] != '\0')
		{
			if (str[i] < '0' || str[i] > '9')
				return (0);
			i++;
		}
	}
	return (1);
}

static int	check_options(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!(number_is_positive(argv[i])))
			return (0);
		i++;
	}
	return (1);
}

int	init_options(int argc, char **argv, t_options *o)
{
	if (check_options(argc, argv))
	{
		o->number_of_philosophers = ft_atoi(argv[1]);
		o->time_to_die = ft_atoi(argv[2]);
		o->time_to_eat = ft_atoi(argv[3]);
		o->time_to_sleep = ft_atoi(argv[4]);
		if (o->number_of_philosophers == 0 || o->time_to_die == 0 || o->time_to_eat == 0 || o->time_to_sleep == 0)
			return (0);
		else if (o->number_of_philosophers > 200 || o->time_to_die < 60 ||
		o->time_to_eat < 60 || o->time_to_sleep < 60)
		{
			printf("\033[33mdo not test with\nmore than 200 "
				   "philosophers\nor\ntime_to_die < 60\ntime_to_eat < "
				   "60\ntime_to_sleep < 60\033[0m\n");
			return (0);
		}
		o->number_of_times_a_philosopher_must_eat = -1;
		o->begin_time = time_has_passed(0);
		if (argc == 6)
			o->number_of_times_a_philosopher_must_eat = ft_atoi(argv[5]);
		pthread_mutex_init(&o->string, NULL);
		return (1);
	}
	else
		return (0);
}

t_philosophers	*init_philosophers(t_options *o)
{
	t_philosophers	*p;
	pthread_mutex_t	*f;
	int				i;

	i = -1;
	p = 0;
	f = malloc(o->number_of_philosophers * sizeof(pthread_mutex_t));
	p = malloc(o->number_of_philosophers * sizeof(t_philosophers));
	if (f && p)
	{
		while (++i < o->number_of_philosophers)
			pthread_mutex_init(&f[i], NULL);
		i = -1;
		while (++i < o->number_of_philosophers)
		{
			p[i].left_fork = &f[i];
			p[i].right_fork = &f[(i + 1) % o->number_of_philosophers];
			p[i].number = i + 1;
			p[i].beginning_of_life = o->begin_time;
			p[i].o = o;
			p[i].times_left_to_eat = o->number_of_times_a_philosopher_must_eat;
		}
	}
	return (p);
}
