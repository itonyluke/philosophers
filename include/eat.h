#ifndef EAT_H
# define EAT_H

typedef struct s_philosophers	t_philosophers;

void	eat(t_philosophers *p);
void	lock_and_unlock_a_str(t_philosophers *p, const char *str);

#endif
