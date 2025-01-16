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

// SAFE-GUARD: 
// It is good practice to apply safe-guards to header files
// Safe-guard's ensures only 1 copy of the header file is used in the project build
// The macro name should be mirroring the file name with _ for spaces, dots, etc.

// !!! DO NOT DELETE THE BELOW 2 LINES !!!
#ifndef CORE_H
#define CORE_H

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// 
// Copy your work done from Milestone #2 (core.h) into this file
// 
// NOTE:
// - Organize your functions into the below categories
// - Make sure the core.c file also lists these functions in the same order!
// - Be sure to provide a BRIEF comment for each function prototype
// - The comment should also be copied to the core.c function definition
//
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// defines/macros

#define DEFAULT_STRING_COUNT 50

//////////////////////////////////////
// USER INTERFACE FUNCTIONS
//////////////////////////////////////

// Clear the standard input buffer
void clearInputBuffer(void);

// Wait for user to input the "enter" key to continue
void suspend(void);


//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

//Gets a valid integer from user
int inputInt(void);

//Validates if value entered is greater than 0
int inputIntPositive(void);

//Checks if value is within permitted range
int inputIntRange(int lowerBound, int upperBound);

//Checks if string contains valid characters
char inputCharOption(const char validCharactersList[]);

//Checks if string contains valid characters: Special Case
char inputCharStringOption(const char validCharactersList[]);

//Check if string is within permitted range of characters
void inputCString(char* stringCharacters, int minCharacters, int maxCharacters);

//Check if string is within permitted range of characters: Specific for Phones
void inputPhone(char* stringCharacters, int minCharacters, int maxCharacters);

//Displays an array of 10-character digits as a formatted phone number
void displayFormattedPhone(const char* stringCharacters);

//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////
// !!! DO NOT DELETE THE BELOW LINE !!!
#endif // !CORE_H
