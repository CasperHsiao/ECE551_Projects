#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

void decode(FILE * f) {
  int c;
  int arr[26] = {0};
  while ((c = fgetc(f)) != EOF) {
    if (isalpha(c)) {
      c = tolower(c);
      c -= 'a';
      arr[c] += 1;
    }
  }
  int maxC = 0;
  int max = arr[0];
  for (size_t i = 1; i < 26; i++) {
    if (arr[i] > max) {
      max = arr[i];
      maxC = i;
    }
  }
  if (maxC >= 4) {
    printf("%d\n", maxC - 4);
  }
  else {
    printf("%d\n", maxC - 4 + 26);
  }
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: breaker inputFileName\n");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Could not open file");
    return EXIT_FAILURE;
  }
  decode(f);
  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
