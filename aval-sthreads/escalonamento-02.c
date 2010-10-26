/*
 * Ping-pong among three threads
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sthread.h>

static int ping = 0;
static int counter = 0;
static int t1_complete = 0;
static int t2_complete = 0;
static int t3_complete = 0;

void *thread_1(void *);
void *thread_2(void *);
void *thread_3(void *);

int main(int argc, char **argv)
{
  int count = 100;

  sthread_init();

  if (sthread_create(thread_1, (void*)count, 5) == NULL) {
    printf("sthread_create failed\n");
    exit(1);
  }

  if (sthread_create(thread_2, (void*)count, 5) == NULL) {
    printf("sthread_create failed\n");
    exit(1);
  }

  if (sthread_create(thread_3, (void*)count, 5) == NULL) {
    printf("sthread_create failed\n");
    exit(1);
  }

  printf("created threads\n");

  while(!t1_complete || !t2_complete || !t3_complete);

  printf("PASSED\n");
  return 0;
}


void *thread_1(void *arg)
{
   while(counter<(int)arg) {
       
      if(ping == 0) {
         ping = 1;
         counter++;
         printf("[1] ping %d\n", counter);
      } 
   }
   t1_complete = 1;
   return 0;
}


void *thread_2(void *arg)
{
   while(counter<(int)arg) {
       
      if(ping == 1) {
         ping = 2;
         counter++;
         printf("[2] pong %d\n", counter);
      } 
   }
   t2_complete = 1;
   return 0;
}


void *thread_3(void *arg)
{
   while(counter<(int)arg) {
       
      if(ping == 2) {
         ping = 0;
         counter++;
         printf("[3] pung %d\n", counter);
      } 
   }
   t3_complete = 1;
   return 0;
}


