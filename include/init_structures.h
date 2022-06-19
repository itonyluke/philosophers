#ifndef INIT_STRUCTURES_H
# define INIT_STRUCTURES_H

typedef struct s_options	t_options;

int				init_options(int argc, char **argv, t_options *o);
t_philosophers	*init_philosophers(t_options *o);

#endif
