#ifndef _CYOA_
#define _CYOA_

#include <errno.h>
#include <limits.h>

#include <exception>
#include <fstream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#include "page.hpp"
class InvalidPage : public std::exception {
 public:
  virtual const char * what() const throw() { return "Invalid page format!"; }
};

class InvalidStory : public std::exception {
 public:
  virtual const char * what() const throw() { return "Invalid story format!"; }
};

class InvalidFilename : public std::exception {
 public:
  virtual const char * what() const throw() { return "Invalid page filename!"; }
};

void findWinPaths(const Story & story);
void findWinPathHelper(unsigned currPgNum,
                       std::string currPath,
                       const std::vector<Page> pages,
                       std::vector<std::string> & paths,
                       std::set<unsigned> visited);
void pageDepth(const Story & story);
void verifyStory(const Story & story);
Story readPages(const char * dir);
unsigned strToInt(const char * str);
void parseNavigation(std::istream & is,
                     std::vector<std::string> & navigationText,
                     std::vector<unsigned> & choices,
                     int & isLastPage);
void verifyFilename(char * str);
Page parsePage(std::istream & is);
void parseChoices(std::istream & is,
                  std::string & str,
                  std::vector<std::string> & navigationText,
                  std::vector<unsigned> & choices);
#endif
