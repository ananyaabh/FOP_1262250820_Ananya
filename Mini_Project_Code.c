#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define MAX_WORDS 8
#define MAX_LENGTH 20
#define MAX_TRIES 6

/* ================= WORD SCRAMBLE ================= */

void scrambleWord(char *original, char *scrambled) {
    int length = strlen(original);
    strcpy(scrambled, original);

    for (int i = length - 1; i > 0; i--) {
        int j = rand() % (i + 1);

        char temp = scrambled[i];
        scrambled[i] = scrambled[j];
        scrambled[j] = temp;
    }
}

void play_scramble() {
    char words[][20] = {"computer", "program", "language", "variable", "pointer"};
    char guess[50];
    int attempts = 3;

    char targetWord[20];
    char jumbledWord[20];

    strcpy(targetWord, words[rand() % 5]);
    scrambleWord(targetWord, jumbledWord);

    printf("\n===== WORD SCRAMBLE GAME =====\n");
    printf("Scrambled word: %s\n", jumbledWord);

    while (attempts > 0) {
        printf("Your guess (%d attempts left): ", attempts);
        scanf("%49s", guess);

        if (strcmp(guess, targetWord) == 0) {
            printf("✅ Correct! You win!\n");
            return;
        } else {
            attempts--;
            if (attempts > 0)
                printf("❌ Wrong! Try again.\n");
            else
                printf("💀 Game Over! The word was: %s\n", targetWord);
        }
    }
}

/* ================= HANGMAN ================= */

void display_hangman(int tries) {
    char *stages[] = {
        "  ______\n |    |\n |    O\n |   /|\\\n |    |\n |   / \\\n_|__________\n",
        "  ______\n |    |\n |    O\n |   /|\\\n |    |\n |   /\n_|__________\n",
        "  ______\n |    |\n |    O\n |   /|\\\n |    |\n |\n_|__________\n",
        "  ______\n |    |\n |    O\n |   /|\n |    |\n |\n_|__________\n",
        "  ______\n |    |\n |    O\n |    |\n |    |\n |\n_|__________\n",
        "  ______\n |    |\n |    O\n |\n |\n |\n_|__________\n",
        "  ______\n |    |\n |\n |\n |\n |\n_|__________\n"
    };

    printf("%s\n", stages[MAX_TRIES - tries]);
}

void play_hangman() {
    char *countries[MAX_WORDS] = {
        "JAPAN", "INDIA", "VIETNAM", "ROME",
        "KENYA", "IRAN", "TURKEY", "TUNISIA"
    };

    char word[MAX_LENGTH];
    char guessed_word[MAX_LENGTH];
    char guess[MAX_LENGTH];
    int guessed_letters[26] = {0};

    int tries = MAX_TRIES;
    int guessed = 0;

    strcpy(word, countries[rand() % MAX_WORDS]);
    int length = strlen(word);

    for (int i = 0; i < length; i++)
        guessed_word[i] = '_';
    guessed_word[length] = '\0';

    printf("\n===== HANGMAN GAME =====\n");

    while (tries > 0 && !guessed) {

        display_hangman(tries);
        printf("Word: %s\n", guessed_word);
        printf("Tries left: %d\n", tries);
        printf("Enter letter or word: ");

        scanf("%19s", guess);

        for (int i = 0; guess[i]; i++)
            guess[i] = toupper(guess[i]);

        if (strlen(guess) == 1) {
            char letter = guess[0];

            if (!isalpha(letter)) {
                printf("Invalid input!\n");
                continue;
            }

            if (guessed_letters[letter - 'A']) {
                printf("Already guessed!\n");
                continue;
            }

            guessed_letters[letter - 'A'] = 1;

            int found = 0;
            for (int i = 0; i < length; i++) {
                if (word[i] == letter) {
                    guessed_word[i] = letter;
                    found = 1;
                }
            }

            if (!found) {
                printf("Letter not found!\n");
                tries--;
            }
        } else {
            if (strcmp(word, guess) == 0) {
                strcpy(guessed_word, word);
                guessed = 1;
            } else {
                printf("Wrong guess!\n");
                tries--;
            }
        }

        if (strcmp(word, guessed_word) == 0)
            guessed = 1;
    }

    if (guessed)
        printf("\n🎉 You guessed the word: %s\n", word);
    else {
        display_hangman(0);
        printf("\n💀 Game Over! The word was: %s\n", word);
    }
}

/* ================= MAIN MENU ================= */

int main() {
    int choice;

    srand(time(NULL));

    while (1) {
        printf("\n==============================\n");
        printf("        WORD GAMES MENU       \n");
        printf("==============================\n");
        printf("1. Word Scramble\n");
        printf("2. Hangman\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                play_scramble();
                break;
            case 2:
                play_hangman();
                break;
            case 3:
                printf("Exiting... Thank you for playing!\n");
                exit(0);
            default:
                printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}