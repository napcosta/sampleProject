/*
 * test-mutex.c
 *
 * Simple test of mutexes. Checks that they do, in fact, provide 
 * mutual exclusion.
 *
 * Mutexes are implemented as semaphores initialized with 1 unit.
 */


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sthread.h>

static int counter = 0;
static int ran_thread = 0;
static sthread_mutex_t mutex;


void *thread_start(void *);


int main(int argc, char **argv)
{
	int checks;
	
	printf("Testing sthread_mutex_*, impl: %s\n",
		   (sthread_get_impl() == STHREAD_PTHREAD_IMPL) ? "pthread" : "user");
	
	sthread_init();
	
	mutex = sthread_mutex_init();
	sthread_mutex_lock(mutex);
	
	if (sthread_create(thread_start, (void*)1) == NULL) {
		printf("sthread_create failed\n");
		exit(1);
	}
	
	/* Wait until the other thread has at least started,
	 * to give it a chance at getting through the mutex incorrectly. */
	while (ran_thread == 0) {
		sthread_yield();
	}
	
	/* The other thread has run, but shouldn't have been
	 * able to affect counter (note that this is not a great test
	 * for preemptive scheduler, since the other thread's sequence
	 * is not atomic). */   
	assert(counter == 0);
	
	/* This should let the other thread run at some point. */
	sthread_mutex_unlock(mutex);
	
	/* Allow up to 100 checks in case the scheduler doesn't
	 * decide to run the other thread for a really long time. */
	checks = 100;
	while (checks > 0) {
		sthread_mutex_lock(mutex);
		if (counter != 0) {
			/* The other thread ran, got the lock,
			 * and incrmented the counter: test passes. */
			checks = -1;
		} else {
			checks--;
		}
		sthread_mutex_unlock(mutex);
		
		/* Nudge the scheduler to run the other thread: */
		sthread_yield();
	}
	
	if (checks == -1) {
		printf("sthread_mutex passed\n");
	} else {
		printf("*** sthread_mutex failed\n");
	}
	sthread_mutex_free(mutex);
	return 0;
}


/* Try and get the lock.
 * When acquired, mark a global to let main know. */
void *thread_start(void *arg)
{
	/* indicate we got in to this thread */
	ran_thread = 1;
	/* should wait until main() has released us */
	sthread_mutex_lock(mutex);
	counter++;
	sthread_mutex_unlock(mutex);
	return 0;
}
