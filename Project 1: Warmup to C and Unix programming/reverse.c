#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function prototypes
void reverse(char **lines, int lineCount);                // Function to reverse lines
void readFile(char* inputFile);                           // Function to read the file
void readAndSaveToFile(char* inputFile,char* outputFile); // Function to read the file and save the result into different file

int main(int argc, char *argv[]) {
  // Different command line cases
  if (argc == 1) {
    readFile(NULL);

  }else if (argc == 2) {
    char *inputFile = argv[1];
    readFile(inputFile);

  }else if (argc == 3){
    char *inputFile = argv[1];
    char *outputFile = argv[2];

    // Ectracting just the filename help from https://www.tutorialspoint.com/c_standard_library/c_function_strrchr.htm to use strrchr
    char *inputt = strrchr(inputFile, '/');     
    char *outputt = strrchr(outputFile, '/');   
    /* Jos inputt/outputt ei ole NULL, siirretään osoitinta eteenpäin mutta jos
       inputt/outputt on NULL niin asetetaan osoitin viittaamaan inputFile/outputFile */
    inputt = (inputt != NULL) ? inputt + 1 : inputFile;
    outputt = (outputt != NULL) ? outputt + 1 : outputFile;
    // Check if the input and output filese are different or same
    if (strcmp(inputt, outputt) == 0) {
      fprintf(stderr, "reverse: input and output file must differ\n");
      exit(1);
    }
    readAndSaveToFile(inputFile, outputFile);

  }else if (argc > 3) {
    fprintf(stderr, "usage: reverse <input> <output>\n");
    exit(1);
  }
  return(0);
}

// Function to reverse the order of the lines
void reverse(char **lines, int lineCount) {
  // Print the lines in reverse order
  for (int i = lineCount - 1; i >= 0; i--) {
    printf("%s", lines[i]);
    free(lines[i]);  // Free the memory for each line after printing
  }
  free(lines);       // Free the memory for the lines array
  return;
}

// Function to read the file and store lines in an array
void readFile(char* inputFile) {
  FILE *file;  // Open the file for reading
  if (inputFile == NULL) {
    file = stdin;  // Reading from standard input
  } else {
    // Open the file for reading
    if ((file = fopen(inputFile, "r")) == NULL) {
      fprintf(stderr, "error: cannot open file '%s'\n", inputFile);
      exit(1);
    }
  }

  char **lines = NULL;  // Array of pointers to store lines
  char *line = NULL;    // Pointer to store each line
  size_t len = 0;       // Size of the allocated memory for each line
  int read;             // Number of characters read by getline
  int lineCount = 0;    // Counter for the number of lines read

  // Read each line from the file using getline() 
  while ((read = getline(&line, &len, file)) != -1) {
    if (line[read - 1] != '\n') {
      line[read] = '\n';      // Append a newline if not already present
      line[read + 1] = '\0';  // Null-terminate the string
      read++;
    }
    // Resize the array to hold one more line
    lines = realloc(lines, (lineCount + 1) * sizeof(char*));
    if (lines == NULL) {
      fprintf(stderr, "Memory allocation failed.\n");
      free(line);
      fclose(file);
      exit(1);
    }

    // Allocate memory for the new line and copy it into the array
    lines[lineCount] = malloc(read + 1);  // Allocate space for the line
    if (lines[lineCount] != NULL) {
      strcpy(lines[lineCount], line);     // Copy the line to the array
      lineCount++;
    } else {
      fprintf(stderr, "Memory allocation failed.\n");
      free(line);   // Free previously allocated memory
      free(lines);  
      fclose(file);
      exit(1);      // Exit with code 1 if malloc fails
    }
  }

  // Reverse the lines and print them
  reverse(lines, lineCount);

  // Free the memory
  free(line);
  fclose(file);
  return;
}

// Function to read file and save the results into different file
void readAndSaveToFile(char* inputFile,char* outputFile){
  FILE *file;     // Open the input file for reading
  FILE *outFile;  // Open the output file for writing

  char **lines = NULL;  // Array of pointers to store lines
  char *line = NULL;    // Pointer to store each line
  size_t len = 0;       // Size of the allocated memory for each line
  int read;             // Number of characters read by getline
  int lineCount = 0;    // Counter for reading the lines

  if ((file = fopen(inputFile, "r")) == NULL) {
    fprintf(stderr, "error: cannot open file '%s'\n", inputFile);
    exit(1);
  }

  if ((outFile = fopen(outputFile, "w")) == NULL) {
    fprintf(stderr, "error: cannot open file '%s'\n", outputFile);
    fclose(file);
    exit(1);
  }

  // Read each line from the input file using getline()
  while ((read = getline(&line, &len, file)) != -1) {
    if (line[read - 1] != '\n') {
      line[read] = '\n';      // Append a newline if not already present
      line[read + 1] = '\0';  // Null-terminate the string
      read++;
    }
    // Resize the array to hold one more line
    lines = realloc(lines, (lineCount + 1) * sizeof(char*));
    if (lines == NULL) {
      fprintf(stderr, "Memory allocation failed.\n");
      free(line);
      fclose(file);
      fclose(outFile);
      exit(1);
    }

    // Allocate memory for the new line and copy it into the array
    lines[lineCount] = malloc(read + 1);  // Allocate space for the line
    if (lines[lineCount] != NULL) {
      strcpy(lines[lineCount], line);     // Copy the line to the array
      lineCount++;
    } else {
      fprintf(stderr, "Memory allocation failed.\n");
      free(line);   // Free the memory
      free(lines);  
      fclose(file);
      exit(1);      // Exit with code if malloc fails
    }
  }

  // Reverse the lines and write them to the output file
  for (int i = lineCount - 1; i >= 0; i--) {
    fprintf(outFile, "%s", lines[i]);  // Write reversed lines to the output file
    free(lines[i]);                    // Free the memory for each line
  }

  // Free the memory
  free(lines);
  free(line);
  fclose(file);
  fclose(outFile);
  return;
}
