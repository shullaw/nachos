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
#include "synch.h"

extern bool prog_select;  // ALL TASKS
extern int numLoops;  
extern int which_func;  // ALL TASKS
// PROJECT 1
extern int thread_count;
extern int shouts_count;
extern char input[6];  // ALL TASKS
extern bool stick[10001];  /* TASK 2  For Assignment 2, you must handle 10k threads 
							for full credit. That is Philosophers or Mailbox Readers. */
extern int num_phi;  // TASKS 1 AND 2
extern int room_count;  // TASKS 1 AND 2
extern int total_eaten;  // TASKS 1 AND 2
extern int meal_goal;  // TASKS 1 AND 2
extern int total_sit;  // TASKS 1 AND 2
//-----------------------------TASK 3----------------------------------//
extern int num_ppl;
extern int num_slt;
extern int num_msg;
extern char ***mailbox;
extern int msg_goal;
extern int msg_total;
extern int left;
extern int idx;
//----------------------------TASK 3----------------------------------//
//----------------------------TASK 4----------------------------------//
extern int nR;
extern int nW;
extern int N;
extern int writer_count;
extern bool Wait;
//----------------------------TASK 4----------------------------------//

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




// extern struct Mbox
// {
// 	int id;
// 	Semaphore **mailbox;
// 	char *slots;
// };



#define MAXIMUM 6  // PROJECT 2
#define SPACE 32
#define COMMA 44
#define DASH 45
#define DOT 46
#define FSLASH 47
#define ZERO 48
#define NINE 57
#define SEMICOLON 58
#define TILDA 126

extern bool prog_select;

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
