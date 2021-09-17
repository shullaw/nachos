// system.h
//	All global variables used in Nachos are defined here.
//
// Copyright (c) 1992-1993,2021 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation
// of liability and disclaimer of warranty provisions.

#ifndef SYSTEM_H
#define SYSTEM_H

#include "copyright.h"
#include "utility.h"
#include "thread.h"
#include "scheduler.h"
#include "interrupt.h"
#include "stats.h"
#include "timer.h"

// #ifdef THREADS
// extern bool prog_select;
// #endif

// Initialization and cleanup routines
extern void Initialize(int argc, char **argv); // Initialization,
											   // called before anything else
extern void Cleanup();						   // Cleanup, called when
											   // Nachos is done.

extern Thread *currentThread;		// the thread holding the CPU
extern Thread *threadToBeDestroyed; // the thread that just finished
extern Scheduler *scheduler;		// the ready list
extern Interrupt *interrupt;		// interrupt status
extern Statistics *stats;			// performance metrics
extern Timer *timer;				// the hardware alarm clock

// HOMEWORK 1
extern int which_func;
// PROJECT 1
extern bool prog_select;
extern int thread_count;
extern int shouts_count;

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

class Project1
{
public:
	char *storage;
	int idx;
	char *n1;
	char *n2;
	// int thread_count;
	// int shout_count;

	Project1() : storage(new char[MAXIMUM + 1]()){};

	void free_mem()
	{
		delete[] storage;
	}
	~Project1()
	{
	}

	double check_input(int num)
	{
		int c;
		int idx = num;
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

		printf("\n-----------------------TASK 2----------------------------------------");
		printf("\nPlease enter fewer than %d characters with your keyboard followed by the \"Enter\" key.\nPress \"Ctrl\" + \"c\" to exit the program.\n", MAXIMUM + 1);
		printf("If an odd character is shown (ex. press an arrow key) delete it with backspace or the program will exit upon execution.\n");
		printf("At the end of the program, the array created to hold input will be deleted.\n");
		printf("Enter a positive integer Thread Count and press \"Enter\"\n");
		while ((position++ <= MAXIMUM) && (c = getchar()) != '\n' && c != EOF)
		{
			if (position == MAXIMUM)
			{
				break;
			}
			if (c >= ZERO && c <= NINE) // if digit between 0-9
			{							// checks for digit
				storage[position] = c;
				ndigit++;
				total++;
			}
			else if (c == DASH && position == 0 && ndash == 0) // if - in first position; possible negative
			{
				storage[position] = c;
				ndash++;
				total++;
			}
			else if (c == DASH && position != 0) // if - in first position; possible negative
			{
				storage[position] = c;
				nchar++;
				total++;
			}
			else if (c == DOT && position != 0 && ndot == 0) // if . (decimal)
			{
				storage[position] = c;
				ndot++;
				total++;
			}
			else if (c == DOT && position == 0) // if . (decimal)
			{
				storage[position] = c;
				nchar++;
				total++;
			}
			else if (c >= SPACE && c <= FSLASH || c >= SEMICOLON && c <= TILDA && c != DOT && c != DASH) // checks for "normal" ascii characters
			{
				storage[position] = c;
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
			storage[position] = '\0';
			final = storage[--position];					 // last position in array
			if (final == DOT && storage[++position] == '\0') // if . (decimal)
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
				if (storage[0] == DASH)
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
					if (storage[0] == DASH && nchar == 0 && ndigit >= 1 && storage[1] >= ZERO && storage[1] <= NINE)
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
					else if (storage[0] != DOT && nchar == 0 && storage[1] >= ZERO && storage[1] <= NINE && final != DOT)
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
						printf("%d=%c ", storage[i], storage[i]);
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
		if (storage && number && !negative)
		{
			if (idx == 1) {
				thread_count = atoi(storage);
				printf("tc: %i\n", thread_count);
				return thread_count;
			}
			else if (idx == 2) {
				shouts_count = atoi(storage);
				printf("tc: %i\n", shouts_count);
				return shouts_count;
			}
		}
		else
		{
			return 0;
		}
	}
};

#ifdef USER_PROGRAM
#include "machine.h"
extern Machine *machine; // user program memory and registers
#endif

#ifdef FILESYS_NEEDED // FILESYS or FILESYS_STUB
#include "filesys.h"
extern FileSystem *fileSystem;
#endif

#ifdef FILESYS
#include "synchdisk.h"
extern SynchDisk *synchDisk;
#endif

#ifdef NETWORK
#include "post.h"
extern PostOffice *postOffice;
#endif

#endif // SYSTEM_H
