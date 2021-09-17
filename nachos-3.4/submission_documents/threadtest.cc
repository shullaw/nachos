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

// bool prog_select;  // PROJECT 1 TASK 2

void get_input(int);
void no_leak(char *);

int thread_count;
int shouts_count;
void no_leak(char *input)
{
    if (input)
    {
        delete[] input;
    }
}
void get_input(int idx)
{
    int c;
    static char *input = new char[MAXIMUM + 1](); // initialize to prevent null pointing
    int position = -1;
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
    while ((position++ < MAXIMUM) && (c = getchar()) != '\n' && c != EOF)
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
        if (total <= MAXIMUM) // while number of chars is less than maximum array size
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
        }
    }
}
void shout(int i)
{
    int waits_goal = (Random() % ((6) - 3)) + 3;
    int waits_done = 0;
    int shouts_done = 0;
    while (shouts_done < shouts_count)
    {
        while (waits_done < waits_goal)
        {
            waits_done++;
            printf("%s is yielding with %i shouts on iteration %i of loop.\n", currentThread->getName(), shouts_done, i);
            currentThread->Yield();
        }
        printf("%s : %i :  : %i :  : %i :  : %c\n", currentThread->getName(), waits_goal, waits_done, shouts_done, (Random() % (('Z') - 'A')) + 'A');
        shouts_done++;
        waits_done = 0;
    }
}

void ThreadTest()
{
    DEBUG('t', "Entering ThreadTest");
    if (which_func == 1)
    {
        Thread *t1 = new Thread("Forked Thread T1");
        t1->Fork(get_input, 1);
    }
    if (which_func == 2)
    {
        Project1 input;
        int thread_count = input.check_input(1);
        int shouts_count = input.check_input(2);
        printf("\n-----------------------START YOUR ENGINES----------------------------------------\n");
        printf("THREAD COUNT :::::::: %i\n", thread_count);
        printf("SHOUT *GOAL* :::::::: %i\n", shouts_count);
        for (int i = 0; i != thread_count; i++)
        {

            char rando = i + '0';
            char name[] = {'T', rando, '\0'};
            Thread *t = new Thread(name);
            printf("%s Created\n", t->getName());
            t->Fork(shout, i);
            printf("%s Forked\n", t->getName());
        }
    }
    // if (prog_select==false){
    //     printf("Missing -A.\n");
    // }
}
