#include <iostream>

#include "cyoa.hpp"
#include "page.hpp"
int main(int argc, char ** argv) {
  if (argc != 2) {
    std::cerr << "Invalid command line argument!" << std::endl;
    return EXIT_FAILURE;
  }
  try {
    Story story = readPages(argv[1]);
    verifyStory(story);
    pageDepth(story);  // prints the depth of each page
  }
  catch (std::exception & e) {  // catches if story is invalid
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
