#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <errno.h>

int read_file_to_lines(char ***lines, char *file_path)
{
  int MAX_LINE_LENGTH = 256;
  FILE *file = fopen(file_path, "r");
  int lineCount = 0;

  char buffer[MAX_LINE_LENGTH];
  while (fgets(buffer, MAX_LINE_LENGTH, file) != NULL)
  {
    *lines = realloc(*lines, (lineCount + 1) * sizeof(char *));
    (*lines)[lineCount] = malloc(strlen(buffer) + 1);

    strcpy((*lines)[lineCount], buffer);
    lineCount++;
  }
  fclose(file);
  return lineCount;
}

char *read_entire_file(char *file_path) {
  // Reads an entire file into a char array, and returns a ptr to this. The ptr should be freed by the caller
  FILE *f = fopen(file_path, "r");
  if (f==NULL) {
    fprintf(stderr, "Could not read %s: %s\n", file_path, strerror(errno));
    exit(1);
  }

  fseek(f, 0L, SEEK_END);
  int sz = ftell(f);
  fseek(f, 0L, SEEK_SET);

  char *contents = calloc(2*sz, sizeof(char));
  if (contents==NULL) {
    fprintf(stderr, "Could not allocate memory. Buy more RAM I guess?\n");
    exit(1);
  }
  fread(contents, 1, sz, f);

  fclose(f);
  
  return contents;
}


