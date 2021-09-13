// threadtest.cc
//	Simple test case for the threads assignment.
//
//	Create two threads, and have them context switch
//	back and forth between themselves by calling Thread::Yield,
//	to illustratethe inner workings of the thread system.
//
// Copyright (c) 1992-1993,2021 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "system.h"

// #include "check_input.h"  // PROJECT 1 TASK 2

//----------------------------------------------------------------------
// SimpleThread
// 	Loop 5 times, yielding the CPU to another ready thread
//	each iteration.
//
//	"which" is simply a number identifying the thread, for debugging
//	purposes.
//----------------------------------------------------------------------

// void SimpleThread(int which)
// {
//     int num;
// 
//     for (num = 0; num < 5; num++)   // HOMEWORK 1
//     {
//         printf("*** thread %d looped %d times\n", which, num);
//         currentThread->Yield();
//     }
// }
// HOMEWORK 1
void SimpleThreadOG(int which)
{
    printf("*** THIS IS FUNCTION: %d --> %s\n", (int) SimpleThreadOG, "SimpleThreadOG!");
    int start = 0;    
    int num;
    int limit = 5;

    for (num = start; num < limit; num++)   // HOMEWORK 1
    {
        printf("*** thread %d looped %d times\n", which, num);
    }
}
// HOMEWORK 1
void SimpleThreadYield(int which)
{
    printf("*** THIS IS FUNCTION: %d --> %s\n", (int) SimpleThreadYield, "SimpleThreadYield!");
    int start = 0;    
    int num;
    int limit = 5;   

    for (num = start; num < limit; num++)   // HOMEWORK 1
    {
        printf("*** thread %d looped %d times\n", which, num);
        currentThread->Yield();
        if (num==0) {
            printf("*** THIS IS FUNCTION: %d --> %s\n", (int) SimpleThreadYield, "SimpleThreadYield!");
        }
    }
    printf("*** FUNCTION: %d --> %s\n", (int) SimpleThreadYield, "SimpleThreadYield is complete!");
}
// HOMEWORK 1
void SimpleThreadPrint(int which)
{
    printf("*** THIS IS FUNCTION: %d --> %s\n", (int) SimpleThreadPrint, "SimpleThreadPrint!");
    printf("*** The user initialized which_func: %d\n", which_func);
}
char* check_input();
void shout(int user_input);
void get_input(int user_input);
void no_leak(char *);

#define MAXIMUM 128
#define SPACE 32
#define COMMA 44
#define DASH 45
#define DOT 46
#define FSLASH 47
#define ZERO 48
#define NINE 57
#define SEMICOLON 58
#define TILDA 126

char *input;

void no_leak(char * input) {
    delete [] input;
}
void get_input(int user_input)
{
    int c;
    int position = -1;
    char *input = new char[MAXIMUM + 1];
    int final;
    int ndash, ndot, ndigit, nchar, total;
    ndash = 0;
    ndot = 0;
    ndigit = 0;
    nchar = 0;
    total = 0;
    enum boolean
    {
        NO,
        YES
    };
    int number = NO, integer = NO, negative = NO, decimal = NO, character = NO, char_string = NO;

    printf("\n-----------------------TASK 1----------------------------------------");
    printf("\nPlease enter fewer than %d characters with your keyboard followed by the \"Enter\" key.\nPress \"Ctrl\" + \"c\" to exit the program.\n", MAXIMUM + 1);
    printf("If an odd character is shown (ex. press an arrow key) delete it with backspace or the program will exit upon execution.\n");
    printf("At the end of the program, the array created to hold input will be deleted.\n");
    while ((position++ <= MAXIMUM) && (c = getchar()) != '\n' && c != EOF)
    {
        if (position == MAXIMUM)
        {
            break;
        }
        if (c >= ZERO && c <= NINE) // if digit between 0-9
        {                           // checks for digit
            input[position] = c;
            ndigit++;
            total++;
        }
        else if (c == DASH && position == 0 && ndash == 0) // if - in first position; possible negative
        {
            input[position] = c;
            ndash++;
            total++;
        }
        else if (c == DASH && position != 0) // if - in first position; possible negative
        {
            input[position] = c;
            nchar++;
            total++;
        }
        else if (c == DOT && position != 0 && ndot == 0) // if . (decimal)
        {
            input[position] = c;
            ndot++;
            total++;
        }
        else if (c == DOT && position == 0) // if . (decimal)
        {
            input[position] = c;
            nchar++;
            total++;
        }
        else if (c >= SPACE && c <= FSLASH || c >= SEMICOLON && c <= TILDA && c != DOT && c != DASH) // checks for "normal" ascii characters
        {
            input[position] = c;
            nchar++;
            total++;
        }
        else if (sizeof(c) > 1)
        {
            while (c != '\n')
            {
                c = getchar();
            }
            printf("Not accepting weird stuff.  Exiting program.\n");
            position = 0;
            break;
        }
    }
    if (position != 0)
    {
        input[position] = '\0';
        final = input[--position];                     // last position in array
        if (final == DOT && input[++position] == '\0') // if . (decimal)
        {
            if (ndot == 1)
            {
                nchar++;
                ndot--;
            }
            else if (ndot > 1)
            {
                ndot *= 2;
                nchar += ndot;
                ndot = 0;
            }
            if (input[0] == DASH)
            {
                nchar++;
                ndash--;
            }
        }
        if (total < MAXIMUM) // while number of chars is less than maximum array size
        {
            if (total == 1) // either char or int
            {
                if (ndigit == 1) // if one digit; int
                {
                    number = YES;
                    integer = YES;
                }
                else
                    character = YES; // else; char
            }
            else if (total > 1) // if more than one char
            {
                // if first position is -, and no alpha, and next position is digit
                if (input[0] == DASH && nchar == 0 && ndigit >= 1 && input[1] >= ZERO && input[1] <= NINE)
                {
                    // if a decimal with digit at final position
                    if (ndot == 1 && final != DOT) // float
                    {
                        number = YES;
                        decimal = YES;
                        negative = YES;
                    }
                    else if (ndot == 0) // if no decimal, integer
                    {
                        number = YES;
                        integer = YES;
                        negative = YES;
                    }
                }
                // if first position is not decimal, and no chars, and next position is digit
                else if (input[0] != DOT && nchar == 0 && input[1] >= ZERO && input[1] <= NINE && final != DOT)
                {
                    if (ndot == 1 && ndigit >= 1) // float
                    {
                        number = YES;
                        decimal = YES;
                    }
                    else if (ndot == 0 && ndigit >= 1) // integer
                    {
                        number = YES;
                        integer = YES;
                    }
                }
                else
                {
                    char_string = YES; // we've exhausted all posibilities? so it's a string of chars
                    nchar += (ndigit + ndash + ndot);
                    ndigit = 0;
                    ndot = 0;
                    ndash = 0;
                }
            }
            if (total == 0)
            {
                printf("You enter %d characters\n", total);
            }
            else if (total >= 0)
            {
                printf("input: ");
                for (int i = 0; i < total; i++)
                {
                    printf("%d=%c ", input[i], input[i]);
                }
                printf("\nchars: %d, digits: %d, dots: %d, dashes: %d, total: %d", nchar, ndigit, ndot, ndash, total);
                printf("\nnumber: %d, integer: %d, negative: %d, decimal: %d, character: %d, char_string: %d\n", number, integer, negative, decimal, character, char_string);
            }
            else
            {
                printf("\nYour input was too large.  Please limit input to %d.\n", MAXIMUM);
            }
        }
    }
    no_leak(input); // memory leak prevented
}
char* check_input()
{
    int c;
    int position = -1;
    char *input = new char[MAXIMUM + 1];
    int final;
    int ndash, ndot, ndigit, nchar, total;
    ndash = 0;
    ndot = 0;
    ndigit = 0;
    nchar = 0;
    total = 0;
    enum boolean
    {
        NO,
        YES
    };
    int number = NO, integer = NO, negative = NO, decimal = NO, character = NO, char_string = NO;

    printf("\n-----------------------TASK 2----------------------------------------");
    printf("\nPlease enter fewer than %d characters with your keyboard followed by the \"Enter\" key.\nPress \"Ctrl\" + \"c\" to exit the program.\n", MAXIMUM + 1);
    printf("If an odd character is shown (ex. press an arrow key) delete it with backspace or the program will exit upon execution.\n");
    printf("At the end of the program, the array created to hold input will be deleted.\n");
    printf("Enter Thread Count and Shout Number as two integers separated by a space, e.g. \"ThreadCount ShoutNumber\" == \"3 9\" and press \"Enter\"\n");
    while ((position++ <= MAXIMUM) && (c = getchar()) != '\n' && c != EOF)
    {
        if (position == MAXIMUM)
        {
            break;
        }
        if (c >= ZERO && c <= NINE) // if digit between 0-9
        {                           // checks for digit
            input[position] = c;
            ndigit++;
            total++;
        }
        else if (c == DASH && position == 0 && ndash == 0) // if - in first position; possible negative
        {
            input[position] = c;
            ndash++;
            total++;
        }
        else if (c == DASH && position != 0) // if - in first position; possible negative
        {
            input[position] = c;
            nchar++;
            total++;
        }
        else if (c == DOT && position != 0 && ndot == 0) // if . (decimal)
        {
            input[position] = c;
            ndot++;
            total++;
        }
        else if (c == DOT && position == 0) // if . (decimal)
        {
            input[position] = c;
            nchar++;
            total++;
        }
        else if (c >= SPACE && c <= FSLASH || c >= SEMICOLON && c <= TILDA && c != DOT && c != DASH) // checks for "normal" ascii characters
        {
            input[position] = c;
            nchar++;
            total++;
        }
        else if (sizeof(c) > 1)
        {
            while (c != '\n')
            {
                c = getchar();
            }
            printf("Not accepting weird stuff.  Exiting program.\n");
            position = 0;
            break;
        }
    }
    if (position != 0)
    {
        input[position] = '\0';
        final = input[--position];                     // last position in array
        if (final == DOT && input[++position] == '\0') // if . (decimal)
        {
            if (ndot == 1)
            {
                nchar++;
                ndot--;
            }
            else if (ndot > 1)
            {
                ndot *= 2;
                nchar += ndot;
                ndot = 0;
            }
            if (input[0] == DASH)
            {
                nchar++;
                ndash--;
            }
        }
        if (total < MAXIMUM) // while number of chars is less than maximum array size
        {
            if (total == 1) // either char or int
            {
                if (ndigit == 1) // if one digit; int
                {
                    number = YES;
                    integer = YES;
                }
                else
                    character = YES; // else; char
            }
            else if (total > 1) // if more than one char
            {
                // if first position is -, and no alpha, and next position is digit
                if (input[0] == DASH && nchar == 0 && ndigit >= 1 && input[1] >= ZERO && input[1] <= NINE)
                {
                    // if a decimal with digit at final position
                    if (ndot == 1 && final != DOT) // float
                    {
                        number = YES;
                        decimal = YES;
                        negative = YES;
                    }
                    else if (ndot == 0) // if no decimal, integer
                    {
                        number = YES;
                        integer = YES;
                        negative = YES;
                    }
                }
                // if first position is not decimal, and no chars, and next position is digit
                else if (input[0] != DOT && nchar == 0 && input[1] >= ZERO && input[1] <= NINE && final != DOT)
                {
                    if (ndot == 1 && ndigit >= 1) // float
                    {
                        number = YES;
                        decimal = YES;
                    }
                    else if (ndot == 0 && ndigit >= 1) // integer
                    {
                        number = YES;
                        integer = YES;
                    }
                }
                else
                {
                    char_string = YES; // we've exhausted all posibilities? so it's a string of chars
                    nchar += (ndigit + ndash + ndot);
                    ndigit = 0;
                    ndot = 0;
                    ndash = 0;
                }
            }
            if (total == 0)
            {
                printf("You enter %d characters\n", total);
            }
            else if (total >= 0)
            {
                printf("input: ");
                for (int i = 0; i < total; i++)
                {
                    printf("%d=%c ", input[i], input[i]);
                }
                printf("\nchars: %d, digits: %d, dots: %d, dashes: %d, total: %d", nchar, ndigit, ndot, ndash, total);
                printf("\nnumber: %d, integer: %d, negative: %d, decimal: %d, character: %d, char_string: %d\n", number, integer, negative, decimal, character, char_string);
            }
            else
            {
                printf("\nYour input was too large.  Please limit input to %d.\n", MAXIMUM);
            }
        }
    }
    return input;
}
void shout(int user_input) {
    char * input;
    if (input = check_input()) {
        while (input) {
        printf("%s\n", input);
        no_leak(input);
        }
    }
    else if (input) {
        no_leak(input);
    }
}
//----------------------------------------------------------------------
// ThreadTest
// 	Invoke a test routine.
//----------------------------------------------------------------------

void ThreadTest()
{
    DEBUG('t', "Entering ThreadTest");

    Thread *t1 = new Thread("forked thread T1");

    if (which_func == 1){
        t1->Fork(get_input, 1);
    }
    if (which_func == 2) {
        t1->Fork(shout, 1);
    }
}
