#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include "utils.h"

int main(int argc, char *argv[]){

  // prints error message if command-line arguments are given
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

    // repeats until exiting
    while(1){
      char *command = NULL;
      size_t command_size = 32;
      size_t chars_read;
      command = (char *)malloc (command_size * sizeof(char));

      // asks for and reads input
      printf(">> ");
      chars_read = getline(&command, &command_size, stdin);

      // token points to the first "word" of the command, i.e. the part of the string before the first space
      char *token = strtok(command, " ");

      // if user wishes to exit, exits program and de-allocates memory
      if (strcmp(token, "exit\n") == 0){
	free(command);
	command = NULL;	
	printf("Exiting shell...\n");
	exit(0);
      }
      
      // if user exits with a specific code, parses for that code and exits if it is an integer
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

      // reads proc file is user enters proc      
      else if (strcmp(token, "proc") == 0){
      
        // token stores the file name, file_name stores the path
        token = strtok(NULL, " ");
        char file_name[chars_read];
        strcpy(file_name, "/proc/");
        strcat(file_name, token);

        // removes newline from end of command
        int null_index = strcspn(file_name, "\n");
        file_name[null_index] = 0;
        
        FILE *file = fopen(file_name, "r");

        // opens file and prints it character-by-character
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

        // frees allocated memory
        free(command);
        command = NULL;
      }

      // if neither exit nor proc are entered      
      else {
      
        // command_arr stores the "words" in the command
        char command_arr[chars_read][chars_read + 2];
      
        // populates command_arr
        int count = 0;
        while (token != NULL){
          strcpy(command_arr[count], token);
          count++;
          token = strtok(NULL, " ");
        }

        // removes newline from end of command      
        int null_index = strcspn(command_arr[count - 1], "\n");
        command_arr[count - 1][null_index] = 0;

        // puts command arguments into arg_arr for parsing to exec(), also uses unescape to handle escape sequences
        const char *arg_arr[count + 1];
        for (int i = 0; i < count; i++){
          char *unescaped = unescape(command_arr[i], stderr);
          arg_arr[i] = unescaped;
        }
        arg_arr[count] = NULL;

        // creates child process and tries to run user command
      	int error = 0;
        if (fork() == 0){
        
          // allocates binary_path and fills with 0s
          char binary_path[chars_read + 5];
          for (int i = 0; i < chars_read + 5; i++){
            binary_path[i] = 0;
          }          
          
          // puts /bin/ at start of path if not already there
          if (strncmp("/bin/", command_arr[0], 5) != 0){
            strcpy(binary_path, "/bin/");
          }
          strcat(binary_path, command_arr[0]);
          
          // tries to execute command
          error = execv(binary_path, arg_arr);
          
          // if program did not execute, exits child process
          if (error == -1){
            free(command);
            for (int i = 0; i < count + 1; i++){
              free(arg_arr[i]);
            }
            exit(0);         
          }
        }
        
        // waits for child process to execute
        wait(NULL);
 
        // frees elements of arg_arr and command
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
