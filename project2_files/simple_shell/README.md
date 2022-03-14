Part 1:

Requirement 1:

I simply used getline() to get the user command, and I used a while(1) loop to ensure it continued asking for commands.

Requirement 2:

I built argc and argv values into main, for which argc represents the number of arguments given on the command line. If argc is greater than one, that means command-line arguments were passed, and I used fprintf to print a message to stderr.

Requirement 3:

getline() allocates more data if not enough was initially allocated, so it handles inputs of arbitrary length.

Requirement 4:

We create an array to store the individual "words" of the command. We use strtok() to get the words and populate the array with the commands. Then, we copy the contents into another array, called arg_arr, and call unescaped() on each word. Then, we fork the process. In the child process, we construct the file name depending on whether the user entered "/bin/" at the start, and we call exec() on said file name. If the process does not execute, we free the memory and close the child process manually.

Requirement 5:

We check to see if the first "word" in the command is exit. If a newline comes right after, we simple free memory and exit. If there is a non-newline afterwards, we inspect and check to see if it is a digit. If it is, we exit with that code. If it is not, we free the command and go back to the start of the loop.

Requirement 6:

Throughout the production of my code, I was constantly using valgrind to test for memory leaks. Every time I saw a leak, I figured out what it was and fixed it. Overall, I wound up freeing "command" a lot, and also had to free the contents of arg_arr. I came into contact with some memory errors, but careful inspection allowed me to get rid of all of those.

Part 2:

In a similar manner to exit, we use strcmp() to compare the first "word" of the command with "proc". If it is equal, we store the file name in a string and open it. Then, we simply use fgetc() to read from the file, and we print the contents out character-by-character.
