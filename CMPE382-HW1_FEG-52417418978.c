#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int findAmountOfInt (char filename[]){
    FILE *file;
    char ch;
    int count = 0;

    file = fopen( filename , "r");

    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    while ((ch = fgetc(file)) != EOF){
        if (isdigit(ch)){
            count ++;
            while (isdigit(ch = fgetc(file))){}
        }
    }

    fclose(file);

    return(count);
}

int isPrime(int number) {
    if (number <= 1) {
        return 0;
    }

    for (int i = 2; i * i <= number; i++) {
        if (number % i == 0) {
            return 0; 
        }
    }
    
    return 1;
}


int main()
{  
    char filename[] = "numbers.txt";
    int numberOfInt = findAmountOfInt(filename);



    
    return 0;
}



