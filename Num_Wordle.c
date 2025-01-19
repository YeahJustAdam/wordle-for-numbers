#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define NUM_DIGITS 5 // change this to increase of decrease the number of digits guessed

void printHelp(){
    printf("\033[1m\033[34mUsage:\033[0m new_project [options]\n");
    printf("\033[1m\033[34mOptions:\033[0m\n");
    printf("  \033[1m-help\033[0m   Display this help message\n");
    printf("  \033[1m-cheat\033[0m  Display the generated random numbers\n");
    printf("\n\033[1m\033[34mDescription:\033[0m\n");
    printf("This is a number guessing game. The program generates a sequence of NUM_DIGITS random numbers between 0 and 9.\n");
    printf("Your task is to guess the sequence. After each round, you will receive feedback:\n");
    printf("  '\033[1mM\033[0m' indicates a correct number in the correct position.\n");
    printf("  '\033[1mF\033[0m' indicates a correct number in the wrong position.\n");
    printf("  '\033[1mX\033[0m' indicates an incorrect number.\n");
}

void generateRandomNumber(int array[])
{
    int i, n;
    time_t t;
    n = NUM_DIGITS;
    srand((unsigned)time(&t));
    for (i = 0; i < n; i++)
    {
        array[i] = rand() % 10;
    }
}

int checkForMatch(int guess[], int userInput[], int index) {
    for (int i = 0; i < NUM_DIGITS; i++)
    {
        if (userInput[index] == guess[i])
        {
            if (userInput[index] == guess[index])
            {
                return 1;
            }else{
                return 0;
            }
            
        }
    }
    return -1;
}

void playRound(int guess[], int userInput[]) {

    printf("Enter %d numbers:\n", NUM_DIGITS);

    for (int i = 0; i < NUM_DIGITS; i++) {
        if (scanf("%d", &userInput[i]) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n'); // clear the input buffer
            i--; // decrement i to retry the current index
        }else if (userInput[i] < 0 || userInput[i] > 9) {
            printf("Invalid input. Please enter a single-digit number (0-9).\n");
            while (getchar() != '\n'); // clear the buffer
            i--; // retry the same index
        }
    }

    char result[NUM_DIGITS];
    for (int index = 0; index < NUM_DIGITS; index++) {
        int match = checkForMatch(guess, userInput, index);
        if (match == 1) {
            result[index] = 'M';
        } else if (match == 0) {
            result[index] = 'F';
        } else {
            result[index] = 'X';
        }
        
    
    }
    printf("User input: ");
    for (int i = 0; i < NUM_DIGITS; i++) {
        printf("%d ", userInput[i]);
    }
    printf("\nResult:     ");
    for (int i = 0; i < NUM_DIGITS; i++) {
        switch (result[i])
        {
        case 'M':
            printf("\033[1m\033[32m%c \033[0m", result[i]);
            break;
        
        case 'F':
            printf("\033[1m\033[33m%c \033[0m", result[i]);
            break;

        case 'X':
            printf("\033[1m\033[31m%c \033[0m", result[i]);
            break;
        }
    }
    printf("\n");
}

int checkForWin(int guess[], int userInput[]) {
    for (int i = 0; i < NUM_DIGITS; i++) {
        if (guess[i] != userInput[i]) {
            return 0;
        }
    }
    return 1;
}

int main(int argc, char const *argv[])
{
    int guess[NUM_DIGITS] = {0};
    generateRandomNumber(guess);
    int userInput[NUM_DIGITS];
    if (argc == 2 && strcmp(argv[1], "-cheat") == 0)
    {
        printf("\033[0;31mAnswer: ");
        for (int i = 0; i < NUM_DIGITS; i++) {
            printf("%d ", guess[i]);
        }
        printf("\033[0m\n");
    }

    if (argc == 2 && strcmp(argv[1], "-help") == 0)
    {
        printHelp();
        return 0;
    }
    
    int win = 0;
    printf("\n");
    int iterate = 0;
    while (win == 0) {
        playRound(guess, userInput);
        win = checkForWin(guess, userInput);
        iterate++;
    }

    printf("\n\033[1m\033[32mYou won in %d moves!\033[0m\n", iterate);
    return 0;
}
