/*
------------5-----------------
--------1-------2-------------
----8-------0-------6---------
--------4-------3-------------
------------7-----------------
*/

/*  Star Formation Program   */

#include <iostream>
#include <sched.h>
#include <time.h>
#include <pthread.h>
#include "sem.h"

#define THREAD_COUNT 9

using namespace std;

extern sim_semaphore create_sim_sem(int) ;
extern void wait_sem (sim_semaphore) ;
extern void signal_sem (sim_semaphore) ;

      /* For technical reasons, we use the pthread mutex below,
         instead of a semaphore, to lock the screen for output.  Don't
         change this.  */

pthread_mutex_t stdoutLock ;

     /* Here declare whatever shared variables you need for 
        synchronization. Variables declared here will be visible 
        to (shared by) all the threads in the task. */
   /* HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH */ 
	sim_semaphore flag[9];
	

   /* HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH */ 

     /* These are global variable to represent threads created
        dynamically. */
pthread_t thr[THREAD_COUNT] ; 

    /* This is included to facilitate adding random delays in the code
       -- as a debugging aid. */
extern long random(void);  

   /* This can be changed to 1, but the resulting diagnostic output
      will probably seem excessive. */
int checking = 0 ;

     /* A data type - a struct (class) with an int field to represent
        a thread ID. */
struct threadIdType
{
  int id ;
};

/* ################################################## */
/*                         init                       */
/* ################################################## */
void init() 
{ 
      /* This code initializes special mutex lock for screen output.
         Just leave this alone. */
  if ( 0!=pthread_mutex_init(&stdoutLock, NULL) )
  {  cout << "MUTEX INITIALIZATION FAILURE!" << endl ;
     exit(-1) ;}

    /* Here insert the code that you want to intialize 
       the shared variables that you are using 
       for synchronization. */
   /* HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH */

for (int i=0; i<10;i++)
{
	flag[i]= create_sim_sem(0);
}


   /* HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH */

       /* This initializes a random number generator */ 
  srandom(time((time_t *) 0));
}

/* ################################################## */
/*                     rand_delay                     */
/* ################################################## */
/*void rand_delay(int max) 
{
  int m_delay, j ;
  m_delay = (int) random()%max ;
  for (j=0; j<m_delay; j++) sched_yield();  
}
*/
/* ################################################## */
/*                childMessage                        */
/* ################################################## */
void childMessage (int ID)
{
   pthread_mutex_lock(&stdoutLock) ;
   cout << "Child # " << ID 
        << " is now in position.\n" ;
   pthread_mutex_unlock(&stdoutLock) ;
}

/* ################################################## */
/*                        child                       */
/* ################################################## */

void * child(void * idPtr) 
{
       /* This is just a change of data type for convenience.  Now
          'me' is the number of the child.  Children have numbers from
          0 to 8. */
   int me = ((threadIdType *) (idPtr))->id, temp ;

       /* Delay code inserted here to magnify the chances that child
          threads will delay each other.  The student
          completing the program should think of more ways to insert
          random delays that are likely to 'stress test' the program. */

  // rand_delay(100) ;

       /* Here put whatever synchronization code is required prior
          to the code where the child process declares that it has
          put itself into position. */

   /* HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH */

wait_sem(flag[me]);

switch (me)
{
	case 0:
	
	signal_sem
	
}

   /* HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH */

   childMessage(me) ;  // The child declares that it is in position
  
       /* Here put whatever synchronization code is required AFTER
          the code where the child process declares that it has
          put itself into position. */

   /* HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH */ 

put the numbers in the right area 

   /* HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH */ 

   pthread_exit ((void *)0) ;
}

/* ################################################## */
/*                       mother                       */
/* ################################################## */

/* The mother spawns child threads and then waits for
   them all to finish.  The mother's waiting has to be
   implemented as part of the overall protocol - using
   the sim_semaphore data type. */

void mother() 
{ 
   int i; 

       /* This is a pointer to a struct (class) that contains an int
          field - it is a convenient data type to use as the parameter
          to the child function.  */
   threadIdType * idPtr ; 

        /* Create child threads numbered 1 through 8. */

   pthread_mutex_lock(&stdoutLock) ;
   cout << "Mother Begins Spawning Threads.\n"   << endl ;
   pthread_mutex_unlock(&stdoutLock) ;

   for (i = 0; i < THREAD_COUNT ; i++) 
   {
      idPtr = new threadIdType ; /* allocate memory for struct */
      idPtr->id = i ;  /* records current index as the child's ID */

         /* The call below is what actually creates the child thread
            and passes a pointer to the struct 'idPtr' as the
            parameter to the child function. */

      if ( 0!=pthread_create(&thr[i], NULL, child, (void *) idPtr) )
      {  pthread_mutex_lock(&stdoutLock) ; /* 'error out' code here */
         cout << "THREAD CREATION FAILURE!" << endl ;
         pthread_mutex_unlock(&stdoutLock) ;
         exit(-1) ; }

         /* The call to pthread_detach() below marks a child 
            thread as 'detached' so that the system will not 
            expect the parent to 'join' (wait for) it. */     

      if (0!=pthread_detach(thr[i]))
      {  pthread_mutex_lock(&stdoutLock) ;/* 'error out' code here */
         cout << "THREAD DETACHMENT FAILURE!" << endl ;
         pthread_mutex_unlock(&stdoutLock) ;
         exit(-1) ;}
   }

   pthread_mutex_lock(&stdoutLock) ;
   cout << "Mother Finishes Spawning Threads.\n"   << endl ;
   pthread_mutex_unlock(&stdoutLock) ;

      /* Some synchronization code is needed here to make the mother 
         behave correctly - she is not supposed to exit until after 
         all the children have finished putting themselves into position. */

      /* HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH */ 

signal semaphore[0];


      /* HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH */ 
      /* 
         REMOVE THE DELAY CODE BELOW AFTER YOU FINISH
         ADDING SYNCHRONIZATION CODE TO THE PROGRAM.

         The delay below is an artificial elment of the program.
         When the program runs un-synched and without the delay 
         below, it's likely that the mother will exit before most
         or all of the child threads get a chance to do anything
         at all.  With the delay below in place, in many runs of
         the un-synched program, some or all of the children will
         have time to write their messages to the screen, which
         will allow the student to see how the un-synched 
         child threads behave.

         Once the student has added sufficient synchronization code,
         the program should execute correctly in every run, WITHOUT
         delay below in the program any more.

         It is important for the student to take it out eventually,
         to make sure that the program can execute correctly without it. */

  // rand_delay(1000) ; /* REMOVE THIS DELAY BEFORE FINAL TESTING */

   pthread_mutex_lock(&stdoutLock) ;
   cout << "\nAll children are now in position.\n" ;
   cout << "Mother exiting ... \n\n" ;
   pthread_mutex_unlock(&stdoutLock) ;
   return ;
}

/* ################################################## */
/*                         main                       */
/* ################################################## */

int main() 
{ 

   cout << "\nWelcome to The Star Chamber!\n\n" ;

     /* This calls the function that performs initializations. */
  init(); 

        /* Execute the mother() function */ 
  mother();

  return 0 ;
}
