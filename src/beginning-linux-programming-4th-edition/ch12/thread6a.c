#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

#ifndef _POSIX_THREAD_PRIORITY_SCHEDULING
#error "Sorry, your system does not support thread priority scheduling"
#endif

void *thread_function(void *arg);

char message[] = "Hello World";
int thread_finished = 0;

int main() {
  
  int res;
  pthread_t a_thread;
  void *thread_result;
  int max_priority, min_priority;
  struct sched_param scheduling_value;

  pthread_attr_t thread_attr;

  res = pthread_attr_init(&thread_attr);
  if (res != 0) {
    perror("Attribute creation failed");
    exit(EXIT_FAILURE);
  }

  res = pthread_attr_setdetachstate(&thread_attr, PTHREAD_CREATE_DETACHED);
  if (res != 0) {
    perror("Setting detached attribute failed");
    exit(EXIT_FAILURE);
  }

  res = pthread_attr_setschedpolicy(&thread_attr, SCHED_OTHER);
  if (res != 0) {
    perror("Setting schedpolicy failed");
    exit(EXIT_FAILURE);
  }

  max_priority = sched_get_priority_max(SCHED_OTHER);
  min_priority = sched_get_priority_min(SCHED_OTHER);
  scheduling_value.sched_priority = min_priority;
  res = pthread_attr_setschedparam(&thread_attr, &scheduling_value);
  if (res != 0) {
    perror("Setting schedpolicy failed");
    exit(EXIT_FAILURE);
  }
  printf("Scheduling priority set to %d, max allowed was %d\n", min_priority, max_priority);
  
  res = pthread_create(&a_thread, &thread_attr, thread_function, (void *)message);
  if (res != 0) {
    perror("Thread creation failed");
    exit(EXIT_FAILURE);
  }

  (void)pthread_attr_destroy(&thread_attr);
 
  while(!thread_finished) {
    printf("Waiting for thread...\n");
    sleep(1);
  }
  printf("Thread finished, bye!\n");
  
  exit(EXIT_SUCCESS);
}

void *thread_function(void *arg) {
  
  printf("thread_function is running. Argument was %s\n", (char *)arg);
  sleep(4);
  
  thread_finished = 1;
  pthread_exit(NULL);
}




