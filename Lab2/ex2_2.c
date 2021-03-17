#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h> 
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#define NUMBER_OF_THREADS 4
#define MAX_COUNT 10000

static sem_t obj_produced;
static sem_t obj_consumed;

static sem_t totSem;

static int number,total;
pthread_t tid[NUMBER_OF_THREADS];

void * producer() {
  int i;
  
  for(i=2; i< MAX_COUNT; i++) {
    number = i;
    sem_post(&obj_produced);
    sem_wait(&obj_consumed);
  }

  return NULL;
}


void * consumer() {
  unsigned char isPrime;
  int i;
  int num_to_check;

  while(1) {
    sem_wait(&obj_produced);
    num_to_check = number;
    sem_post(&obj_consumed);
    
    isPrime = 1;
    for (i=2;i<num_to_check; i++) {
      if (num_to_check % i == 0) {
        isPrime = 0;
      }
    }
    if(isPrime  == 1) {
      int threadId = 0;

      //find your own thread id
      for (int id = 0; id < sizeof(tid); id++)
      {
        if (tid[id]==pthread_self()){
          threadId = id+1;
        }
      }
      sem_wait(&totSem);
      total = total + 1;
      sem_post(&totSem);


      printf("    thread %d announces that %d is prime. Total is %d\n", threadId, num_to_check,total);
    }
  }
}


int main() {
  int i = 0, err;

  // create semaphores
  err = sem_init(&obj_produced, 0, 0);
  if(err != 0) {
    printf("\ncan't create semaphore: obj_produced [%s]", strerror(err));
    return 1;
  }
  err = sem_init(&obj_consumed, 0, 0);
  if(err != 0) {
    printf("\ncan't create semaphore: obj_produced [%s]", strerror(err));
    return 1;
  }

  // create producer thread
  err = pthread_create(&(tid[i]), NULL, &producer, NULL);
  if (err != 0) {
    printf("\ncan't create producer thread: [%s]", strerror(err));
    return 1;
  } 
  printf("Producer thread created\n");

  // create consumer threads
  for(i=1;i<NUMBER_OF_THREADS;i++) {
    err = pthread_create(&(tid[i]), NULL, &consumer, NULL);
    if (err != 0) {
      printf("\ncan't create consumer thread %d: [%s]", i, strerror(err));
    }
    printf("Consumer thread %d created\n", i);
  }
  //release totSem
  sem_post(&totSem);

  // wait for producer thread
  pthread_join(tid[0], NULL);

  // kill consumer threads 
  for(i=1;i<NUMBER_OF_THREADS;i++) {
    pthread_kill(tid[i], 9);
  }
  
  // delete the semaphores
  sem_destroy(&obj_produced);
  sem_destroy(&obj_consumed);
  sem_destroy(&totSem);
  return 0;
}