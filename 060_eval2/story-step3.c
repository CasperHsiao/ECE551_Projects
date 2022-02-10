#include "rand_story.h"

/**
 * This program parses and prints the story template, by replacing the category
 * names with words from the input file.
 * pre: Takes in two command line arguments: name of the file to read the story
 * template from and name of the file with the categories and words
 */
int main(int argc, char ** argv) {
  if (argc != 3) {
    fprintf(stderr, "Incorrect command line argument!\n");
    exit(EXIT_FAILURE);
  }
  FILE * f1 = fopen(argv[1], "r");  //open the categories/words file
  if (f1 == NULL) {
    fprintf(stderr, "Unable to open the file!\n");
    exit(EXIT_FAILURE);
  }
  FILE * f2 = fopen(argv[2], "r");
  if (f2 == NULL) {
    fprintf(stderr, "Unable to open the file!\n");
    exit(EXIT_FAILURE);
  }
  catarray_t * catarr = storeWords(f1);
  parseTemplate(f2, catarr, -1);
  freeCatarr(catarr);
  if (fclose(f1) != 0) {
    fprintf(stderr, "Unable to close file!\n");
    exit(EXIT_FAILURE);
  }
  if (fclose(f2) != 0) {
    fprintf(stderr, "Unable to close file!\n");
    exit(EXIT_FAILURE);
  }
  return EXIT_SUCCESS;
}
