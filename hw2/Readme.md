# Scheduler in Linux Kernel

1. Invoke FIFO scheduler
   (1) First obtain the current using CPU by sched getcpu(). Then set the cpu set t mask by CPU ZERO and CPU set.
   
   (2) Check the argument input number, if there is no other argument, use default scheduler (do nothing). If the argument is ”SCHED FIFO”, the use sched setscheduler to set the scheduler to FIFO scheduler.
   
   (3) Use pthread create to produce two threads executing function ”thread func”, 
   and print the message ”Thread # is created”.
   
   (4) The function ”thread func” will print the thread number of itself, and busy waiting for 0.5 seconds. 
   The busy waiting is achieved by using clock.h. 
   One timer is recorded first as start, 
   and use the while loop to check if the time exceed 0.5 second by subtracting 
   by the current time (another clock t object). 
   If exceed 0.5 second, then jump out the while. 
   The function will be busy waiting for 0.5 seconds three times.
   
   (5) After all the thread functions finished, use thread join to end up the thread.  
   
2. Implement weighted round robin scheduling
  (1) Use list add tail() to enqueue task struct* p and decrease rq ->weighted rr.nr running by one.
  
  (2) Use list del() to dequeue task struct* p and increase rq ->weighted rr.nr running by one.
  
  (3) Assign rq->curr->weighted time slice to rq->curr->task time slice 
      and use list move tail() to put the current task struct* (rq->curr) to the end of the run list.
      
  (4) Minus p ->task time slice by one. 
      If the value is zero, Assign rq ->curr ->weighted time slice to rq ->curr ->task time slice 
      and check if curr->weighted_rr_list_item.prev is equal to curr->weighted_rr_list_item.next. 
      If not, call set tsk need resched() and requeue p.
      
  (5) If rq ->weighted rr.nr running is zero, return NULL because there is no task to run.
      Otherwise, use list first entry() to obtain the first task in rq ->weighted rr.queue and return it.
