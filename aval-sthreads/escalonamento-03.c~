/*
 * Threads with different priorities
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sthread.h>

static int counter1 = 0;
static int counter2 = 0;

void *thread_1(void *);
void *thread_2(void *);
void *thread_3(void *);

int main(int argc, char **argv)
{
  int counter0 = 0;
  int c1, c2;


  sthread_init();

  if (sthread_create(thread_1, (void*)0, 10) == NULL) {
    printf("sthread_create failed\n");
    exit(1);
  }

  if (sthread_create(thread_2, (void*)0, 1) == NULL) {
    printf("sthread_create failed\n");
    exit(1);
  }

  printf("created threads\n");

  for(; counter0 < 30000000; counter0++);

  c1 = counter1;
  c2 = counter2;
  printf("1: %i, 2: %i\n", c1, c2);
  printf("2/1: %f\n", ((float)c2)/c1);

  if (c2/c1 >= 6 && c2/c1 <= 14)
    printf("PASSED\n");

  return 0;
}


void *thread_1(void *arg)
{
  for (;;counter1++);
  return 0;
}


void *thread_2(void *arg)
{
  for (;;counter2++);
  return 0;
}


