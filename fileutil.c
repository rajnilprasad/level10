#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fileutil.h"

// DIRECTIONS
// Choose whether you are doing the 2D array or
// the array of arrays.
// For the 2D array,
//    implement loadFile2D, substringSearch2D, and free2D.
// For the array of arrays, 
//    implement loadFileAA, substringSearchAA, and freeAA.


// Load the text file from the given filename.
// Return a pointer to the array of strings.
// Sets the value of size to be the number of valid
// entries in the array (not the total array length).
char ** loadFileAA(char *filename, int *size)
{
	FILE *in = fopen(filename, "r");
	if (!in)
	{
	    perror("Can't open file");
	    exit(1);
	}

	char **arr = NULL; // Pointer to array of strings
    char buffer[256];  // Buffer to read lines
    int count = 0;     // Number of entries
    int capacity = 10; // Initial capacity
	
	// TODO
	// Allocate memory for an array of strings (arr).
	arr = malloc(capacity * sizeof(char *));
    if (!arr) {
        perror("Memory allocation failed");
        fclose(in);
        exit(1);
    }
	// Read the file line by line.
	while (fgets(buffer, sizeof(buffer), in) != NULL) {
    //   Trim newline.
	buffer[strcspn(buffer, "\n")] = 0;
	//   Expand array if necessary (realloc).
	if (count >= capacity) {
            capacity *= 2;
            arr = realloc(arr, capacity * sizeof(char *));
            if (!arr) {
                perror("Memory reallocation failed");
                fclose(in);
                exit(1);
            }
        }
	//   Allocate memory for the string (str).
	//   Copy each line into the string (use strcpy).
	//   Attach the string to the large array (assignment =).
    // Close the file.
	 arr[count] = malloc((strlen(buffer) + 1) * sizeof(char));
        if (!arr[count]) {
            perror("Memory allocation for string failed");
            fclose(in);
            exit(1);
        }
        strcpy(arr[count], buffer);
        count++;
    }

	 fclose(in);
	// The size should be the number of entries in the array.
	*size = count;
	
	// Return pointer to the array of strings.
	return arr;

}

char * substringSearchAA(char *target, char **lines, int size) {
    for (int i = 0; i < size; i++) {
        if (strstr(lines[i], target) != NULL) {
            return lines[i]; // Return the first matching string
        }
    }
    return NULL; // No match found
}

// Free the memory used by the array
void freeAA(char **arr, int size) {
    for (int i = 0; i < size; i++) {
        free(arr[i]); // Free each string
    }
    free(arr); // Free the array of pointers
}