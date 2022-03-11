#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

  if (argc > 1){
    fprintf(stderr, "[ERROR] \nThis shell does not accept any command line arguments! \nArgument(s): ");
    for (int i = 1; i < argc; i++){
      fprintf(stderr, "%s ", argv[i]);
    }
    fprintf(stderr, "\n");
    
    exit(1);
  }

  else{
    printf("This is a simple shell made by James Harris!\n");

    while(1){
      char *command;
      size_t command_size = 0;
      size_t chars_read;

      printf(">> ");
      chars_read = getline(&command, &command_size, stdin);      
    }
  }

  return 0;
}
