#include <stdio.h>
#include <stdlib.h>

#include "schedulers.h"
#include "cpu.h"
#include "list.h"
#include "task.h"

struct node *temp = NULL;
struct node **head = &temp;
int length = 0;

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
  
  printf("This algorithm loops through all of the nodes, bursting them for 10 seconds until they have been completed.\n");
  
  struct node *curr = *head;
  while (*head != NULL){
    if (curr == NULL){
      printf("We have reached the end of the list, so we go back to the beginning.\n");
      curr = *head;
    }
  
    struct task * curr_task = curr->task;
    int curr_burst = curr_task->burst;
    
    printf("Checking to see if the current task has 10 or fewer time units left.\n");
    if (curr_burst <= 10){
      printf("Runs current task until its burst is gone, deletes task.\n");
      run(curr_task, curr_burst);
      delete(head, curr_task);
    } else {
      printf("Runs current task for 10 time units.\n");
      run(curr_task, 10);
      curr->task->burst -= 10;
    }
  
    printf("Moving to the next task.\n");
    curr = curr->next;
  }
  
  printf("All tasks are deleted, so the algorithm is done.\n");
}
