// threadtest.cc PROJECT2

// Copyright (c) 1992-1993,2021 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "system.h"
// #include "synch.h" // PROJECT2

//-----------------------------GLOBALS--------------------------------//

//-----------------------------TASK 1 & 2--------------------------------//
int num_phi;
int meal_goal;
int total_eaten;
int room_count;
char input[6];
bool stick[10001];
Semaphore **sticks;
int total_sit;
int idx = 0;
//-----------------------------TASK 1 & 2-------------------------------//
//-----------------------------TASK 3----------------------------------//
int num_ppl;
int num_slt;
int num_msg;
char ***mailbox = new char **[10001];
Semaphore **PostOffice = new Semaphore *[10001];
int msg_goal;
int msg_total;
int left;
//----------------------------TASK 3----------------------------------//
//----------------------------TASK 4----------------------------------//
int nR;
int nW;
int N;
int writer_count;
bool Wait;
Semaphore *mutex = new Semaphore("mutex", 1);
Semaphore *room_empty;
Semaphore *in = new Semaphore("in", 1);
Semaphore *out = new Semaphore("out", 1);
Semaphore *wrt = new Semaphore("wrt", 0);
Semaphore *wait = new Semaphore("wait", 0);

int thread_count;
int shouts_count;

//----------------------------TASK 4----------------------------------//

//-----------------------------GLOBALS--------------------------------//

//-----------------------------INPUT--------------------------------//

int get_one(char *input)
{
    if (fgets(input, 3, stdin) == 0)
    {
        printf("Invalid Input.\n");
        return 0;
    }
    if (strlen(input) > 2 || atoi(input) > 9 || atoi(input) < 1)
    {
        printf("Invalid Input.\n");
        return 0;
    }
    else
    {
        return atoi(input);
    }
}

int get_big(char input[])
{
    int num;
    if (fgets(input, 7, stdin) == 0)
    {
        printf("Invalid Input.\n");
        return 0;
    }
    else if (strlen(input) > 6 || atoi(input) > 10000 || atoi(input) < 1)
    {
        printf("Invalid Input.\n");
        return 0;
    }
    else
    {

        for (int i = 0; i < strlen(input) - 1 && input[i] != 0; i++)
        {
            if (input[i] < 48 || input[i] > 57)
            {
                printf("Invalid Input.\n");
                return 0;
            }
        }
    }
    num = atoi(input);
    return num;
}

void prompt()
{
    printf("Enter the number of philosophers (>1): ");
    num_phi = get_big(input);
    if (num_phi > 1)
    {
        printf("\n%d\n", num_phi);
        printf("\nEnter the number of meals: ");
        meal_goal = get_big(input);
        if (meal_goal)
        {
            printf("\n%d\n ", meal_goal);
        }
        else
        {
            num_phi = 0;
            meal_goal = 0;
            printf("Invalid Input.\n");
        }
    }
    else
    {
        num_phi = 0;
        meal_goal = 0;
        printf("Invalid Input.\n");
    }
}

int prompt2(int x)
{
    if (x == 0)
        printf("Enter the number of people (>0): ");
    if (x == 1)
        printf("\nEnter the number of slots (>0): ");
    if (x == 2)
        printf("\nEnter the number of messages (>0): ");
    int global = get_big(input);
    if (!global)
    {
        printf("Invalid Input.\n");
    }
    return global;
}

int prompt3(int x, int y)
{
    while (!x)
    {
        x = prompt2(y);
    }
    printf("%d\n", x);
    return x;
}

int prompt4(int x)
{
    if (x == 0)
        printf("Enter the number of Readers (>0): ");
    if (x == 1)
        printf("\nEnter the number of Writers (>0): ");
    if (x == 2)
        printf("\nEnter the maximum Readers at once (>0): ");
    int global = get_big(input);
    if (!global)
    {
        printf("Invalid Input.\n");
    }
    return global;
}

int prompt5(int x, int y)
{
    while (!x)
    {
        x = prompt4(y);
    }
    printf("%d\n", x);
    return x;
}
void prompt6()
{
    printf("Enter the number of threads (>1): ");
    thread_count = get_big(input);
    if (thread_count > 1)
    {
        printf("\n%d\n", thread_count);
        printf("\nEnter the number of shouts (>1): ");
        shouts_count = get_big(input);
        if (shouts_count)
        {
            printf("\n%d\n ", shouts_count);
        }
        else
        {
            thread_count = 0;
            shouts_count = 0;
            printf("Invalid Input.\n");
        }
    }
    else
    {
        thread_count = 0;
        shouts_count = 0;
        printf("Invalid Input.\n");
    }
}

//-----------------------------INPUT--------------------------------//

//-----------------------------TASK 1--------------------------------//
void busy_dinner(int phi_ID)
{

    int right = phi_ID;
    int left = (phi_ID + 1) % num_phi;
    bool holding_left = false;
    bool holding_right = false;
    int my_meals = 0;
    bool sitting = false;

    printf("Philosopher %d entered.\n", phi_ID);
    room_count++;

    while (room_count != num_phi) // while all phi not in room
    {
        currentThread->Yield();
    }

    sitting = true;
    total_sit++;
    while (total_sit != num_phi)
    {
        currentThread->Yield();
    }
    printf("Philosopher %d sat down.\n", phi_ID);

    while (meal_goal >= total_eaten)
    {

        if (stick[left] && stick[right]) // if l and r avail PICK UP STICKS
        {
            stick[left] = false; // take left
            printf("Philosopher %d has chopstick %d (LEFT).\n", phi_ID, left);
            holding_left = true;
            // currentThread->Yield();
            stick[right] = false; //take right
            printf("Philosopher %d has chopstick %d (RIGHT).\n", phi_ID, right);
            holding_right = true;
            // currentThread->Yield();

            int eating = (Random() % (6 - 3) + 3);
            if (meal_goal > total_eaten) // if meal goal not met EAT
            {
                total_eaten++;
                my_meals++;
                printf("Philosopher %d is EATING %d times.\n", phi_ID, eating);
                while (eating-- > 0 && meal_goal > total_eaten)
                {
                    currentThread->Yield();
                }
                if (meal_goal >= total_eaten) // goal not met, PUT DOWN STICKS AND THINK
                {
                    /* i originally had the philos eating a "random amount of times", 
                    and I'm not going back and breaking anything */

                    printf("Philosopher %d is STOPPED EATING.\n", phi_ID);
                    stick[left] = true; // left avail
                    printf("Philosopher %d has dropped chopstick %d (LEFT).\n", phi_ID, left);
                    holding_left = false; // not holding
                    stick[right] = true;  // right avail
                    printf("Philosopher %d has dropped chopstick %d (RIGHT).\n", phi_ID, right);
                    holding_right = false; // not holding
                    int thinking = (Random() % (6 - 3) + 3);
                    printf("1Philosopher %d is THINKING %d times.\n", phi_ID, thinking);
                    while (thinking-- > 0)
                    {
                        currentThread->Yield();
                    }
                }
            }
            else // If meal goal met, PUT DOWN STICKS
            {
                printf("Meal goal met.\n");
                printf("Philosopher %d is STOPPED EATING.\n", phi_ID);
                stick[left] = true; // left avail
                printf("Philosopher %d has dropped chopstick %d (LEFT).\n", phi_ID, left);
                holding_left = false; // not holding
                stick[right] = true;  // right avail
                printf("Philosopher %d has dropped chopstick %d (RIGHT).\n", phi_ID, right);
                holding_right = false; // not holding
                int thinking = (Random() % (6 - 3) + 3);
                printf("2Philosopher %d is THINKING %d times.\n", phi_ID, thinking);
                while (thinking-- > 0)
                {
                    currentThread->Yield();
                }
                break;
            }
        }
        else // no sticks available THINK
        {
            int thinking = (Random() % (6 - 3) + 3);
            printf("No sticks available.  Philosopher %d is THINKING %d times.\n", phi_ID, thinking);
            while (thinking-- > 0)
            {
                currentThread->Yield();
            }
        }
    }
    if (meal_goal == total_eaten)
    {
        if (holding_left || holding_right)
        {
            stick[left] = true; // left avail
            printf("Philosopher %d has dropped chopstick %d (LEFT).\n", phi_ID, left);
            holding_left = false; // not holding
            stick[right] = true;  // right avail
            printf("Philosopher %d has dropped chopstick %d (RIGHT).\n", phi_ID, right);
            holding_right = false; // not holding

            int thinking = (Random() % (6 - 3) + 3);
            printf("Philosopher %d is THINKING %d times.\n", phi_ID, thinking);
            while (thinking-- > 0)
            {
                currentThread->Yield();
            }
        }
        if (sitting)
        {
            sitting = false;
            total_sit--;
            printf("Philosopher %d STOOD UP.\n", phi_ID);
        }
    }
    while (total_sit > 0)
    {
        // if (meal_goal == total_eaten)
        // {
        //     break;
        // }
        currentThread->Yield(); // wait for other philos
    }
    printf("Philosopher %d EXITING with %d meals of %d total of %d goal.\n", phi_ID, my_meals, total_eaten, meal_goal);
}
//-----------------------------TASK 1--------------------------------//
//-----------------------------TASK 2--------------------------------//
void sem_dinner(int phi_ID)
{
    int right = phi_ID;
    int left = (phi_ID + 1) % num_phi;
    int my_meals = 0;
    bool sitting = false;

    printf("Philosopher %d entered.\n", phi_ID);
    room_count++;

    while (room_count != num_phi) // while all have no entered, wait
    {
        currentThread->Yield(); // not sharing a resource here, so we loop (wait for all philos to enter)
    }

    sitting = true;
    total_sit++;
    printf("Philosopher %d sat down.\n", phi_ID);
    while (total_sit != num_phi)
    {
        currentThread->Yield(); // still not sharing a resource, wait for everyone to sit
    }

    while (meal_goal > total_eaten)
    {
        sticks[left]->P(); // initially 1 (>0), so decrement (no waiting)
        printf("Philosopher %d has chopstick %d (LEFT).\n", phi_ID, left);
        // currentThread->Yield();
        sticks[right]->P(); // if it was <=0 then wait.... for ->V()
        printf("Philosopher %d has chopstick %d (RIGHT).\n", phi_ID, right);
        // currentThread->Yield();
        int eating = (Random() % (6 - 3) + 3);

        if (meal_goal > total_eaten)
        {
            printf("Philosopher %d is EATING %d times.\n", phi_ID, eating);
            my_meals++;
            total_eaten++; // A philosopher will have finished eating 1 meal after his/her 3-6 cycles of eating.
            while (eating-- > 0 && meal_goal > total_eaten)
            {
                currentThread->Yield();
            }
        }
        else
        {
            printf("Philosopher %d is STOPPED EATING.\n", phi_ID); // meal goal met
            currentThread->Yield();
        }
        sticks[left]->V(); // increment and allow next in line to access
        printf("Philosopher %d has dropped chopstick %d (LEFT).\n", phi_ID, left);
        sticks[right]->V(); // increment and allow next in line to access
        printf("Philosopher %d has dropped chopstick %d (RIGHT).\n", phi_ID, right);
        int thinking = (Random() % (6 - 3) + 3);
        printf("Philosopher %d is THINKING %d times.\n", phi_ID, thinking);
        while (thinking-- > 0)
        {
            currentThread->Yield();
        }
    }
    printf("Meal goal met.\n"); // this will print for any philo that was stuck in the loop at meal goal
    sitting = false;
    total_sit--;
    printf("Philosopher %d STOOD UP.\n", phi_ID);

    while (total_sit > 0)
    {
        currentThread->Yield(); // wait for other philos
    }
    printf("Philosopher %d EXITING with %d meals of %d total of %d goal.\n", phi_ID, my_meals, total_eaten, meal_goal);
    printf("Zoom count: %d\n", --room_count);
}
//-----------------------------TASK 2--------------------------------//
//-----------------------------TASK 3--------------------------------//

int compose_note()
{
    int note = (Random() % ('G' - 'A') + 'A');
    // printf("\"Dear P %d, my favorite chord is %c\"", person, note);
}

int rando(int id)
{
    int rcvr = (Random() % num_ppl);
    while (id == rcvr)
    {
        rcvr = (Random() % num_ppl);
    }
    return rcvr;
}
void mail_func(int P) // For this task, the mailboxes are the critical resource that must be protected via synchronization
{
    // /* V() == FREEING SLOT when message READ.
    // --------------------------------------
    // P() == TAKING SLOT when message INSERT.*/

    left++;
    // // begin
    while (num_msg > msg_total)
    {

        printf("P %d Entered the Post Office.\n", P); // PostOffice walking in (STEP 1)
        printf("P %d Checks mailbox.\n", P);
        for (int i = 0; i < num_slt; i++) // check all slots (STEP 5)
        {
            // printf("slot[i]: %s\n", mailbox[P][i]);
            if (mailbox[P][i] != "0")
            {
                printf("P %d has 1 note and will now read, V(), Yield, Repeat.\n", P);
                printf("P %d reads \"Dear P %d, my favorite chord is %c\"\n", P, P, mailbox[P][i]);
                mailbox[P][i] = "0";    // empty the slot
                PostOffice[P]->V();     // n>0 so --> (STEP 3)
                currentThread->Yield(); // (STEP 4)
                printf("P %d now claims %d\n", P, P);
            }
        }
        printf("P %d Mailbox is empty; composing note.\n", P);
        int rcvr = rando(P);
        printf("rcvr: %d\n", rcvr);
        PostOffice[rcvr]->V(); // claim other persons mail box
        printf("P %d now called P() on P %d\n", P, rcvr);
        int note = (Random() % ('G' - 'A') + 'A');
        printf("P %d tries to send \"Dear P %d, my favorite chord is %c\"\n", P, rcvr, note);
        bool sent = false;
        if (msg_total < num_msg)
        {
            for (int i = 0; i < num_slt; i++)
            {
                if (mailbox[rcvr][i] == "0" && (msg_total < num_msg))
                {
                    mailbox[rcvr][i] = (char *)note; // (STEP 6)
                    printf("P %d sends \"Dear P %d, my favorite chord is %c\"\n", P, rcvr, note);
                    PostOffice[rcvr]->P(); // claim other persons mail box (STEP 7)
                    sent = true;
                    break;
                }
                else
                {
                    printf("P %d has a full mail box.\n", mailbox[rcvr]);
                    sent = false;
                    break;
                }
            }
            if (sent && (msg_total < num_msg))
            {
                msg_total++;
                sent = false;
            }
        }
        printf("P %d leaves.\n", P);
        int walk = (Random() % (6 - 3) + 3);
        while (walk-- > 0)
        {
            currentThread->Yield();
        }
    }
    left--;
    if (left == 0)
    {
        printf("%d of %d messages sent.\n", msg_total, num_msg);
    }
}
//-----------------------------TASK 3--------------------------------//
//-----------------------------TASK 4--------------------------------//
void W(int w)
{
    // printf("Writer %d is TRYING to ENTER the room.\n", w);
    // writer->P();  // lock
    // writer_count++;
    // printf("Writer %d is WRITING in the room.\n", w);
    // currentThread->Yield();
    // writer_count--;
    // printf("Writer %d is LEAVING the room.\n", w);
    // if (writer_count > 1)
    // mutex->P();  // lock

    if (room_count==writer_count) room_empty->V();
    else
    {
        mutex->V();
    }
    room_empty->P(); // reader waits
    printf("Writer %d is WRITING the room.\n", w);
    printf("Writer %d is LEAVING the room.\n", w);
    room_empty->V();
}
void R(int r)
{ /*Readers only read the information from the file and does not change file contents. 
    Writers can change the file contents. The basic synchronization constraint is the 
    any number of readers should be able to access the file at the same time, but only 
    ONE WRITER CAN WRITE to the file at a time (WITHOUT ANY READERS). 
    nREAD -> (1)WRITE -> nREAD -> (1)WRITE -> ... -> nREAD -> (1)WRITE.*/

    printf("Reader %d is TRYING to enter the room\n", r);
    mutex->P(); // decrement && lock
    if (room_count < N)
    {
        room_count++;
        if (room_count == 1)
            room_empty->P();
        mutex->V(); // unlock
        printf("Reader %d is READING in the room.\n", r);
        currentThread->Yield();
        printf("Reader %d is LEAVING the room.\n", r);
        mutex->P(); // decrement && lock
        room_count--;
        if (room_count == 0)
            room_empty->V(); // unlock
        mutex->V();
    }
    else
    {
        room_empty->V();
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
        shouts_done++;
        waits_done = 0;
    }
            printf("%s : %i :  : %i :  : %i :  : %c\n", currentThread->getName(), waits_goal, waits_done, shouts_done, (Random() % (('Z') - 'A')) + 'A');

}


//-----------------------------TASK 4--------------------------------//
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
void ThreadTest()
{

    DEBUG('t', "Entering ThreadTest");

    // TASK 1
    if (which_func == 3)
    {
        printf("\n=========Task 1 Dining Philosopher (Busy Waiting)=========.\n\n");
        prompt();
        Thread **threads = new Thread *[num_phi];
        for (int i = 0; i < num_phi; i++)
        {
            stick[i] = true;
        }
        for (int i = 0; i < num_phi; i++)
        {
            Thread *t = new Thread("Philo");
            t->Fork(busy_dinner, i);
        }
    }
    // TASK 2
    else if (which_func == 4)
    {
        printf("\n=========Task 2 Dining Philosopher (Semaphores)=========.\n\n");
        prompt();
        Thread **threads = new Thread *[num_phi];
        sticks = new Semaphore *[num_phi];
        sticks[num_phi] = new Semaphore("Semaphore", 1);
        for (int i = 0; i < num_phi; i++)
        {
            sticks[i] = new Semaphore("Semaphore", 1);
        }
        for (int i = 0; i < num_phi; i++)
        {

            Thread *t = new Thread("Philo");
            t->Fork(sem_dinner, i);
        }
    }
    // TASK 3
    else if (which_func == 5)
    {
        num_ppl = prompt3(num_ppl, 0);
        num_slt = prompt3(num_slt, 1);
        num_msg = prompt3(num_msg, 2);
        for (int i = 0; i < num_ppl; i++)
        {
            mailbox[i] = new char *[num_slt];
            PostOffice[i] = new Semaphore("B", 1);
            for (int j = 0; j < num_slt; j++)
            {
                mailbox[i][j] = new char[6];
                mailbox[i][j] = "0";
            }
        }

        printf("num_ppl: %d, num_slt: %d, num_msg: %d\n", num_ppl, num_slt, num_msg);
        for (int i = 0; i < num_ppl; i++)
        {

            printf("Forking T%d\n", i);
            Thread *t = new Thread("T");
            t->Fork(mail_func, i);
        }
    }
    // TASK 4
    else if (which_func == 6)
    {
        nR = prompt5(nR, 0);
        nW = prompt5(nW, 1);
        N = prompt5(N, 2);
        printf("Readers: %d, Writers: %d, Max Readers: %d\n", nR, nW, N);
        room_empty = new Semaphore("Room empty", N);
        for (int i = 0; i < nR; i++)
        {
            Thread *t = new Thread("T");
            t->Fork(R, i);
        }
        for (int i = 0; i < nW; i++)
        {
            Thread *t = new Thread("W");
            t->Fork(W, i);
        }
    }
    else if (which_func == 2)
    {
        prompt6();
        prompt6();
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
    else if (which_func==1)
    {

                Thread *t1 = new Thread("Forked Thread T1");
        t1->Fork(get_input, 1);
        
    }
    else
    {
        printf("\n=========Invalid Input=========.\n\n");
    }
}
