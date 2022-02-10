// Student: Casper Hsiao
// 09.25.2021
// ECE 551
// Evaluative Assignemnt 1
// Parses, computes, and prints COVID-19 information.

#include "pandemic.h"

#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>

/**
 * Handles error by  printing the error message and exit the program with
 * a failure status.
 * @param func - The name of the function in which the error occurred.
 * @param rsn - A briefy reason why the error occured.
 */
void errorMsg(char * func, char * rsn) {
  fprintf(stderr, "Invalid input for %s! Attempted to pass in %s.\n", func, rsn);
  exit(EXIT_FAILURE);
}

/**
 * Parses a string input to extract the name of the country and store 
 * it inside the country struct.
 * pre: The country name must not be empty or exceed 63 characters.
 * The country name terminates with a comma character. 
 * Otherwise, the program exits with a error message.
 * @param country - The struct to store the parsed country name.
 * @param ptr1 - The pointer to the string input.  
 */
void parseName(country_t * country, char ** ptr1, size_t len) {
  size_t i = 0;
  while (**ptr1 != ',' && i < 63 && i < len) {
    country->name[i] = **ptr1;
    i++;
    *ptr1 += 1;
  }
  if (**ptr1 != ',') {
    errorMsg("parseLine", "a string of incorrect format");
  }
  if (i == 63 || i == 0) {
    errorMsg("parseLine", "a country name of incorrect length");
  }
  else {
    country->name[i] = '\0';
  }
}

/**
 * Parses a string input to extract the population of the country and
 * store it inside the country struct.
 * pre: The population must represent a number that fits in uint64_t.
 * The population terminates with a comma character. The poulation must
 * not be empty. Otherwise, the program exits with a error message. 
 * @param country - The struct to store the parsed population.
 * @param ptr2 - The pointer to the string input at the last character.
 * @param lastIndex - The last index of the string input.
 */
void parsePopulation(country_t * country, char ** ptr2, size_t lastIndex) {
  size_t j = lastIndex;
  while (**ptr2 != ',' && j >= 0) {
    if (j != 0) {
      j--;
      *ptr2 -= 1;
    }
  }
  if (**ptr2 != ',') {
    errorMsg("parseLine", "a string with incorrect format");
  }
  if (j == lastIndex) {
    errorMsg("parseLine", "a string with population that is empty");
  }
  uint64_t ans = strtoull(*ptr2 + 1, NULL, 10);
  if (ans == 0ULL) {
    errorMsg("parseLine", "a string with population that is invalid");
  }
  if (ans == ULLONG_MAX && errno == ERANGE) {
    perror("Invalid input for parseLine!");
    exit(EXIT_FAILURE);
  }
  country->population = ans;
}

/**
 * Parses a string input to extract the country name and population, and
 * returns a country_t struct with those information.
 * pre: Accept strings with the correct format - country name,population.
 * Otherwise, prints a error message, and exit with failure status.
 * @param line - The string input to be parsed.
 * @return country - The struct with the country name and population.
 */
country_t parseLine(char * line) {
  if (line == NULL) {
    errorMsg("parseLine", "a NULL pointer");
  }
  size_t len = strlen(line);
  if (len < 2) {
    errorMsg("parseLine", "a string of incorrect length");
  }
  country_t country;
  char * ptr1 = line;  // points at first character
  size_t j = len - 1;
  if (line[j] == '\n') {  // exclude line feed
    j--;
    len--;
  }
  char * ptr2 = line + j;  // points at last character
  parseName(&country, &ptr1, len);
  parsePopulation(&country, &ptr2, j);
  if (ptr2 != ptr1) {
    errorMsg("parseLine", "a string of incorrect format");
  }
  return country;
}

/**
 * Calculates the seven-day running average of case data.
 * @param data - The case data.
 * @param n_days - The number of days over which the data is measured.
 * @param avg - Stores the seven-day running average of case data..
 */
void calcRunningAvg(unsigned * data, size_t n_days, double * avg) {
  size_t avgLen = n_days - 6;
  if (avgLen < 1) {
    errorMsg("calcRunningAvg", "an data of incorrect length");
  }
  for (size_t i = 0; i < avgLen; i++) {
    uint sum = 0;
    for (size_t j = i; j < i + 7; j++) {
      sum += data[j];
    }
    double tempAvg = sum / 7.0;
    avg[i] = tempAvg;
  }
}

/**
 * Calculates the cumulative number of cases that day per 100,000 people.
 * @param data - The case data.
 * @param n_days - The number of days over which the data is measured.
 * @param pop - The population for that country
 * @param cum - The culumative number of cases that day per 100,000 people.
 */
void calcCumulative(unsigned * data, size_t n_days, uint64_t pop, double * cum) {
  if (n_days < 1) {
    errorMsg("calcCumulative", "an data of incorrect length");
  }
  unsigned prevSum = 0;
  for (size_t i = 0; i < n_days; i++) {
    double curr = data[i] + prevSum;
    double cumCases = curr / pop * 100000;
    cum[i] = cumCases;
    prevSum = curr;
  }
}

/**
 * Finds the maximum number of daily cases of all countries represented
 * in the data, and prints the country name with the number of cases.
 * @param countries - The countries represented.
 * @param n_countries - The number of countries.
 * @param data - The case data.
 * @param n_days - The number of days represented.
 */
void printCountryWithMax(country_t * countries,
                         size_t n_countries,
                         unsigned ** data,
                         size_t n_days) {
  if (n_countries < 1 || n_days < 1) {
    errorMsg("printCountrywithmax", "array of incorrect length");
  }
  const char * maxCountry = countries[0].name;
  unsigned max = data[0][0];
  uint8_t tie = 0;
  for (size_t day = 0; day < n_days; day++) {
    for (size_t country = 1; country < n_countries; country++) {
      if (data[country][day] > max) {
        tie = 0;
        max = data[country][day];
        maxCountry = countries[country].name;
      }
      else if (data[country][day] == max) {
        tie++;
      }
    }
  }
  if (tie > 0) {
    printf("There is a tie between at least two countries\n");
  }
  else {
    printf("%s has the most daily cases with %u\n", maxCountry, max);
  }
}
