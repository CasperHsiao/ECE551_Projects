#include "rand_story.h"

/**
 * This program parses the story template by printing the story and
 * replacing blanks with the word "cat".
 * pre: Takes in one command line argument: the name of the file to
 * read the story template from.
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
  parseTemplate(f, NULL, -1);
  if (fclose(f) != 0) {
    fprintf(stderr, "Unable to close file!\n");
    exit(EXIT_FAILURE);
  }
  return EXIT_SUCCESS;
}
