#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function protorype to read file and search for a specific word
void readFile(char* searchWord, char* inputFile);

int main(int argc, char *argv[]){

  if (argc < 2){
    printf("my-grep: searchterm [file ...]\n");
    exit(1);
  }
  else if (argc == 2) {           // If only search term is given, reading from stdin
    char *searchWord = argv[1];
    readFile(searchWord, NULL);
  } else {                        // If search term and file are given
    char *searchWord = argv[1];
    // Going through all of the given files
    for (int i = 2; i < argc; i++) {
      char *inputFile = argv[i];
      readFile(searchWord,inputFile);
    }
  }
  return(0); // Exit succesfully

}

// Function to read lines from the file and print the lines that have the specific word
void readFile(char* searchWord,char* inputFile){

  int read;             // Variable for line lenghts
  char *line = NULL;    // Pointer to store each line
  size_t len = 0;       // Storing point for getline line lenght
  FILE *file;           // File pointer for input file
  // Opening the file or using stdin if the file isnt given
  if (inputFile == NULL) {
    file = stdin;
  } else {
    // Opening the file for reading
    if ((file = fopen(inputFile, "r")) == NULL) {
      printf("my-grep: cannot open file\n");
      exit(1);
    }
  }
  // Reading every line from the file
  while ((read = getline(&line, &len, file)) != -1) {
    // Checking if the word is found from the line, help from https://www.w3schools.com/c/ref_string_strstr.php to use strstr
    if (strstr(line, searchWord) != NULL && strlen(searchWord) > 0) {
      // Printing the line if it is found
      printf("%s", line);
      // Printing newline if the line doesnt exist
      if (line[read - 1] != '\n') {
	      printf("\n");
      }
    }
  }

  fclose(file);   // Closing the file after the reading is finished
  return;

}
