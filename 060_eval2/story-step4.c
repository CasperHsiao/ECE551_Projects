#include "rand_story.h"

/**
 * This program parses and prints the story template, by replacing the category
 * names with words from the input file. Provides a option for no reuse of words.
 * pre: Takes in two required and one optional command line arguments: name of 
 * the file to read the story template from, name of the file with the categories
 * and words, and the option to avoid reusing words.
 */
int main(int argc, char ** argv) {
  if (argc > 4 || argc < 3) {
    fprintf(stderr, "Incorrect command line argument!\n");
    exit(EXIT_FAILURE);
  }
  int option = 0;
  FILE * f1 = NULL;
  FILE * f2 = NULL;
  if (argc == 4) {  //contains option
    if (strcmp(argv[1], "-n") != 0) {
      fprintf(stderr, "Incorrect command line argument!\n");
      exit(EXIT_FAILURE);
    }
    option = 1;
    f1 = fopen(argv[2], "r");  //open the categories/words file
    if (f1 == NULL) {
      fprintf(stderr, "Unable to open the file!\n");
      exit(EXIT_FAILURE);
    }
    f2 = fopen(argv[3], "r");
    if (f2 == NULL) {
      fprintf(stderr, "Unable to open the file!\n");
      exit(EXIT_FAILURE);
    }
  }
  else {
    option = -1;
    f1 = fopen(argv[1], "r");  //open the categories/words file
    if (f1 == NULL) {
      fprintf(stderr, "Unable to fgopen the file!\n");
      exit(EXIT_FAILURE);
    }
    f2 = fopen(argv[2], "r");
    if (f2 == NULL) {
      fprintf(stderr, "Unable to open the file!\n");
      exit(EXIT_FAILURE);
    }
  }
  catarray_t * catarr = storeWords(f1);
  parseTemplate(f2, catarr, option);
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
