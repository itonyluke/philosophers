#include "../include/philosophers.h"

void	lock_and_unlock_a_str(t_philosophers *p, const char *str)
{
	int		time;

	pthread_mutex_lock(&p->o->string);
	time = time_has_passed(p->o->begin_time);
	printf("\033[90m%d ms\033[0m %d %s\n", time, p->number, str);
	pthread_mutex_unlock(&p->o->string);
}

static void	take_forks(t_philosophers *p)
{
	if (p->number % 2 != 0)
	{
		pthread_mutex_lock(p->left_fork);
		lock_and_unlock_a_str(p, "has taken a left fork");
		pthread_mutex_lock(p->right_fork);
		lock_and_unlock_a_str(p, "has taken a right fork");
	}
	else
	{
		pthread_mutex_lock(p->right_fork);
		lock_and_unlock_a_str(p, "has taken a right fork");
		pthread_mutex_lock(p->left_fork);
		lock_and_unlock_a_str(p, "has taken a left fork");
	}
}

static void	drop_forks(t_philosophers *p)
{
	if (p->number % 2 != 0)
	{
		pthread_mutex_unlock(p->left_fork);
		pthread_mutex_unlock(p->right_fork);
	}
	else
	{
		pthread_mutex_unlock(p->right_fork);
		pthread_mutex_unlock(p->left_fork);
	}
}

void	eat(t_philosophers *p)
{
	take_forks(p);
	p->beginning_of_life = time_has_passed(0);
	lock_and_unlock_a_str(p, "is eating");
	usleep_for_a_while(p->o->time_to_eat);
	drop_forks(p);
}
