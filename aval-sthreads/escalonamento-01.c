/* 
 * escalonamneto-01.c
 *
 * Simple test of thread create
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#include <sthread.h>


void *thread_start(void *);


int main(int argc, char **argv)
{
  int i;

  printf("Testing sthread_create, impl: %s\n",
	 (sthread_get_impl() == STHREAD_PTHREAD_IMPL) ? "pthread" : "user");
	
  sthread_init();
    
  if (sthread_create(thread_start, (void*)1, 1) == NULL) {
    printf("sthread_create failed\n");
    exit(-1);
  }
    
  for(i=0;i<300000000;i++);
  return 0;
}


void *thread_start(void *arg)
{
  if ((int)arg == 1)
    printf("Sucesso!\n");
  return 0;
}
