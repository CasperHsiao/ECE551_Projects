#include <iostream>

#include "cyoa.hpp"
#include "page.hpp"
int main(int argc, char ** argv) {
  if (argc != 2) {  // takes only one command line argument
    std::cerr << "Invalid command line argument!" << std::endl;
    return EXIT_FAILURE;
  }
  std::ifstream ifs(argv[1], std::ifstream::in);
  if (!ifs.is_open()) {
    std::cerr << "Invalid filename!" << std::endl;
    return EXIT_FAILURE;
  }
  try {
    verifyFilename(argv[1]);         // verify filename
    Page curr = parsePage(ifs);      // parse input file
    std::cout << curr << std::endl;  // print the page
  }
  catch (std::exception & e) {  // catches if filename or page format is invalid
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }
  ifs.close();
  return EXIT_SUCCESS;
}
