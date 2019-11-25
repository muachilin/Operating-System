#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>

void* thread_func(void* nu){
  //printf("into the thread %d\n",*((int*) nu));
  int* num = ((int *) nu);
  int i;
  //printf("%d\n",*num);
  for(i=0;i<3;i++){
    clock_t start;
    clock_t end;
    printf("thread %d is running\n",*num+1);
    start = clock();
    end = clock();
    while( (double) ((end-start)/CLOCKS_PER_SEC) < 0.5){
      end = clock();
    }
  }
}

int main(int argc, char** argv){
  //set cpu affinity
  int current_cpu = sched_getcpu();
  cpu_set_t mask;
  CPU_ZERO(&mask);
  if (CPU_SET(current_cpu,&mask) < 0){
    fprintf(stderr,"can not set cpu affinity\n");
    exit(0);
  }
  //invoke FIFO scheduler if specified in the input
  struct sched_param param;
  //memset(&param,0,sizeof(param));
  if (argc == 2){
    if (strcmp(argv[1],"SCHED_FIFO") == 0){
      int pri = sched_get_priority_max(SCHED_FIFO);
      param.sched_priority = pri;
      if (sched_setscheduler(0,SCHED_FIFO,&param) != 0){
        fprintf(stderr,"cannot set scheduler %s\n",strerror(errno));
        exit(0);
      }
    }
    else{
      fprintf(stderr,"unknown scheduler\n");
      exit(0);
    }
  }
  if (argc > 2){
    fprintf(stderr,"too many inputs\n");
    exit(0);
  }
  //create two processes to see if correct
  pthread_t tid[2];
  int arg[2];
  int i;
  for(i=0;i<2;i++){
    arg[i] = i;
    if (pthread_create(&tid[i],NULL,thread_func, (void*) (&arg[i])) != 0){
      fprintf(stderr,"cannot create thread\n");
      exit(0);
    }
    printf("Thread %d is created\n",i+1);
  }
  for(i=0;i<2;i++){
    pthread_join(tid[i],NULL);
  }
  return 0;
}
