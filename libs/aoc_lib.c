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