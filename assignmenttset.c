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

int* returnAllIntFromFile(char *filename)
{
    FILE *file;
    char ch;
    int count = 0;
    int *intArray = malloc(sizeof(int) * findAmountOfInt(filename));

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
            intArray[count] = atoi(ch);
            count++;
            while (isdigit(ch = fgetc(file)))
            {
                intArray[count] = atoi(ch);
                count++;
            }
        }
    }

    fclose(file);

    return intArray;
}

int main(){
    int *intArray = returnAllIntFromFile("numbers.txt");
    for (int i = 0; i < findAmountOfInt("numbers.txt"); i++)
    {
        printf("%d\n", intArray[i]);
    }
}