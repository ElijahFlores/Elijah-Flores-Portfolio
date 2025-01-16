/*/////////////////////////////////////////////////////////////////////////
                        Assignment 1 - Milestone 3
Full Name  : Elijah Alton Flores
Student ID#: 106480239
Email      : eaflores1@myseneca.ca
Section    : ZGG

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
/////////////////////////////////////////////////////////////////////////*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include "core.h"

//////////////////////////////////////
// USER INTERFACE FUNCTIONS
//////////////////////////////////////

// Clear the standard input buffer
void clearInputBuffer(void)
{
    // Discard all remaining char's from the standard input buffer:
    while (getchar() != '\n')
    {
        ; // do nothing!
    }
}

// Wait for user to input the "enter" key to continue
void suspend(void)
{
    printf("<ENTER> to continue...");
    clearInputBuffer();
    putchar('\n');
}


//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

//
// Copy your work done from Milestone #2 (core.c) into this file
// - Organize your functions in the same order as they are listed in the core.h file
//

//Gets a valid integer from user
int inputInt(void)
{
    //Variable Declaration
    char newLine = 'x';
    int value;

    do
    {
        scanf("%d%c", &value, &newLine);
        if (newLine == '\n')
        {
            return value;
            break;
        }
        else
        {
            clearInputBuffer();
            printf("Error! Input a whole number: ");
        }
    } while (1);

    return 0;
}

//Validates if value entered is greater than 0
int inputIntPositive(void)
{
    int value;
    char newLine = 'x';

    do
    {
        scanf("%d%c", &value, &newLine);
        if (newLine == '\n')
        {
            if (value <= 0)
            {
                printf("ERROR! Value must be > 0: ");
            }
            else
            {
                return value;
                break;
            }
        }
        else
        {
            clearInputBuffer();
            printf("Error! Input a whole number: ");
        }
    } while (1);

    return 0;
}

//Checks if value is within permitted range
int inputIntRange(int lowerBound, int upperBound)
{
    //Variable Declaration
    char newLine = 'x';
    int value;

    do
    {
        scanf("%d%c", &value, &newLine);
        if (newLine == '\n')
        {
            if (lowerBound <= value && upperBound >= value)
            {
                return value;
                break;
            }
            else
            {
                printf("ERROR! Value must be between %d and %d inclusive: ", lowerBound, upperBound);
            }

        }
        else
        {
            clearInputBuffer();
            printf("Error! Input a whole number: ");
        }
    } while (1);

    return 0;
}

//Checks if string contains valid characters
char inputCharOption(const char validCharactersList[])
{
    char value;
    int i, validFlag = 0;
    do
    {
        scanf(" %c", &value);
        for (i = 0; validCharactersList[i] != '\0'; i++)
        {
            if (value == validCharactersList[i])
            {
                validFlag = 1;
                return value;
            }
        }

        if (validFlag == 0)
        {
            printf("ERROR: Character must be one of [%s]: ", validCharactersList);
        }
    } while (validFlag == 0);

    return value;
}

//Checks if string contains valid characters: Special Case
char inputCharStringOption(const char validCharactersList[])
{
    char value[DEFAULT_STRING_COUNT] = { 0 };
    int i, validFlag = 0;
    do
    {
        scanf(" %s", value);
        for (i = 0; validCharactersList[i] != '\0'; i++)
        {
            if (strcmp(&validCharactersList[i], value) == 0)
            {
                validFlag = 1;
            }
            else if (validCharactersList[i] == value[i] && strlen(value) == 1)
            {
                validFlag = 1;
            }
        }
        if (validFlag == 0 || strlen(value) > 1)
        {
            printf("ERROR: Character must be one of [%s]: ", validCharactersList);
        }
        else
        {
            return value[0];
        }
    } while (validFlag == 0);

    return value[0];
}

//Check if string is within permitted range of characters
void inputCString(char* stringCharacters, int minCharacters, int maxCharacters)
{
    int charCount = 0, i;
    char value[DEFAULT_STRING_COUNT];
    int stringCount = 0;

    do
    {
        charCount = 0;
        scanf(" %[^\n]", value);

        for (i = 0; value[i] != '\0'; i++)
        {
            charCount++;
        }
        if (minCharacters == maxCharacters && maxCharacters != charCount)
        {
            printf("ERROR: String length must be exactly %d chars: ", maxCharacters);
        }
        else if (charCount > maxCharacters)
        {
            printf("ERROR: String length must be no more than %d chars: ", maxCharacters);
        }
        else if (charCount < minCharacters)
        {
            printf("ERROR: String length must be between %d and %d chars: ", minCharacters, maxCharacters);
        }
        else
        {
            *stringCharacters = value[maxCharacters];
            for (i = 0; value[i] != '\0'; i++)
            {
                stringCount++;
                if (strlen(stringCharacters) > stringCount)
                {
                    stringCharacters[stringCount] = '\0';
                }
                stringCharacters[i] = value[i];
            }
            if (strlen(stringCharacters) > strlen(value))
            {
                stringCharacters[strlen(value)] = '\0';
            }
            break;
        }
    } while (1);

}

//Check if string is within permitted range of characters: Specific for Phones
void inputPhone(char* stringCharacters, int minCharacters, int maxCharacters)
{
    int charCount = 0, i;
    char value[DEFAULT_STRING_COUNT];

    do
    {
        charCount = 0;
        scanf(" %[^\n]", value);

        for (i = 0; value[i] != '\0'; i++)
        {
            charCount++;
        }
        if (minCharacters == maxCharacters && maxCharacters != charCount)
        {
            printf("Invalid %d-digit number! Number: ", maxCharacters);
        }
        else if (charCount > maxCharacters)
        {
            printf("Invalid %d-digit number! Number: ", maxCharacters);
        }
        else if (charCount < minCharacters)
        {
            printf("Invalid %d-digit number!: Number: ", maxCharacters);
        }
        else
        {
            *stringCharacters = value[maxCharacters];
            for (i = 0; value[i] != '\0'; i++)
            {
                stringCharacters[i] = value[i];
            }
            break;
        }
    } while (1);

}

//Displays an array of 10-character digits as a formatted phone number
void displayFormattedPhone(const char* stringCharacters)
{
    if (stringCharacters != NULL)
    {
        int charCount = 0, validFlag = 1, i, j;
        char validCharactersList[10 + 1] = "0123456789";
        for (i = 0; stringCharacters[i] != '\0' && validFlag == 1; i++)
        {
            validFlag = 0;
            for (j = 0; validCharactersList[j] != '\0' && validFlag == 0; j++)
            {
                if (stringCharacters[i] == validCharactersList[j])
                {
                    validFlag = 1;
                }
            }
        }

        for (i = 0; stringCharacters[i] != '\0'; i++)
        {
            charCount++;
        }
        if (validFlag == 1 && charCount == 10)
        {
            for (i = 0; stringCharacters[i] != '\0'; i++)
            {
                if (i == 0)
                {
                    printf("(%c", stringCharacters[i]);
                }
                else if (i == 2)
                {
                    printf("%c)", stringCharacters[i]);
                }
                else if (i == 5)
                {
                    printf("%c-", stringCharacters[i]);
                }
                else
                {
                    printf("%c", stringCharacters[i]);
                }
            }
        }
        else
        {
            printf("(___)___-____");
        }
    }
    else
    {
        printf("(___)___-____");
    }

}



//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////
