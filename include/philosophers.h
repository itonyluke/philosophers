#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include "../include/eat.h"
# include "../include/sleep_and_think.h"
# include "../include/init_structures.h"
# include "../include/utils.h"

typedef struct s_options		t_options;

typedef struct s_options
{
	int				number_of_philosophers;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				number_of_times_a_philosopher_must_eat;
	size_t			begin_time;
	pthread_mutex_t	string;
}				t_options;

typedef struct s_philosophers	t_philosophers;

typedef struct s_philosophers
{
	pthread_t		tid;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	int				number;
	size_t			beginning_of_life;
	t_options		*o;
	int				times_left_to_eat;
}				t_philosophers;

#endif
