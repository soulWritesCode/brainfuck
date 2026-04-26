#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "file.h"

#define NUM_ELEMENTS 32768 // 2 ^ 15

int main(int argc, char **argv)
{
  if (argc < 2) {
    printf("bf: no file provided.\n");
    return EXIT_FAILURE;
  }
  
  char* filename = argv[1];
  
  char* file = read_file(filename);
  
  if (file == NULL) {
    fprintf(stderr, "bf: failed to read file.\n");
    return EXIT_FAILURE;
  }
  
  uint8_t *array = (uint8_t *)calloc(NUM_ELEMENTS, sizeof(uint8_t));
  uint16_t dp = 0;

  if (array == NULL) {
    fprintf(stderr, "bf: memory allocation failed.\n");
    return EXIT_FAILURE;
  }

  char *element = file;
  while (*element != '\0') {
    switch (*element) {
      case '>':
        dp = (dp + 1 + NUM_ELEMENTS) % NUM_ELEMENTS;
        break;
      case '<':
        dp = (dp - 1 + NUM_ELEMENTS) % NUM_ELEMENTS;
        break;
      case '-':
        array[dp] = array[dp] - 1;
        break;
      case '+':
        array[dp] = array[dp] + 1;
        break;
      case '.':
        printf("%c", (char)array[dp]);
        break;
      case '[':
        if (array[dp] == 0) {
          int depth = 1;
          while (depth > 0) {
            element++;
            if (*element == '[') depth++;
            if (*element == ']') depth--;
          }
        }
        break;
      case ']':
        if (array[dp] != 0) {
          int depth = 1;
          while (depth > 0) {
            element--;
            if (element < file) break;
            if (*element == ']') depth++;
            if (*element == '[') depth--;
          }
        }
    }

    element++;
  }

  free(file);
  free(array);
  array = NULL;

  return 0;

}
