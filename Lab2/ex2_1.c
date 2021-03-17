#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#define NUMBER_OF_THREADS 2

pthread_t tid[NUMBER_OF_THREADS];

//function for the thread to execute
void* doSomeThing(void* arg) {
    int threadId = 0;

    //find your own thread id
    for (int i = 0; i < sizeof(tid); ++i)
    {
      if (tid[i]==pthread_self()){
        threadId = i+1;
      }
    }

    printf("Tread id: %d, PID : %d\n", threadId,getpid());
    return NULL;
}

//Main function that starts the threads
int main(void) {
  int i = 0, err;
  int j = 0;
  
  //get the address of the thread function
  void* (*doSomething_ptr)() = &doSomeThing;
  //Starting threads:
  while(i < NUMBER_OF_THREADS) {
    err = pthread_create(&(tid[i]), NULL, doSomething_ptr, NULL);
    
    if (err != 0) {
      printf("\ncan't create thread :[%s]", strerror(err));
    }
    i++;
  }

  //Wait till all threads are done
  while (j<NUMBER_OF_THREADS){
    pthread_join(tid[j], NULL);
    j++;
  }
  return 0;
}