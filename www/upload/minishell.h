
#ifndef MINISHELL_H
# define MINISHELL_H

#include "libft/libft.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

t_list  *myenv;
int		get_next_line(int fd, char **line);

#endif
