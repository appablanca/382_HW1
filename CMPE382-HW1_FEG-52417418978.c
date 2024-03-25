#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/types.h>
#include <unistd.h>

int findAmountOfInt(char *filename)
{
    FILE *file;
    char ch;
    int count = 0;

    file = fopen(filename, "r");

    if (file == NULL)
    {
        printf("Error opening file.\n");
        return 1;
    }

    while ((ch = fgetc(file)) != EOF)
    {
        if (isdigit(ch))
        {
            count++;
            while (isdigit(ch = fgetc(file)))
            {
            }
        }
    }

    fclose(file);

    return (count);
}

int isPrime(int number)
{
    if (number <= 1)
    {
        return 0;
    }

    for (int i = 2; i * i <= number; i++)
    {
        if (number % i == 0)
        {
            return 0;
        }
    }

    return 1;
}

int main()
{
    FILE *fileread;
    int ch1;

    pid_t pid1;
    pid_t pid2;
    int pfd1[2];
    int pfd2[2];
    pipe(pfd1);
    pipe(pfd2);

    pid1 = fork();

    if (pid1 > 0)
    {
        pid2 = fork();
        if (pid2 > 0)
        {
            printf("parent ");
            printf("%ld ", (long)getpid());
            char *filename = "numbers.txt";
            int numberOfInt = findAmountOfInt(filename);
            printf("%d\n", numberOfInt);
            int buffer[numberOfInt];
            close(pfd1[0]);
            dup2(pfd1[1], 1);

            fileread = fopen(filename, "r");

            if (fileread == NULL)
            {
                printf("Error opening file.\n");
                return 1;
            } else {
                while ((ch1 = fgetc(fileread)) != EOF)
                {
                    if (isdigit(ch1))
                    {
                        ungetc(ch1, fileread);
                        fscanf(fileread, "%d", &buffer);
                        printf("%d ", buffer);
                    }
                }
            }
        
        }
        else if (pid2 == 0)
        {
            printf("child2 2");
            printf("%ld \n", (long)getpid());
        }
    }
    else if (pid1 == 0)
    {
        int buffer;

        printf("child 1");
        printf("%ld\n", (long)getpid());
        close(pfd1[1]);
        dup2(pfd1[0], 0);
        while (read(0, &buffer, 1) > 0)
        {
            printf("%d -", buffer);
        }
    }

    return 0;
}
