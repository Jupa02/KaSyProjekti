#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

// Function prototype to compress file 
void zipFile(char **inputFiles, int numFiles);

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("my-zip file1 [file2 ...]\n");
    exit(1);   
  }
  // Process all input files
  zipFile(&argv[1], argc - 1);

  return 0; // Exit succesfully
}

// Function for 
void zipFile(char **inputFiles, int numFiles) {
  // Allocate a buffer for all file contents combined
  size_t totalSize = 0;
  char *combinedBuffer = NULL;

  // Read the content of all files
  for (int i = 0; i < numFiles; i++) {
    FILE *file = fopen(inputFiles[i], "r"); // Opening the file in reading mode
    // Error handling when opening file
    if (file == NULL) {                 
      perror("Error opening file");
      exit(1);
    }

    /* Moving the file pointer to the end, retrieving the file size in bytes,
      and reseting the pointer to beginning.Help from https://www.tutorialspoint.com/c_standard_library/c_function_fseek.htm */
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    // Reallacating the buffer for the files content
    combinedBuffer = realloc(combinedBuffer, totalSize + fileSize);
    if (combinedBuffer == NULL) {
      perror("Memory allocation failed");
      exit(1);
    }

    // Reading the conted of the file into the buffer
    fread(combinedBuffer + totalSize, 1, fileSize, file);
    totalSize += fileSize;

    fclose(file); // Closing the file
  }

  // Process the combined file content 
  size_t i = 0;  // Index for the buffer
  while (i < totalSize) {
    char currentChar = combinedBuffer[i]; // Getting the current character
    uint32_t count = 1;                   // Intializing the run lenght help from https://docs.oracle.com/cd/E19253-01/817-6223/chp-typeopexpr-2/index.html

    // Counting the occurance of consecutive characters
    while (i + 1 < totalSize && combinedBuffer[i + 1] == currentChar) {
      i++;
      count++;
    }

    // Writing the run lenght into binary format to stdout, how the fwrite works from https://www.tutorialspoint.com/c_standard_library/c_function_fwrite.htm
    fwrite(&count, sizeof(uint32_t), 1, stdout);

    // Writing the character to stdout
    fwrite(&currentChar, sizeof(char), 1, stdout);

    // Moving to the next different character
    i++;
  }
  // Free the meory of the buffer
  free(combinedBuffer);
}
