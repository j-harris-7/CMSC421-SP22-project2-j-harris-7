#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include "utils.h"

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
      
      else if (strcmp(token, "exit") == 0){
	token = strtok(NULL, " ");
		
	if (isdigit(token[0]) != 0){
	  int code = atoi(token);
	  printf("Exiting shell with exit code %u...\n", code);
	  
	  free(command);
	  command = NULL;
	  
	  exit(code);
	}
	free(command);
	command = NULL;	
      }
      
      if (strcmp(token, "proc") == 0){
        token = strtok(NULL, " ");
        char file_name[chars_read];
        strcpy(file_name, "/proc/");
        strcat(file_name, token);
        
        int null_index = strcspn(file_name, "\n");
        file_name[null_index] = 0;
        
        FILE *file = fopen(file_name, "r");
        
        if (file == NULL){
          printf("File does not exist!\n");
        } else{
          char c = fgetc(file);
          while (c != EOF){
            printf("%c", c);
            c = fgetc(file);
          }
          printf("\n");
          
          fclose(file);
        }
        
        free(command);
        command = NULL;
      }
      
      else {
        char command_arr[chars_read][chars_read + 1];
      
        int count = 0;
        while (token != NULL){
          strcpy(command_arr[count], token);
          count++;
          token = strtok(NULL, " ");
        }
      
        int null_index = strcspn(command_arr[count - 1], "\n");
        command_arr[count - 1][null_index] = 0;

        const char *arg_arr[count + 1];
        for (int i = 0; i < count; i++){
          char *unescaped = unescape(command_arr[i], stderr);
          arg_arr[i] = unescaped;
        }
        arg_arr[count] = NULL;

      	int error = 0;
        if (fork() == 0){
          char binary_path[] = "";
          if (strncmp("/bin/", command_arr[0], 5) != 0){
            strcpy(binary_path, "/bin/");
          }
          strcat(binary_path, command_arr[0]);
          error = execv(binary_path, arg_arr);
        }
        wait(NULL);
        
        if (error == -1){
          exit(0);
        }
        
        for (int i = 0; i < count + 1; i++){
          free(arg_arr[i]);
        }
        free(command);
        command = NULL;
      }
    }
  }

  return 0;
}
