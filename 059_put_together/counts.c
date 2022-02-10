#include "counts.h"

#include <stdlib.h>
#include <string.h>
counts_t * createCounts(void) {
  counts_t * ans = malloc(sizeof(*ans));
  ans->arr = NULL;
  ans->sz = 0;
  ans->unknownCounts = 0;
  return ans;
}
void addCount(counts_t * c, const char * name) {
  //WRITE ME
  if (name != NULL) {
    int cmp = 1;
    for (int i = 0; i < c->sz; i++) {
      if ((cmp = strcmp(c->arr[i].str, name)) == 0) {
        c->arr[i].count += 1;
        break;
      }
    }
    if (cmp != 0) {
      c->arr = realloc(c->arr, (c->sz + 1) * sizeof(*c->arr));
      c->sz++;
      c->arr[c->sz - 1].str = malloc((strlen(name) + 1) * sizeof(*name));
      strcpy(c->arr[c->sz - 1].str, name);
      c->arr[c->sz - 1].count = 1;
    }
  }
  else {
    c->unknownCounts++;
  }
}
void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME
  for (int i = 0; i < c->sz; i++) {
    fprintf(outFile, "%s: %d\n", c->arr[i].str, c->arr[i].count);
  }
  if (c->unknownCounts > 0) {
    fprintf(outFile, "<unknown> : %d\n", c->unknownCounts);
  }
}

void freeCounts(counts_t * c) {
  //WRITE ME
  for (int i = 0; i < c->sz; i++) {
    free(c->arr[i].str);
  }
  free(c->arr);
  free(c);
}
