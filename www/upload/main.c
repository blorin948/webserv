
#include <unistd.h>
#include <stdio.h>
 #include <string.h>
 #include <sys/wait.h>

int fill_zero(char **av, char *c)
{
    int i = 0;
    while (*av)
    {
        if (strcmp(*av, c) == 0)
        {
            *av = NULL;
            i++;
        }
        av++;
    }
    return i;
}

char **exec(char **av, char **env)
{
	int tmp = fill_zero(av, "|");
	int i = tmp;
	int p[2];
	int save;
	int save_in;
	save = dup(1);
	save_in = dup(0);
	while (i > -1)
	{
		printf("%s\n", *av);
		int in = 0;
		int out = 1;;
		pipe(p);
		if (i == 0)
			out = 0;
		if (i > 0 && i != tmp)
			in = 1;
		int f = fork();

		if (out == 0)
			dup(save);
		//if (in == 0)
		//	dup2(0, save_in);
		if (f == 0)
		{

			dup2(p[0], STDIN_FILENO);
			if (out == 1)
				dup2(p[1], STDOUT_FILENO);

			close(p[0]);
			close(p[1]);
			execve(av[0], av, env);
		}
		else
		{
			if (in == 1)
			dup2(p[0], STDIN_FILENO);
			close(p[0]);
			close(p[1]);
			waitpid(0, NULL, 0);
			i--;
			while (*av)
				av++;
			if (i > -1)
				av++;
		}
	}
	close(p[0]);
	close(p[1]);
	dup(1);
	return (av);
}


int main(int ac, char **av, char **env)
{
    if (ac == 1)
        return (0);
av++;
   int i =  fill_zero(av, ";");
    while (i > -1)
    {
        av = exec(av, env);
        if (*av == NULL)
        {
           i--;
           av++;
        }
    }
}
