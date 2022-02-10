#include <iostream>

#include "cyoa.hpp"
#include "page.hpp"
int main(int argc, char ** argv) {
  if (argc != 2) {
    std::cerr << "Invalid command line argument!" << std::endl;
    return EXIT_FAILURE;
  }
  try {
    Story story = readPages(argv[1]);  // construct the story object
    verifyStory(story);                // verify that the story met the requirement
    std::vector<Page> pages = story.getPages();
    Page currPage = pages[0];
    unsigned pageNum = 1;
    std::cout << currPage << std::endl;  // print page1.txt prompt for user
    std::string input;
    while (getline(std::cin, input)) {  // get input from user repeatedly
      std::vector<unsigned> choices = currPage.getChoices();
      try {
        // Checks valid input
        unsigned select = strToInt(input.c_str());
        if (select > choices.size()) {
          throw InvalidPage();
        }
        pageNum = choices[select - 1];
        currPage = pages[pageNum - 1];  // update current page
        std::cout << currPage << std::endl;
        // Exit success if WIN or LOSE
        if (currPage.getStatus() != 0) {
          return EXIT_SUCCESS;
        }
      }
      catch (std::exception & e) {  // catches invalid input from user
        std::cout << "That is not a valid choice, please try again" << std::endl;
      }
    }
  }
  catch (std::exception & e) {  // catches if story is invalid
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
