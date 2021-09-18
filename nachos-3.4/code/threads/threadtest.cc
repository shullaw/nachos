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
#include "synch.h"

//----------------------------------------------------------------------
// SimpleThread
// 	Loop 5 times, yielding the CPU to another ready thread 
//	each iteration.
//
//	"which" is simply a number identifying the thread, for debugging
//	purposes.
//----------------------------------------------------------------------

typedef struct tInfo {
    int id;
    int nl;
};

const int numThreads = 5;
int num = 0;
int numLoops;
 // when interrupt is off, there will be no random yeilding of threads
Semaphore *numSem =  new Semaphore("Num Sem", 1);  // int arg is number of things you want to guard access to at a time

int nums[numThreads]; // DinePhil --> sem array
Semaphore **numSems = new Semaphore*[numThreads];  // dynamic array of pointers to guard one item per semaphore

void SimpleThread(int param) {

    tInfo* ti = (tInfo*)param;
    for (int i = 0; i < ti->nl; i++) {  // each thread loops a number of times
        
        numSem->P();    // decrement the numSem semaphore (synch.cc); P = "to test"
                        // preceding threads will yield if numSem->P() sees that value==0 (another thread was interrupted
                        // during an operation
                        // or value==1, proceed
        // numSems[0]->P();
        int x = num; 
        x++;

        int rand = Random() % 5;  // randomly yield threads, 
        if (rand == 0) currentThread->Yield();

        num = x;
        numSem->V();  // interrupted threads will be notified that value==1, so they can proceed; V = "to increment"

        printf("Thread %d, looped %d times, num is %d\n", ti->id, i, num);
        currentThread->Yield();

    }
}
void ThreadTest()
{
    DEBUG('t', "Entering ThreadTest");
    Thread **threads = new Thread*[numThreads];
    for (int i = 0; i < numThreads; i++)
    {   
        numSems[i] = new Semaphore("S", i);
        threads[i] = new Thread("T");
        tInfo *ti = new tInfo();

        ti->id = i; ti->nl = numLoops;

        threads[i]->Fork(SimpleThread, (int) ti);
    }

    // Thread ** threads = new Thread*[numThreads];
    // for (int i = 0; i < numThreads; i++) {
    //     threads[i] = new Thread("T");

    //     tInfo *ti = new tInfo();
    //     ti -> id = i; ti->nl = numLoops;

    //     threads[i]->Fork(SimpleThread, (int) ti);
    // }

}