#include "get_input.h"

#include <stdio.h>
#include <stdlib.h> /* malloc, free, rand */
#include <assert.h> /* stop program if --> assertion == 0 */
#include <string.h> /* strcmp */

/* For this task, you must fork a single thread to a function that will prompt 
the user for arbitrary input.
You will then determine which of the following categories the input belongs in, 
and display output indicating such:
● Integer
● Decimal
● Negative Integer
● Negative Decimal
• Character
• Character String

Procedure
Have the user enter some arbitrary input and store it in a character array. 
Inspect each character and determine which category the input belongs to. 

You must consider the input as a whole; 
42 is a number,
42ASDF is not. 
3.14 is a decimal, 
-3.14 is a negative decimal, 
3.AD is neither. 

If the input belongs to multiple categories, display each category it belongs to.
For the purposes of this task, use the following definitions:
● A number can be an integer, a decimal, or a negative.
    ○ An integer is a sequence of 1 or more digits.
    ○ A decimal is a sequence of 1 or more digits followed by a period (‘.’) followed by
    a sequence of 1 or more digits.
    ○ A negative is a dash (‘-’) followed by an integer or decimal.
● A character or character string is anything that is not a number.
*/

#define MAXIMUM 10
#define SPACE 32
#define COMMA 44
#define DASH 45
#define DOT 46
#define FSLASH 47
#define ZERO 48
#define NINE 57
#define SEMICOLON 58
#define TILDA 126

void get_input();

int main()
{

    // assert(0);
    // printf("value of EOF is %i\n", EOF);     /* print the value of EOF */

    // char c;
    // // char s[1] = {'s'};  // this is a character --> 's'
    // char * s = 's';  // this is an integer --> 115
    // printf("%s\n", (char)s);
    void get_input()
    {
        int c;
        int position = -1;
        char input[MAXIMUM];
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

        while ((position++ <= MAXIMUM) && (c = getchar()) != '\n')
        {
            if (position == MAXIMUM)
            {
                break;
            }
            if (c >= ZERO && c <= NINE)
            { // checks for digit
                input[position] = c;
                ndigit++;
                total++;
            }
            else if (c == DASH && position != 0)
            {
                input[position] = c;
                nchar++;
                total++;
            }
            else if (c == DASH && position == 0)
            {
                input[position] = c;
                ndash++;
                total++;
            }
            else if (c == DOT)
            {
                input[position] = c;
                ndot++;
                total++;
            }
            else if (c >= SPACE && c <= FSLASH || c >= SEMICOLON && c <= TILDA)
            { // checks for "normal" ascii characters
                input[position] = c;
                nchar++;
                total++;
            }
        }

        if (total < MAXIMUM)
        {
            if (total == 1)
            {
                if (ndigit == 1)
                {
                    number = YES;
                    integer = YES;
                }
                else
                    character = YES;
            }
            else if (total > 1)
            {
                if (input[0] == DASH && nchar == 0 && ndigit >= 1 && input[1] >= ZERO && input[1] <= NINE)
                {
                    negative = YES;
                    if (ndot == 1)
                    {
                        number = YES;
                        decimal = YES;
                    }
                    else if (ndot == 0)
                    {
                        number = YES;
                        integer = YES;
                    }
                }
                else if (input[0] != DOT && nchar == 0 && input[1] >= ZERO && input[1] <= NINE)
                {
                    if (ndot == 1 && ndigit >= 1)
                    {
                        number = YES;
                        decimal = YES;
                    }
                    else if (ndot == 0 && ndigit >= 1)
                    {
                        number = YES;
                        integer = YES;
                    }
                }
                else
                    char_string = YES;
            }

            printf("input: ");
            for (int i = 0; input[i] != '\0'; i++)
            {
                printf("%d=%c ", input[i], input[i]);
            }
            printf("\nchars: %d, digits: %d, dots: %d, dashes: %d, total: %d", nchar, ndigit, ndot, ndash, total);
            printf("\nnumber: %d, integer: %d, negative: %d, decimal: %d, character: %d, char_string: %d\n", number, integer, negative, decimal, character, char_string);
        }
        else
            printf("Your input was too large.  Please limit input to %d\n", MAXIMUM);
    }


    printf("\n---------------------------------------------------------------");
    printf("\nPlease enter %d characters with your keyboard followed by the \"Enter\" key.\nPress \"Ctrl\" + \"c\" to exit the program.\n", MAXIMUM);
    get_input();

    return 0;
}
