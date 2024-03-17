#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
int main()
{

    pid_t child_a, child_b;

    child_a = fork();

    if (child_a == 0)
    {
        /* Child A code */
    }
    else
    {
        child_b = fork();

        if (child_b == 0)
        {
            /* Child B code */
        }
        else
        {
            /* Parent Code */
        }
    }

    return 0;
}