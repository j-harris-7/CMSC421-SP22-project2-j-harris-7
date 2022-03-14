#include <stdio.h>
#include <stdlib.h>

#include "schedulers.h"
#include "cpu.h"
#include "list.h"
#include "task.h"

struct node *temp = NULL;
struct node **head = &temp;
int length = 0;

struct task * pickNextTask();

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
  
  printf("This algorithm searches for the highest priority remaining, runs that, and deletes it from the list.\n");
  
  int count = 0;
  while (count < length){
    
    printf("Uses pickNextTask to pick the highest priority and runs that.\n");
    struct task *curr = pickNextTask();
    run(curr, curr->burst);
    count++;
  }
  printf("Now that we have reached the end of the length, the algorithm is done.\n");
}

struct task * pickNextTask(){
  struct node *head_node = *head;
  struct task *highest_task = head_node->task;
  int highest = highest_task->priority;
  
  struct node *curr = *head;
  while (curr != NULL){
    struct task *curr_task = curr->task;
    int curr_prior = curr_task->priority;
    
    if (curr_prior > highest){
      highest = curr_prior;
      highest_task = curr_task;
    }
  
    curr = curr->next;
  }
  
  delete(head, highest_task);
  
  return highest_task;
}
