#include "page.hpp"

Page::Page(const std::vector<std::string> & nT,
           const std::vector<std::string> & bT,
           const std::vector<unsigned> & c,
           const int status) :
    navigationText(nT),
    bodyText(bT),
    choices(c),
    status(status) {
}

/**
 * Prints out the page class with the specified format
 */
std::ostream & operator<<(std::ostream & s, const Page & page) {
  for (std::vector<std::string>::const_iterator it = page.bodyText.begin();
       it != page.bodyText.end();
       ++it) {
    s << *it << std::endl;
  }
  for (std::vector<std::string>::const_iterator it = page.navigationText.begin();
       it != page.navigationText.end();
       ++it) {
    s << std::endl << *it;
  }
  return s;
}
