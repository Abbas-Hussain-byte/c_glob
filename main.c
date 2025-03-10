//C PROGRAM:
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#define MAX_WORD_LENGTH 500
#define NUM_ROUNDS 5
void scrambleWord(char *word, char *scrambledWord);
int getPlayerGuess(char *word, char *hint);

// Function to generate a scrambled version of the word
void scrambleWord(char *word, char *scrambledWord) 
{
    strcpy(scrambledWord, word);
    int length = strlen(word);
    
    for (int i = 0; i < length - 1; i++)
    {
        int j = i + rand() % (length - i);
        // Swap characters
        char temp = scrambledWord[i];
        scrambledWord[i] = scrambledWord[j];
        scrambledWord[j] = temp;
    }
}

// Function to get a player's guess with a maximum of 2 attempts
int getPlayerGuess(char *word, char *hint) 
{
    char guess[MAX_WORD_LENGTH];
    int attempts = 0;

    while (attempts < 2) 
    {
        printf("Enter your guess (or 'hint' for a hint): ");
        int i = 0;
        char ch;
        while (1) 
        {
        ch = getch();
        // Break the loop on Enter key
        if (ch == '\r' || ch == '\n') {
            guess[i] = '\0';
            break;
        }
        // Handle backspace
        if (ch == '\b' && i > 0) {
            i--;
            printf("\b \b");  // Move cursor back, erase character, move cursor back again
        } else {
            guess[i] = ch;
            i++;
            printf("*");  // Print '*' instead of the actual character
        }
        }

        if (strcmp(guess, "hint") == 0) 
        {
            printf("\nHint: %s\n", hint);
            attempts++; // Using hint counts as an attempt
        } 
        else if (strcmp(guess, word) == 0) 
        {
            printf("\nCorrect!\n");
            return attempts == 0 ? 5 : 2; // Score differently based on attempts
        } 
        else 
        {
            attempts++;
            printf("\nIncorrect! %d attempts remaining.\n", 2 - attempts);
            
        }
    }

    return 0; // If all attempts are incorrect
}

int main() 
{
    printf("\nWelcome to the Scramble Word Game!\n");
    printf("In this game, two players take turns guessing the secret word.\n");
    printf("The secret words are scrambled, and players have 2 attempts per round.\n");
    printf("You will be given a hint each round. The player with the most correct guesses in 5 rounds is the Winner.\n");
    printf("\nLet's Start!\n\n");

    srand(time(NULL));

    char words[NUM_ROUNDS][MAX_WORD_LENGTH] = {"linearsearch", "binarysearch", "keywords", "array", "structure"}; //{"programming", "array", "algorithm", "variable", "clanguage"}; =>set of words for next game
    char hints[NUM_ROUNDS][500] = {"Sequential search", "Search based on divide and conquer", "Reserved words with predefined meanings", "Homogenous collection of data", "Heterogenous collection of data"};
//respective hints for next game. {"The process for telling a computer which tasks to perform to solve problems", "A data structure consisting of a collection of elements of the same data type", "A sequence of instructions carried out in a predetermined order to solve a problem", "The name of a memory location used for storing data", "Programming language developed by Dennis Ritchie at Bell Laboratories"};
    int player1Score = 0, player2Score = 0;

    for (int round = 0; round < NUM_ROUNDS; round++)
    {
        char word[MAX_WORD_LENGTH];
        char scrambledWord[MAX_WORD_LENGTH];

        strcpy(word, words[round]);
        scrambleWord(word, scrambledWord);

        printf("Round %d\n", round + 1);
        printf("Scrambled Word: %s\n", scrambledWord);
        // printf("Hint: %s\n", hints[round]);
        printf("Player 1 : \n");
        player1Score += getPlayerGuess(word, hints[round]);
        printf("Player 2 : \n");
        player2Score += getPlayerGuess(word, hints[round]);

        printf("Current Scores: Player 1 - %d, Player 2 - %d\n\n", player1Score, player2Score);
    }

    // Determine the winner
    if (player1Score > player2Score) 
    {
        printf("Player 1 is the winner!\n");
    } 
    else if (player2Score > player1Score) 
    {
        printf("Player 2 is the winner!\n");
    } 
    else
    {
        printf("It's a tie!\nTry again!");
    }

    return 0;
}
