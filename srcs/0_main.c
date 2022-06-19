#include "../include/philosophers.h"

static void	*do_this(void *ptr_to_a_philosopher)
{
    t_philosophers	*p;

	p = (t_philosophers *)ptr_to_a_philosopher;
	p->beginning_of_life = time_has_passed(0);
	while (1)
	{
		eat(p);
		if (p->times_left_to_eat > 0)
			p->times_left_to_eat--;
		sleep_for_a_while(p);
		think(p);
	}
}

int	a_philosopher_has_died(t_philosophers *p, int *number_of_p_that_dined)
{
	size_t		life_time;
	t_options	*o_ptr;

	o_ptr = p->o;
	life_time = time_has_passed(p->beginning_of_life);
	if (p->times_left_to_eat == 0)
	{
		p->times_left_to_eat = -1;
		(*number_of_p_that_dined)++;
	}
	if (life_time > o_ptr->time_to_die)
	{
		pthread_mutex_lock(&o_ptr->string);
		printf("\033[90m%zu ms\033[0m %d died\n",
			   time_has_passed(o_ptr->begin_time),
			   p->number);
		pthread_mutex_destroy(&o_ptr->string);
		return (1);
	}
	return (0);
}

void	*is_watching_you(void *p)
{
	int				i;
	int				number_of_p_that_dined;
	t_options		*o_copy;
	t_philosophers	*p_copy;

	number_of_p_that_dined = 0;
	p_copy = (t_philosophers *)p;
	o_copy = (p_copy[0].o);
	while (1)
	{
		i = 0;
		while (i < o_copy->number_of_philosophers)
		{
			if (a_philosopher_has_died(&p_copy[i], &number_of_p_that_dined))
				return (NULL);
			i++;
		}
		if (number_of_p_that_dined == o_copy->number_of_philosophers)
		{
			pthread_mutex_lock(&o_copy->string);
			return (NULL);
		}
	}
}

static void	start_simulation(t_philosophers *p)
{
	pthread_t	big_brother;
	int			i;

	i = 0;
	while (i < p->o->number_of_philosophers)
	{
		pthread_create(&p[i].tid, NULL, do_this, (void *)&p[i]);
		i++;
	}
	pthread_create(&big_brother, NULL, is_watching_you, (void *)p);
	pthread_join(big_brother, NULL);
}

int	main(int argc, char **argv)
{
	t_options		o;
	t_philosophers	*p;

	if (argc == 5 || argc == 6)
	{
		if (!(init_options(argc, argv, &o)))
			return (error_exit("\033[91mInvalid arguments\033[0m"));
		if (o.number_of_philosophers == 0)
			return (0);
		p = init_philosophers(&o);
		if (p == NULL)
			return (error_exit("\033[91mMalloc has failed\033[0m"));
		start_simulation(p);
	}
	else
		return (error_exit("\033[91mInvalid number of arguments.\033[0m\n"
						   "\033[33mUsage:\n"
						   "number_of_philosophers time_to_die time_to_eat"
						   "time_to_sleep "
						   "[number_of_times_each_philosopher_must_eat]\033[0m\n"
						   "Example:\n"
						   "./philo 5 800 200 200"));
	return (0);
}
