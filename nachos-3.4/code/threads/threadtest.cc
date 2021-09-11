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
#include "get_input.h"

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
}
