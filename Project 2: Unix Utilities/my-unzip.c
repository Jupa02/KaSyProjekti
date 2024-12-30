#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Function prototype to decompress a single file using run-length encoding (RLE)
void unzipFile(FILE *inputFile);

int main(int argc, char *argv[]) {

  if (argc < 2) {
    printf("my-unzip: file1 [file2 ...]\n");
    exit(1);
  }

  // Go through all provided files
  for (int i = 1; i < argc; i++) {
    FILE *file = fopen(argv[i], "rb");    // Opening th file in binary read mode
    // Error handling when opening file
    if (file == NULL) {                   
      perror("Error opening file");
      exit(1);
    }
    // Decompress the current file
    unzipFile(file);

    // Closing the file
    fclose(file);
  }

  return 0; // Exit succesfully
}

// Function to decompress a single file using run-length encoding
void unzipFile(FILE *inputFile) {
  while (1) {
    uint32_t count;      // Variable to store run lenght count help from https://docs.oracle.com/cd/E19253-01/817-6223/chp-typeopexpr-2/index.html
    char currentChar;    // Variable to store the character

    // Read the run-length count and the character, how fread works from https://www.tutorialspoint.com/c_standard_library/c_function_fread.htm 
    size_t readCount = fread(&count, sizeof(uint32_t), 1, inputFile);
    size_t readChar = fread(&currentChar, sizeof(char), 1, inputFile);

    // Stopping the process if the end of the file is reached
    if (readCount == 0 || readChar == 0) {
      break;
    }

    // Printing the character count times to output
    for (uint32_t i = 0; i < count; i++) {
      printf("%c",currentChar);
    }
  }
}
