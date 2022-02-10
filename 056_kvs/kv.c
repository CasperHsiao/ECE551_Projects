#include "kv.h"

#include <stdio.h>
#include <string.h>

int parseLine(char * line, kvarray_t * kv) {
  char * ptr = line;
  int i = 0;
  kvpair_t * ans = &kv->arr[kv->sz];
  ans->key = NULL;
  while (*ptr != '\n' && *ptr != '=') {
    ans->key = realloc(ans->key, (i + 2) * sizeof(*(ans->key)));
    ans->key[i] = *ptr;
    i++;
    ptr++;
  }
  if (*ptr != '=' || i == 0) {
    fprintf(stderr, "Incorrect line format!\n");
    return -1;
  }
  ans->key[i] = '\0';
  ptr++;
  i = 0;
  ans->val = NULL;
  while (*ptr != '\n') {
    ans->val = realloc(ans->val, (i + 2) * sizeof(*(ans->val)));
    ans->val[i] = *ptr;
    i++;
    ptr++;
  }
  if (*ptr != '\n' || i == 0) {
    fprintf(stderr, "Incorrect line format!\n");
    return -1;
  }
  ans->val[i] = '\0';
  return 0;
}

int parseFile(kvarray_t * kv, FILE * f) {
  char * line = NULL;
  size_t size;
  kv->arr = NULL;
  kv->sz = 0;
  while (getline(&line, &size, f) != -1) {
    kv->arr = realloc(kv->arr, (kv->sz + 1) * sizeof(*kv->arr));
    if (kv->arr == NULL) {
      fprintf(stderr, "Cannot allocate heap memory!\n");
      free(line);
      return -1;
    }
    if (parseLine(line, kv) != 0) {
      kv->sz++;
      free(line);
      return -1;
    }
    kv->sz++;
  }
  free(line);
  return 0;
}

void closeFile(FILE * f) {
  if (fclose(f) != 0) {
    fprintf(stderr, "Unable to close file!\n");
    exit(EXIT_FAILURE);
  }
}

kvarray_t * readKVs(const char * fname) {
  //WRITE ME
  FILE * f = fopen(fname, "r");
  if (f == NULL) {
    fprintf(stderr, "Unable to open the file!\n");
    exit(EXIT_FAILURE);
  }
  kvarray_t * ans = malloc(sizeof(*ans));
  if (ans == NULL) {
    fprintf(stderr, "Connot allocate heap memory!\n");
    exit(EXIT_FAILURE);
  }
  if (parseFile(ans, f) != 0) {
    freeKVs(ans);
    closeFile(f);
    exit(EXIT_FAILURE);
  }
  closeFile(f);
  return ans;
}

void freeKVs(kvarray_t * pairs) {
  //WRITE ME
  for (int i = 0; i < pairs->sz; i++) {
    free(pairs->arr[i].key);
    free(pairs->arr[i].val);
  }
  free(pairs->arr);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  //WRITE ME
  for (int i = 0; i < pairs->sz; i++) {
    printf("key = '%s' value = '%s'\n", pairs->arr[i].key, pairs->arr[i].val);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME
  char * ans = NULL;
  for (int i = 0; i < pairs->sz; i++) {
    if (strcmp(key, pairs->arr[i].key) == 0) {
      return pairs->arr[i].val;
    }
  }
  return ans;
}
