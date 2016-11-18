#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>

/**
 * char* get_input()
 * Gets user input (up to 2^64 - 1 bytes max currently) and allocates an array for it
 * Return: char ptr to malloced memory containing null-terminated string of user input
 */
char* get_input() {
    //The full input of the user
    char* input = malloc(1);

    //Tracks the size of the buffer
    unsigned long int i = 0;

    //The current input character
    char c;
    scanf("%c", &c);

    //TODO Handle 0 byte input
    //TODO Check for input == NULL and errno == ENOMEM for allocation failures
    //Allocate a buffer for the new size and store the new string in it
    do {
        input = reallocf(input, i+2); //+2 accounts for null byte
        input[i] = c;
        input[i+1] = '\0';
        i++;
        scanf("%c", &c);
    } while ( c != EOF && c != '\n');
    return input;
}

/**
 * int main()
 * Gets a series of user input and formates it as specified before printing it out
 * Return: 0 on success, anything else on failure
 */
int main() {
    //hooking SIGSEGV to ignore crashes would count as not crashing right? right...?
    //signal(SIGSEGV, ignore_crash);
    //</joke>


    printf("Enter a first name and last name: ");
    char* name = get_input();


    if (name != NULL) {
        free(name);
    }

    return 0; 
}
