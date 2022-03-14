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
  printf("This algorithm simply runs each task in the order they're found in the list.\n");

  printf("Starts at head, moves to next.\n");
  struct node *curr = *head;
  while (curr != NULL){
    run(curr->task, curr->task->burst);
    curr = curr->next;
    printf("Runs task, moves to next in list.\n");
  }
  
  printf("With NULL reached, algorithm ends.\n");
}
