#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

  if (argc > 1){
    fprintf(stderr, "[ERROR] \nThis shell does not accept any command line arguments! \nArgument: %s \n", argv[1]);

    exit(1);
  }

  else{
    printf("This is a simple shell made by James Harris!\n");
  }

  return 0;
}
