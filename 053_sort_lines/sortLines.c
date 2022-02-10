#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//This function is used to figure out the ordering of the strings
//in qsort. You do not need to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}

void print(FILE * stream) {
  char ** data = NULL;
  char * curr = NULL;
  size_t sz;
  int i = 0;
  while (getline(&curr, &sz, stream) >= 0) {
    data = realloc(data, (i + 1) * sizeof(*data));
    //if (data == NULL) {
    //fprintf(stderr, "Not enough heap memory!");
    //exit(EXIT_FAILURE);
    //}
    data[i] = curr;
    curr = NULL;
    i++;
  }
  free(curr);
  sortData(data, i);
  for (int j = 0; j < i; j++) {
    printf("%s", data[j]);
    free(data[j]);
  }
  free(data);
}

int main(int argc, char ** argv) {
  if (argc == 1) {
    print(stdin);
  }
  else {
    for (int i = 1; i < argc; i++) {
      FILE * f = fopen(argv[i], "r");
      if (f == NULL) {
        perror("Could not open file!");
        exit(EXIT_FAILURE);
      }
      print(f);
      if (fclose(f) != 0) {
        perror("Failed to close input file!");
        exit(EXIT_FAILURE);
      }
    }
  }

  return EXIT_SUCCESS;
}
