#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void writeMatrix(char mtx[10][11], int dmn, char * str, int row) {
  for (int col = 0; col < dmn; col++) {
    mtx[col][10 - row] = str[col];
  }
}

void printMatrix(char mtx[10][11]) {
  for (int row = 0; row < 10; row++) {
    for (int col = 0; col < 11; col++) {
      fputc(mtx[row][col], stdout);
    }
  }
}

void rotateMatrix(FILE * stream) {
  int dmn = 10;       //dimension
  char str[dmn + 2];  //account for line feed and null-terminator
  int line = 0;
  char mtx[dmn][dmn + 1];
  while (fgets(str, dmn + 2, stream) != NULL) {
    line++;
    if (strchr(str, '\n') == NULL) {
      fprintf(stderr, "Incorrect dimensions! (line is too long)\n");
      exit(EXIT_FAILURE);
    }
    //printf("%ld\n", strchr(str, '\n') - str);
    if (strchr(str, '\n') - str != dmn) {
      fprintf(stderr, "Incorrect dimensions! (line is too short)\n");
      exit(EXIT_FAILURE);
    }
    if (line > 10) {
      fprintf(stderr, "Incorrect dimensions! (too many lines)\n");
      exit(EXIT_FAILURE);
    }
    writeMatrix(mtx, dmn, str, line);
  }
  if (ferror(stream) != 0) {
    fprintf(stderr, "An error has occured!\n");
    exit(EXIT_FAILURE);
  }
  if (line < 10) {
    fprintf(stderr, "Incorrect dimensions! (too few lines)\n");
    exit(EXIT_FAILURE);
  }
  for (int row = 0; row < dmn; row++) {
    mtx[row][dmn] = '\n';
  }
  printMatrix(mtx);
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: rotateMatrix inputFileName\n");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Could not open file");
    return EXIT_FAILURE;
  }
  rotateMatrix(f);
  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }
  return EXIT_FAILURE;
}
