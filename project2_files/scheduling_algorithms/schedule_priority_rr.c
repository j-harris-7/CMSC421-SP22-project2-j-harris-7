#include <stdio.h>
#include <stdlib.h>

#include "schedulers.h"
#include "cpu.h"
#include "list.h"
#include "task.h"

struct node *temp = NULL;
struct node **head = &temp;
int length = 0;

int priorityLeft(int priority);

// add a task to the list 
void add(char *name, int priority, int burst){

  struct task *ptr = malloc(sizeof(struct task));
  
  ptr->name = name;
  ptr->priority = priority;
  ptr->burst = burst;

  insert(head, ptr);
  length++;
}

// invoke the scheduler
void schedule(){
  
  printf("This program iterates from highest to lowest priority (10->1) and uses round-robin scheduling to execute all tasks on said priority.\n");
  
  struct node * curr = *head;
  
  for (int i = 10; i > 0; i--){
   printf("Moves to the next priority.\n");
    while (priorityLeft(i) == 1){
      printf("Since there are still tasks with this priority, we stay with this priority.\n");
      if (curr == NULL){
        printf("Since we have reached the end of the list, we go back to the start.\n");
        curr = *head;
      }
    
      struct task * curr_task = curr->task;
      int curr_prior = curr_task->priority;
      
      if (curr_prior == i){
        printf("The priority of this task matches the iterated priority, so we run this task.\n");
        
        int curr_burst = curr_task->burst;
        
        if (curr_burst <= 10){
          printf("Runs current task until its burst is gone, deletes task.\n");
          run(curr_task, curr_burst);
          delete(head, curr_task);
        } else{
          printf("Runs current task for 10 time units.\n");
          run(curr_task, 10);
          curr_task->burst -= 10;
        }
        
      }
      
      printf("We move to the next task.\n");
      curr = curr->next;
    }
  }
  
  printf("Now that we have iterated through all of the priorities, we end the algorithm.\n");
}

int priorityLeft(int priority){
  
  int bool = 0;
  
  struct node * curr = *head;
  
  while (curr != NULL){
    int curr_prior = curr->task->priority;
    if (curr_prior == priority){
      bool = 1;
    }
    
    curr = curr->next;
  }
  
  return bool;
}
