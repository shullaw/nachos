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

void get_input(int user_input);

void get_input(int user_input)
{
    int c;
    int position = -1;
    char *input = new char[MAXIMUM+1];
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
    while ((position++ <= MAXIMUM) && (c = getchar()) != '\n')
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
        else if (c == DASH && position == 0) // if - in first position; possible negative
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
        else if (c == DOT && position != 0) // if . (decimal)
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
    }
    final = input[--position];                     // last position in array
    if (final == DOT && input[++position] == '\0') // if . (decimal)
    {
        if (ndot == 1){
        nchar++;
        ndot--;
        }
        else {
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
                char_string = YES; // we've exhausted all posibilities? so it's a string of chars
                nchar += ndigit + ndash;
                ndigit = 0;
                ndash = 0;
        }
        if (total == 0)
        {
            printf("You enter %d characters\n", total);
        }
        else if (total >= 0)
        {
            printf("input: ");
            for (int i = 0; input[i] != '\0'; i++)
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
    delete input;  // memory leak prevented
}