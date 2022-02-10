#include "outname.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * computeOutputFileName(const char * inputName) {
  //WRITE ME
  char * ans = malloc((strlen(inputName) + 8) * sizeof(*ans));
  strcpy(ans, inputName);
  strcat(ans, ".counts");
  return ans;
}
