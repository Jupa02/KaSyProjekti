#include <stdio.h>
#include <stdlib.h>

// Function prototype for reading the function
void readFile(char* inputFile);

int main(int argc, char *argv[]){

  // Exit if no arguments are given
  if (argc < 2){
    exit(0);
  }

  // Looping through all provided files
  for (int i = 1; i < argc; i++) {
    char *inputFile = argv[i];    // Getting the current file naem
    readFile(inputFile);          // Calling the function to read and print the file
  }
  return(0); // Exit succesfully
}

// Function to read the file and print its content line by line
void readFile(char* inputFile){
  // fixed size buffer
  char buffer[1024];
  // Opening the file for reading and checking if it openend correctly
  FILE *file;
  if ((file = fopen(inputFile, "r")) == NULL) {
    printf("my-cat: cannot open file\n");      // The error message if it cant be opened
    exit(1);
  }

  // Reading each line and printing the line
  while (fgets(buffer, 1024, file) != NULL) {
    printf("%s", buffer);
  }
  // Closing the file after the reading is finished
  fclose(file);
  return;
}
