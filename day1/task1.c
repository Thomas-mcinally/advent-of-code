#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 256

int main() {
    // Open the file for reading
    FILE *file = fopen("./input.txt", "r");
    
    // Check if the file is opened successfully
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Allocate memory for an array of strings
    char **lines = NULL;
    int lineCount = 0;

    // Temporary buffer for reading each line
    char buffer[MAX_LINE_LENGTH];

    // Read lines from the file
    while (fgets(buffer, MAX_LINE_LENGTH, file) != NULL) {
        // Allocate memory for the current line
        lines = realloc(lines, (lineCount + 1) * sizeof(char *));
        if (lines == NULL) {
            perror("Error allocating memory");
            return 1;
        }

        // Allocate memory for the current line and copy it
        lines[lineCount] = malloc(strlen(buffer) + 1);
        if (lines[lineCount] == NULL) {
            perror("Error allocating memory");
            return 1;
        }
        strcpy(lines[lineCount], buffer);

        // Increment the line count
        lineCount++;
    }

    // Close the file
    fclose(file);

    int count = 0;

    // Iterate over each line
    for (int i = 0; i < lineCount; i++) {
	int j = 0;
	int found = 0;
	while (found == 0){
		if (isdigit(lines[i][j])){
			int digit = lines[i][j] - '0';
			count += digit * 10;
			found = 1;
		}
	
		j += 1;
	}

	j = strlen(lines[i]) - 1;
	found = 0;
	while (found == 0){
		if (isdigit(lines[i][j])){
			count += lines[i][j] - '0';
			found = 1;
		}
		j -= 1;
	}
	free(lines[i]);
    }
    free(lines);
    printf("%i", count);
    return 0;
}
	
