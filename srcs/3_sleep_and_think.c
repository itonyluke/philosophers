#include "../include/philosophers.h"

void	sleep_for_a_while(t_philosophers *p)
{
	lock_and_unlock_a_str(p, "is sleeping");
	usleep_for_a_while(p->o->time_to_sleep);
}

void	think(t_philosophers *p)
{
	lock_and_unlock_a_str(p, "is thinking");
}
