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
    FILE *fileread1;

    pid_t child1;
    pid_t child2;

    int pipe1[2];
    int pipe2[2];
    int pipe3[2];
    int pipe4[2];
    pipe(pipe1);
    pipe(pipe2);
    pipe(pipe3);
    pipe(pipe4);

    child1 = fork();
    if (child1 == 0)
    {
        // Child 1
        int buffer;
        int count = 0;
        printf("Child 1\n");
        close(pipe1[1]);
        dup2(pipe1[0], 0);
        // while(scanf("%d", &buffer) != EOF)
        // {
        //     count++;
        // }
        // printf("Count: %d\n", count);
    }
    else
    {
        child2 = fork();
        if (child2 == 0)
        {
            // Child 2
            int buffer;
            int primes = 0;
            int nonprimes = 0;
            close(pipe2[1]);
            dup2(pipe2[0], 0);
            printf("Child 2\n");
            while (scanf("%d", &buffer) != EOF)
            {
                if (isPrime(buffer))
                {
                    primes++;
                }
                else
                {
                    nonprimes++;
                }
            }

            printf("%d\n", primes);
            printf("%d", nonprimes);
        }
        else
        {
            // Parent
            int buffer;
            printf("Parent\n");
            fileread1 = fopen("numbers.txt", "r");
            int numberOfInt = findAmountOfInt("numbers.txt");
            close(pipe1[0]);
            close(pipe2[0]);
            dup2(pipe1[1], 1);
            dup2(pipe2[1], 1);
            for (int i = 0; i < numberOfInt; i++)
            {
                int number;
                fscanf(fileread1, "%d", &number);
                printf("%d ", number);
            }

        }
    }

  

return 0;
}