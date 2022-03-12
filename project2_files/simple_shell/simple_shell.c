#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>

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
      char *command = NULL;
      size_t command_size = 0;
      size_t chars_read;

      printf(">> ");
      chars_read = getline(&command, &command_size, stdin);

      char *token = strtok(command, " ");

      if (strcmp(token, "exit\n") == 0){
	free(command);
	command = NULL;
	
	printf("Exiting shell...\n");
	exit(0);
      }
      
      if (strcmp(token, "exit") == 0){
	token = strtok(NULL, " ");
		
	if (isdigit(token[0]) != 0){
	  int code = atoi(token);
	  printf("Exiting shell with exit code %u...\n", code);
	  
	  free(command);
	  command = NULL;
	  
	  exit(code);
	}	
      }
      
      char * command_arr[chars_read][chars_read + 1];
      
      int count = 0;
      while (token != NULL){
        strcpy(command_arr[count], token);
        count++;
        token = strtok(NULL, " ");
      }
      
      for (int i = 0; i < count; i++){
        printf("The command word is: %s\n", command_arr[i]);
      }
      
      
      /*if (strcmp(token, "ls\n") == 0){
        if (fork() == 0){
        
          printf("ls command called\n");
          char *binaryPath = "/bin/ls";
          execl(binaryPath, binaryPath, NULL);
          //make sure to handle if exec fails
        }
        wait(NULL);
      }*/
      
      

      // parse argument, call shell command
      //char command_arr[][]

      free(command);
      command = NULL;
    }
  }

  return 0;
}
