#include <stdio.h>
#include <regex.h>
#include <string.h>
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
 * int check_blank(char* str)
 * Checks if the string is blank or not
 *
 * Args
 * * str - Null-terminated string to check
 * Returns: 0 if not blank, 1 if blank
 */
int check_blank(char* str) {
    if (strlen(str) == 0) {
        return 1;
    }

    if (str[0] == '\n') {
        return 1;
    }

    return 0;
}

/**
 * int check_name(char* name)
 * Makes sure the name input is sane
 * Accepts basically all input because you can have whatever name you want
 * Unless you are Little Bobby Drop Tables. Then go away.
 * 
 * Arguments: name: the name of the person
 * Returns: 0 on success, anything else on failure
 */
int check_name(char* name) {
    if (check_blank(name)) {
        return 1;
    }
    return 0;
}

/**
 * int check_creditcard(char* cc)
 * Checks validity of a credit card number
 *
 * Args
 * * cc - Credit card number
 * Returns: 0 if valid, 1 if not
 */
int check_creditcard(char* cc) {
    if (check_blank(cc)) { 
        printf("Blank credit card number.\n");
        return 1;
    }
    
    //Variables for use with regex
    regex_t regex;
    int ret;

    //Compile regex
    ret = regcomp(&regex, "([[:digit:]]){16}|([[:digit:]]{4}-[[:digit:]]{4}-[[:digit:]]{4}-[[:digit:]]{4})", REG_EXTENDED);
    if (ret) {
        printf("CREDIT CARD REGEX FAILED TO COMPILE!\n");
        printf("Are you running on a modern POSIX system with support for extended regex?\n");
        return 0; //Prevent infinite loop if the regex fails
    }

    //Run regex
    ret = regexec(&regex, cc, 0, NULL, 0);
    regfree(&regex);
    if (!ret) {
        printf("CC - Success\n"); //TODO Remove
        return 0;
    } else if (ret == REG_NOMATCH) {
        printf("Invalid credit card format.\n");
        printf("len: %lu\n", strlen(cc)); //TODO Remove
        printf("Format: 1234567890123456 OR 1234-5678-9012-3456\n");
        return 1;
    } else {
        printf("Error with the regex\n");
        return 0;
    }
}

/**
 * int check_expiry(char* exp)
 * Checks for a valid format CC exp date
 *
 * Args
 * * exp - The expiry date to check
 * Returns: 0 on success, 1 on failure
 */
int check_expiry(char* exp) {
    if (check_blank(exp)) { 
        printf("Blank expiry date.\n");
        return 1;
    }
    
    //Variables for use with regex
    regex_t regex;
    int ret;

    //Compile regex
    ret = regcomp(&regex, "([[:digit:]]){2}/([[:digit:]]){2}/([[:digit:]]){4}", REG_EXTENDED);
    if (ret) {
        printf("EXPIRY REGEX FAILED TO COMPILE!\n");
        printf("Are you running on a modern POSIX system with support for extended regex?\n");
        return 0; //Prevent infinite loop if the regex fails
    }

    //Run regex
    ret = regexec(&regex, exp, 0, NULL, 0);
    regfree(&regex);
    if (!ret) {
        printf("EXP - Success\n"); //TODO Remove
        return 0;
    } else if (ret == REG_NOMATCH) {
        printf("Invalid expiry format.\n");
        printf("Format: MM/DD/YYYY\n");
        return 1;
    } else {
        printf("Error with the regex\n");
        return 0;
    }
}

/**
 * int check_zipcode(char* zipcode)
 * Checks for a valid zipcode, in short or extended form
 *
 * Args
 * * zipcode - The zipcode to check
 * Returns: 0 on success, 1 on failure
 */
int check_zipcode(char* zipcode) {
    if (check_blank(zipcode)) { 
        printf("Blank zipcode.\n");
        return 1;
    }
    
    //Variables for use with regex
    regex_t regex;
    int ret;

    //Compile regex
    ret = regcomp(&regex, "([[:digit:]]){5}|([[:digit:]]){5}-([[:digit:]]){4}", REG_EXTENDED);
    if (ret) {
        printf("ZIPCODE REGEX FAILED TO COMPILE!\n");
        printf("Are you running on a modern POSIX system with support for extended regex?\n");
        return 0; //Prevent infinite loop if the regex fails
    }

    //Run regex
    ret = regexec(&regex, zipcode, 0, NULL, 0);
    regfree(&regex);
    if (!ret) {
        printf("ZIP - Success\n"); //TODO Remove
        return 0;
    } else if (ret == REG_NOMATCH) {
        printf("Invalid zipcode format.\n");
        printf("Format: 12345 OR 12345-5678\n");
        return 1;
    } else {
        printf("Error with the regex\n");
        return 0;
    }
}

/**
 * int check_dollars(char* dollars)
 * Ensures the entered value is a valid monetary amount in USD.
 *
 * Args
 * * dollars - The amount of money to check
 * Returns: 0 on success, 1 on failure
 */
int check_dollars(char* dollars) {
    if (check_blank(dollars)) { 
        printf("Blank dollars value.\n");
        return 1;
    }
    
    //Variables for use with regex
    regex_t regex;
    int ret;

    //Compile regex
    //TODO This has a bug. Idk yet :/
    ret = regcomp(&regex, "^(\\$)([[:digit:]])+|^(\\$)([[:digit:]])+(\\.[[:digit:]][[:digit:]])", REG_EXTENDED);
    if (ret) {
        printf("DOLLARS REGEX FAILED TO COMPILE!\n");
        printf("Are you running on a modern POSIX system with support for extended regex?\n");
        return 0; //Prevent infinite loop if the regex fails
    }

    //Run regex
    ret = regexec(&regex, dollars, 0, NULL, 0);
    regfree(&regex);
    if (!ret) {
        printf("Dollars - Success\n"); //TODO Remove
        return 0;
    } else if (ret == REG_NOMATCH) {
        printf("Invalid monetary format.\n");
        printf("Format: $123.45\n");
        return 1;
    } else {
        printf("Error with the regex\n");
        return 0;
    }
}

/**
 * int check_email(char* email)
 * Checks for valid email format
 *
 * Args
 * * email - The email to check
 * Returns: 0 on success, 1 on failure
 */
int check_email(char* email) {
    if (check_blank(email)) { 
        printf("Blank email.\n");
        return 1;
    }
    
    //Variables for use with regex
    regex_t regex;
    int ret;

    //Compile regex
    //TODO
    ret = regcomp(&regex, "", REG_EXTENDED);
    if (ret) {
        printf("EMAIL REGEX FAILED TO COMPILE!\n");
        printf("Are you running on a modern POSIX system with support for extended regex?\n");
        return 0; //Prevent infinite loop if the regex fails
    }

    //Run regex
    ret = regexec(&regex, email, 0, NULL, 0);
    regfree(&regex);
    if (!ret) {
        printf("Email - Success\n"); //TODO Remove
        return 0;
    } else if (ret == REG_NOMATCH) {
        printf("Invalid email format.\n");
        return 1;
    } else {
        printf("Error with the regex\n");
        return 0;
    }
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

    //First and last name
    char* name;
    do {
        printf("Enter a first name and last name: ");
        name = get_input();
    } while (check_name(name));
    printf("Name: %s\n", name); //TODO Remove

    // Credit Card Number
    char* ccnum;
    do {
        printf("Enter a credit card #: ");
        ccnum = get_input();
    } while (check_creditcard(ccnum));
    printf("CC: %s\n", ccnum); //TODO Remove

    //Expiry date
    char* exp;
    do {
        printf("Enter an expiration number: ");
        exp = get_input();
    } while (check_expiry(exp));
    printf("ExpDate: %s\n", exp); //TODO Remove

    //Zipcode
    char* zipcode;
    do {
        printf("Enter a zip code: ");
        zipcode = get_input();
    } while (check_zipcode(zipcode));
    printf("ZIP: %s\n", zipcode);

    //Dollars
    char* dollars;
    do {
        printf("Enter a valid purchase amount in dollars: ");
        dollars = get_input();
    } while (check_dollars(dollars));
    printf("Dollars: %s\n", dollars); //TODO Remove

    //Email
    char* email;
    do {
        printf("Enter a valid email address: ");
        email = get_input();
    } while (check_email(email));
    printf("Email: %s\n", email); //TODO Remove

    //Free all the allocated data for shits and giggles
    if (name != NULL) {
        free(name);
    }

    if (ccnum != NULL) {
        free(ccnum);
    }

    if (exp != NULL) {
        free(exp);
    }

    if (zipcode != NULL) {
        free(zipcode);
    }

    if (dollars != NULL) {
        free(dollars);
    }

    if (email != NULL) {
        free(email);
    }
    return 0; 
}
