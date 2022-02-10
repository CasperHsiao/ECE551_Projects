#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "provided.h"

//any functions you want your main to use
void parseTemplate(FILE * f, catarray_t * catarr, int option);
void parseLine(const char * line,
               catarray_t * catarr,
               category_t * prevWords,
               int option);
void extractBlankCat(const char * line, char * blankWord, size_t * index);
unsigned long int isInt(char * str);
void printCatWord(catarray_t * catarr,
                  char * blankWord,
                  category_t * prevWords,
                  int option);
void removeWord(category_t * category, const char * word);
void printPrevWord(unsigned long int num, category_t * prevWords);
/////////////////////////////////////////////////////////////////////////////////
catarray_t * storeWords(FILE * f);
void extractCatWord(const char * line, char * cat, char * word);
category_t * getCat(const catarray_t * catarr, const char * cat);
category_t * addNewCat(catarray_t * catarr, char * cat);
void addNewWord(category_t * category, char * word);
void freeCatarr(catarray_t * catarr);
void freeCat(category_t * category);

#endif
