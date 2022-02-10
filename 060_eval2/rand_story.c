#include "rand_story.h"

/**
 * Frees the memory allocated for a category.
 * @param category - The category_t struct to be freed.
 */
void freeCat(category_t * category) {
  if (category->n_words != 0) {
    for (size_t j = 0; j < category->n_words; j++) {
      free(category->words[j]);
    }
    free(category->words);
  }
  free(category->name);
}

/**
 * Frees the memory allocated for the catarray.
 * @param catarr - The catarray_t struct to be freed.
 */
void freeCatarr(catarray_t * catarr) {
  for (size_t i = 0; i < catarr->n; i++) {
    category_t * category = &catarr->arr[i];
    freeCat(category);
  }
  free(catarr->arr);
  free(catarr);
}

/**
 * Adds a new word to a category.
 * @param category - The category_t struct to add the word to.
 * @param word - The word to be added.
 */
void addNewWord(category_t * category, char * word) {
  size_t * n = &category->n_words;
  category->words = realloc(category->words, (*n + 1) * sizeof(*category->words));
  if (category->words == NULL) {
    fprintf(stderr, "Unable to allocate heap memory!\n");
    exit(EXIT_FAILURE);
  }
  *n += 1;
  category->words[*n - 1] = word;
}

/**
 * Adds a new category to the catarray.
 * Returns a pointer to the new category_t.
 * @param catarr - The catarray_t struct to add to.
 * @param cat - The name of the category to be added.
 */
category_t * addNewCat(catarray_t * catarr, char * cat) {
  catarr->arr = realloc(catarr->arr, (catarr->n + 1) * sizeof(*catarr->arr));
  if (catarr->arr == NULL) {
    fprintf(stderr, "Unable to allocate heap memory!\n");
    exit(EXIT_FAILURE);
  }
  catarr->n++;
  category_t * category = &catarr->arr[catarr->n - 1];
  category->name = cat;
  category->n_words = 0;
  category->words = NULL;
  return category;
}

/**
 * Finds a category, stored inside of the catarray, by its name.
 * Returns a pointer to the category found. Returns NULL if not found.
 * @param catarr - The cataray_t struct to search through.
 * @param cat - The name of the category.
 */
category_t * getCat(const catarray_t * catarr, const char * cat) {
  for (size_t i = 0; i < catarr->n; i++) {
    if (strcmp(catarr->arr[i].name, cat) == 0) {
      return &catarr->arr[i];
    }
  }
  return NULL;
}

/**
 * Extracts the category name and its corresponding word from a line.
 * pre: The line must contain at least one ':' character. Otherwise,
 * exit with a failure status.
 * @param line - The string of the line to extract.
 * @param cat - The string to store the extracted category name.
 * @param word - The string to store the extracted word.
 */
void extractCatWord(const char * line, char * cat, char * word) {
  size_t i = 0;
  while (i < strlen(line) && line[i] != ':') {
    cat[i] = line[i];
    i++;
  }
  if (line[i] != ':') {  //does not contain ':'
    fprintf(stderr, "Words conatain incorrect formatted line!\n");
    exit(EXIT_FAILURE);
  }
  cat[i] = '\0';
  size_t j = i + 1;
  while (j < strlen(line) && line[j] != '\n') {
    word[j - i - 1] = line[j];
    j++;
  }
  if (j >= strlen(line)) {  //does not contain line feed
    fprintf(stderr, "Words contain incorrect formatted line!\n");
    exit(EXIT_FAILURE);
  }
  word[j - i - 1] = '\0';
}

/**
 * Parses the file that stores the category names and their corresponding
 * words, and store the data into a catarray_t struct.
 * Returns the catarray_t storing the data.
 * @param f - The file to be parsed.
 */
catarray_t * storeWords(FILE * f) {
  char * line = NULL;
  size_t sz;
  catarray_t * catarr = malloc(sizeof(*catarr));
  if (catarr == NULL) {
    fprintf(stderr, "Unable to allocate heap memory!\n");
    exit(EXIT_FAILURE);
  }
  catarr->n = 0;
  catarr->arr = NULL;
  while (getline(&line, &sz, f) != -1) {
    char * cat = malloc((strlen(line) + 1) * sizeof(*cat));
    char * word = malloc((strlen(line) + 1) * sizeof(*word));
    if (cat == NULL || word == NULL) {
      fprintf(stderr, "Unable to allocate heap memory!\n");
      exit(EXIT_FAILURE);
    }
    extractCatWord(line, cat, word);
    category_t * category;

    if ((category = getCat(catarr, cat)) == NULL) {
      category = addNewCat(catarr, cat);
    }
    else {
      free(cat);
    }
    addNewWord(category, word);
  }
  free(line);
  return catarr;
}

/**
 * Prints a previously used word, given a integer counting backwards
 * from the current word. For example, the number 1 would print the 
 * last used word. And, stores the word printed to the category of
 * previously used words. 
 * pre: The number given must not exceed the number of previously used
 * words. Otherwise, exit with a failure status.
 * @param num - The integer indicating which previously used word to print.
 * @param preWords - The category_t struct that stores all the previously
 * used words.
 */
void printPrevWord(unsigned long int num, category_t * prevWords) {
  if (num > prevWords->n_words) {
    fprintf(stderr, "Story template contains invalid integer!\n");
  }
  char * word = strdup(prevWords->words[prevWords->n_words - num]);
  if (word == NULL) {
    fprintf(stderr, "Unable to allocate heap memory!\n");
    exit(EXIT_FAILURE);
  }
  addNewWord(prevWords, word);
  printf("%s", word);
}

/**
 * Removes a word from a category.
 * @param category - The category_t struct that contains the word
 * to be removed from.
 * @param word - The word to be removed.
 */
void removeWord(category_t * category, const char * word) {
  char ** words = NULL;
  if (category->n_words > 1) {
    words = malloc((category->n_words - 1) * sizeof(*words));
  }
  size_t j = 0;
  int removed = 0;
  for (size_t i = 0; i < category->n_words; i++) {
    if (strcmp(category->words[i], word) == 0 && removed == 0) {
      free(category->words[i]);
      removed = 1;
    }
    else {
      words[j] = category->words[i];
      j++;
    }
  }
  free(category->words);
  category->n_words--;
  category->words = words;
}

/**
 * Prints a word chosen by the chooseWord function with a given category.
 * A option is provided to determine if this function will remove the word
 * printed from its category, to avoid reusing the word.
 * stores the word printed to the category of previously used words.
 * @param catarr - The catarray_t struct storing all the category_t structs.
 * @param blankCat - The name of the category that chooseWord function 
 * chooses a word from.
 * @param preWords - The category_t struct that stores all the previously
 * used words.
 * @param option - The option that indicates if a word should be removed 
 * from its category after printing it. If the option is positive, remove
 * the printed word.
 */
void printCatWord(catarray_t * catarr,
                  char * blankCat,
                  category_t * prevWords,
                  int option) {
  category_t * category = getCat(catarr, blankCat);
  if (category == NULL) {
    fprintf(stderr, "Story template contains invalid category name!\n");
    exit(EXIT_FAILURE);
  }
  char * word = strdup(chooseWord(blankCat, catarr));
  if (word == NULL) {
    fprintf(stderr, "Unable to allocate heap memory!\n");
    exit(EXIT_FAILURE);
  }
  if (option > 0) {
    removeWord(category, word);
  }
  addNewWord(prevWords, word);
  printf("%s", word);
}

/**
 * Determines if the given string is a valid integer.
 * pre: The integer value must not be less than 1 or overflow during the
 * strtol function. Otherwise, exit with a failure status
 * Returns 0 if the string is not a valid integer. Otherwise, return its
 * integer value.
 * @param str - The string to be determined.
 */
unsigned long int isInt(char * str) {
  char * endptr = NULL;
  unsigned long int num;
  num = strtol(str, &endptr, 10);
  if (endptr == NULL && num == 0) {  // not a valid integer
    return 0;
  }
  if (!(*str != '\0' && *endptr == '\0')) {  // not a valid integer
    return 0;
  }
  if ((num == ULONG_MAX && errno == ERANGE) || num < 1) {
    fprintf(stderr, "Story template conatians invalid integer!\n");
    exit(EXIT_FAILURE);
  }
  return num;
}

/**
 * Extract the name of a category from the given line of the story template.
 * pre: The line must contain a pair of opening and closing '_' around the 
 * category name. Otherwise, exit with a failure status.
 * @param line - The string of line to extract from.
 * @param blankCat - The string to store the extracted category name.
 * @param index - The pointer to the index of where to read on the line.
 */
void extractBlankCat(const char * line, char * blankCat, size_t * index) {
  *index += 1;
  size_t i = 0;
  while (*index < strlen(line) && line[*index] != '_') {
    blankCat[i] = line[*index];
    *index += 1;
    i++;
  }
  if (line[*index] != '_') {
    fprintf(stderr, "Story template conatins incorrect formatted line!\n");
    exit(EXIT_FAILURE);
  }
  blankCat[i] = '\0';
}

/**
 * Parses and prints a given line of the story template, by replacing the
 * category names with words from the catarray and previously used words.
 * A option is provided to determine if this function will remove the used
 * word from its category, to avoid reusing the word.
 * @param line - The string of line to be parsed and printed.
 * @param catarr - The catarray_t struct that stores all the categories and
 * their corresponding words.
 * @param prevWords - The category_t that stores the previously used words.
 * @param option - The option that indicates if a word should be removed 
 * from its category after printing it. If the option is positive, remove
 * the printed word.
 */
void parseLine(const char * line,
               catarray_t * catarr,
               category_t * prevWords,
               int option) {
  for (size_t i = 0; i < strlen(line); i++) {
    if (line[i] == '_') {
      char * blankCat = malloc((strlen(line) - i) * sizeof(*blankCat));
      if (blankCat == NULL) {
        fprintf(stderr, "Unable to allocate heap memory!\n");
        exit(EXIT_FAILURE);
      }
      extractBlankCat(line, blankCat, &i);
      if (catarr == NULL) {
        printf("%s", chooseWord("", catarr));
      }
      else {
        unsigned long int num = isInt(blankCat);
        if (num == 0) {  //its a category
          printCatWord(catarr, blankCat, prevWords, option);
        }
        else {  //its a integer
          printPrevWord(num, prevWords);
        }
      }
      free(blankCat);
    }
    else {
      printf("%c", line[i]);
    }
  }
}

/**
 * Parses and prints the story template, by replacing the category names with
 * words from the catarray. A option is provided to determine if this function
 *  will remove the used word from its category, to avoid reusing the word.
 * @param f - The file to be parsed and printed.
 * @param catarr - The catarray_t struct that stores all the categories and
 * their corresponding words.
 * @param option - The option that indicates if a word should be removed 
 * from its category after printing it. If the option is positive, remove
 * the printed word.
 */
void parseTemplate(FILE * f, catarray_t * catarr, int option) {
  char * line = NULL;
  size_t sz;
  category_t * prevWords = malloc(sizeof(*prevWords));
  if (prevWords == NULL) {
    fprintf(stderr, "Unable to allocate heap memory!\n");
    exit(EXIT_FAILURE);
  }
  prevWords->name = malloc(sizeof(*prevWords->name));
  if (prevWords->name == NULL) {
    fprintf(stderr, "Unable to allocate heap memory!\n");
    exit(EXIT_FAILURE);
  }
  prevWords->n_words = 0;
  prevWords->words = NULL;
  while (getline(&line, &sz, f) != -1) {
    parseLine(line, catarr, prevWords, option);
  }
  free(line);
  freeCat(prevWords);
  free(prevWords);
}
