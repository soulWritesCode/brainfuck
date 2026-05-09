#include "file.h"

char* read_file(const char* filename)
{
  FILE* file = fopen(filename, "rb");
  if (!file) {
    perror("bf: error opening file");
    return NULL;
  }

  fseek(file, 0, SEEK_END);
  long fsize = ftell(file);
  fseek(file, 0, SEEK_SET);

  char* buf = malloc(fsize + 1); // file size + space for \0
  if (buf) {
    fread(buf, 1, fsize, file);
    buf[fsize] = 0; // null terminate the string
  }

  fclose(file);

  return buf;
}

FILE *open_file(const char* filename) {
  FILE *fptr;
  fptr = fopen(filename, "w");

  assert(fptr != NULL);

  return fptr;
}
