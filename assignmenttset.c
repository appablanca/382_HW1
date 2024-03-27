#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/types.h>
#include <unistd.h>

int nrDigits(int number)
{
    int count = 0;
    while (number != 0)
    {
        number /= 10;
        count++;
    }
    return count;
}

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
    printf("Input file: \n");
    int status;
    FILE *fileread1;
    FILE *fileread2;
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
        int count1 = 0;
        int digits1 = 0;
        int digits2 = 0;
        int digits3 = 0;
        int digits4 = 0;
        int digits5 = 0;
        int numberOfInt1 = findAmountOfInt("numbers.txt");

        printf("Child 1\n");
        close(pipe1[1]);
        dup2(pipe1[0], 0);
        while (scanf("%d", &buffer) != EOF)
        {
            int number = nrDigits(buffer);
            count1++;
            if (number == 1)
            {
                digits1++;
            }
            else if (number == 2)
            {
                digits2++;
            }
            else if (number == 3)
            {
                digits3++;
            }
            else if (number == 4)
            {
                digits4++;
            }
            else if (number == 5)
            {
                digits5++;
            }
            if (count1 == numberOfInt1)
            {
                break;
            }
        }
        close(pipe1[0]);

        printf("1 digit: %d\n", digits1);
        printf("2 digits: %d\n", digits2);
        printf("3 digits: %d\n", digits3);
        printf("4 digits: %d\n", digits4);
        printf("5 digits: %d\n", digits5);

    }
    else
    {
        child2 = fork();
        if (child2 == 0)
        {
            // Child 2
            int buffer;
            int count2 = 0;
            int primes = 0;
            int nonprimes = 0;
            int numberOfInts2 = findAmountOfInt("numbers.txt");
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
                if (count2 == numberOfInts2)
                {
                    break;
                }
            }

            printf("Primes: %d\n", primes);
            printf("Nonprimes: %d\n", nonprimes);

            exit(0);
        }
        else
        {
            // Parent

            int buffer;
            int countParent = 0;
            printf("Parent\n");
            char *filename = "numbers.txt";
            fileread1 = fopen(filename, "r");
            fileread2 = fopen(filename, "r");
            int numberOfInt = findAmountOfInt(filename);

            close(pipe1[0]);
            dup2(pipe1[1], 1);

            for (int i = 0; i < numberOfInt; i++)
            {
                int number;
                fscanf(fileread1, "%d\n", &number);
                printf("%d\n", number);
            }

            close(pipe1[1]);

            close(pipe2[0]);
            dup2(pipe2[1], 1);

            for (int i = 0; i < numberOfInt; i++)
            {

                int number;
                fscanf(fileread2, "%d\n", &number);
                printf("%d\n", number);
            }
            close(pipe2[1]);
            
        }
    }

    return 0;
}