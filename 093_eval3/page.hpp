#ifndef _PAGE_
#define _PAGE_
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

class Page {
  std::vector<std::string> navigationText;
  std::vector<std::string> bodyText;
  std::vector<unsigned> choices;
  int status;  // 0:choicePage, 1:win, 2:lose

 public:
  Page(const std::vector<std::string> & nT,
       const std::vector<std::string> & bT,
       const std::vector<unsigned> & c,
       const int status = 0);
  std::vector<unsigned> getChoices() { return choices; }
  int getStatus() { return status; }  //optimize with enum later
  friend std::ostream & operator<<(std::ostream & s, const Page & page);
};

class Story {
  std::vector<Page> pages;

 public:
  Story(const std::vector<Page> & pgs) : pages(pgs) {}
  const std::vector<Page> getPages() const { return pages; }
};

#endif
