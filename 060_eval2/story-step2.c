#include "rand_story.h"

/**
 * The program parses a file and stores the categories and words into a
 * catarray_t struct. Prints the catarray using the printWords function.
 * pre: Takes one command line argument: the name of the file with the
 * categories and words.
 */
int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Incorrect command line argument!\n");
    exit(EXIT_FAILURE);
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    fprintf(stderr, "Unable to open the file!\n");
    exit(EXIT_FAILURE);
  }
  catarray_t * catarr = storeWords(f);
  printWords(catarr);
  freeCatarr(catarr);
  if (fclose(f) != 0) {
    fprintf(stderr, "Unable to close file!\n");
    exit(EXIT_FAILURE);
  }
  return EXIT_SUCCESS;
}
