#include "cyoa.hpp"

#include <queue>

/**
 * The recrusive function to find the win paths using DFS. Stores the win paths
 * to the @param(paths).
 */
void findWinPathHelper(unsigned currPgNum,
                       std::string currPath,
                       const std::vector<Page> pages,
                       std::vector<std::string> & paths,
                       std::set<unsigned> visited) {
  Page currPage = pages[currPgNum - 1];
  if (currPage.getStatus() == 2) {  // return to previous stack frame if LOSE
    return;
  }
  // append the current path to the result paths if WIN
  if (currPage.getStatus() == 1) {
    std::stringstream temp;
    temp << currPath << std::dec << currPgNum << "(win)" << std::endl;
    paths.push_back(temp.str());
    return;
  }
  std::vector<unsigned> choices = currPage.getChoices();
  visited.insert(currPgNum);
  for (size_t i = 0; i < choices.size(); i++) {
    unsigned neighbor = choices[i];
    // visit the neighbor if not visited in the current path yet
    // DO NOT visit if visited, since it will be a cycle
    if (visited.find(neighbor) == visited.end()) {
      std::stringstream temp;
      temp << currPath << std::dec << currPgNum << "(" << std::dec << i + 1 << "),";
      findWinPathHelper(neighbor, temp.str(), pages, paths, visited);
    }
  }
}

/**
 * The main function that calls the findWinPathhelper to find the win paths
 * Prints out all the possible win paths. If no win path exists, print this
 * story is unwinnable.
 */
void findWinPaths(const Story & story) {
  const std::vector<Page> pages = story.getPages();
  std::vector<std::string> paths;
  std::set<unsigned> visited;
  findWinPathHelper(1, "", pages, paths, visited);
  if (paths.size() == 0) {  // no win path exists
    std::cout << "This story is unwinnable!" << std::endl;
  }
  for (size_t i = 0; i < paths.size(); i++) {  // prints all win paths
    std::cout << paths[i];
  }
}

/**
 * The function to detect the depth of each page from page1.txt using BFS.
 * If a page is unreachable from page1.txt, prints unreachable. Otherwise,
 * the depth is printed.
 */
void pageDepth(const Story & story) {
  std::queue<unsigned> q;
  std::set<unsigned> visited;
  const std::vector<Page> pages = story.getPages();
  std::vector<int> pageDepths(pages.size(), -1);  // initialize the page depths with -1
  q.push(1);  // use queue data structure to run the BFS
  visited.insert(1);
  unsigned depth = 0;
  while (q.size() > 0) {
    size_t currLvl = q.size();
    for (size_t i = 0; i < currLvl; i++) {  // run all pages for current level
      unsigned pgNum = q.front();
      q.pop();
      pageDepths[pgNum - 1] = depth;  // update the depth of the page
      Page currPage = pages[pgNum - 1];
      std::vector<unsigned> choices = currPage.getChoices();
      for (size_t j = 0; j < choices.size(); j++) {
        unsigned neighbor = choices[j];
        // visit all unvisited neighbors
        if (visited.find(neighbor) == visited.end()) {
          q.push(neighbor);
          visited.insert(neighbor);
        }
      }
    }
    depth++;  // increment the depth for each level visited
  }
  for (size_t i = 0; i < pageDepths.size(); i++) {
    std::cout << "Page " << std::dec << i + 1;
    if (pageDepths[i] == -1) {  // depth is not updated, so its unreachable
      std::cout << " is not reachable" << std::endl;
    }
    else {  // print out the page depths
      std::cout << ":" << std::dec << pageDepths[i] << std::endl;
    }
  }
}

/**
 * Verify story by making sure it has a win page and a lose page. Every page
 * must also be referenced, and no references are out of bound.
 */
void verifyStory(const Story & story) {
  bool winPage = false;
  bool losePage = false;
  std::queue<unsigned> q;
  std::set<unsigned> visited;
  const std::vector<Page> pages = story.getPages();
  visited.insert(1);  // page one is garaunteed to be in the story at this stage
  size_t maxPage = pages.size();
  for (size_t i = 0; i < maxPage; i++) {  // loop through all the pages
    Page currPage = pages[i];
    int status = currPage.getStatus();
    if (status == 1) {  // sets when win page is found
      winPage = true;
    }
    if (status == 2) {  // sets when lose page is found
      losePage = true;
    }
    std::vector<unsigned> choices = currPage.getChoices();
    for (size_t i = 0; i < choices.size(); i++) {
      unsigned neighbor = choices[i];
      if (neighbor > maxPage) {  //invalid reference
        throw InvalidStory();
      }
      if (visited.find(neighbor) == visited.end()) {  //not in visited
        visited.insert(neighbor);
      }
    }
  }
  // if no win page or lose page or not all pages referenced, throw exception
  if (!winPage || !losePage || visited.size() != maxPage) {
    throw InvalidStory();
  }
}

/**
 * Read all the pages in the given directory and construct the story object.
 */
Story readPages(const char * dir) {
  int i = 1;
  std::vector<Page> pgs;
  bool fileFound = true;
  while (fileFound) {  // find all consecutive pages starting from page one
    std::stringstream currFile;
    currFile << dir << "/page" << std::dec << i << ".txt";
    std::string temp = currFile.str();
    const char * temp2 = temp.c_str();
    std::ifstream ifs(temp2, std::ifstream::in);
    if (!ifs.is_open()) {
      fileFound = false;
    }
    else {
      pgs.push_back(parsePage(ifs));
      ifs.close();
      i++;
    }
  }
  if (i == 1) {  // page one not found
    throw InvalidStory();
  }
  Story pages(pgs);
  return pages;
}

/**
 * Converts a c string to a unsigned integer
 */
unsigned strToInt(const char * str) {
  if (*str == '-') {
    throw InvalidPage();
  }
  char * endptr = NULL;
  unsigned long pageNum = strtoul(str, &endptr, 10);
  if (pageNum == 0) {  // not a valid page number
    throw InvalidPage();
  }
  if (!(*str != '\0' && *endptr == '\0')) {  // not a valid integer
    throw InvalidPage();
  }
  if (errno == ERANGE) {  // integer overflows
    throw InvalidPage();
  }
  return pageNum;
}

/**
 * Verify that the file name passed in from step 1 is a valid page filename.
 */
void verifyFilename(char * str) {
  std::string dir(str);
  size_t endIdx = dir.rfind(".txt");  // check that the file type is valid
  if (dir.substr(endIdx).compare(".txt") != 0) {
    throw InvalidFilename();
  }
  size_t startIdx = dir.rfind("page", endIdx);  // check that the name is valid
  if (startIdx != 0 && dir[startIdx - 1] != '/') {
    throw InvalidFilename();
  }
  std::string pgNum = dir.substr(startIdx + 4, endIdx - startIdx - 4);
  try {  // check that the page number is valid
    strToInt(pgNum.c_str());
  }
  catch (std::exception & e) {
    throw InvalidFilename();
  }
}

/**
 * Parse the choices in the navigation section. Put the page number and choice
 * text into vectors.
 */
void parseChoices(std::istream & is,
                  std::string & str,
                  std::vector<std::string> & navigationText,
                  std::vector<unsigned> & choices) {
  int step = 1;
  // read the input file until '#' delimiter is found
  while (!is.eof() && str.find("#") == std::string::npos) {
    size_t idx = str.find(":");
    if (idx == std::string::npos) {
      throw InvalidPage();
    }
    std::string page = str.substr(0, idx);
    unsigned pageNum = strToInt(page.c_str());
    choices.push_back(pageNum);  // store the page number
    std::stringstream choice;
    choice << " " << std::dec << step << ". " << str.substr(idx + 1);
    navigationText.push_back(choice.str());  // store the choice text
    step++;
    getline(is, str);
  }
  if (navigationText.size() == 2) {  // invalid format, needs at least one choice
    throw InvalidPage();
  }
}

/**
 * Parse the navigation section preliminarily. Determine if the page is a win
 * page, lose page, or a choice page.
 */
void parseNavigation(std::istream & is,
                     std::vector<std::string> & navigationText,
                     std::vector<unsigned> & choices,
                     int & isLastPage) {
  std::string str;
  getline(is, str);
  if (str.compare("WIN") == 0) {  // win page
    navigationText.push_back("Congratulations! You have won. Hooray!");
    isLastPage = 1;
    getline(is, str);
  }
  else if (str.compare("LOSE") == 0) {  // lose page
    navigationText.push_back("Sorry, you have lost. Better luck next time!");
    isLastPage = 2;
    getline(is, str);
  }
  else {  // choice page
    isLastPage = 0;
    navigationText.push_back("What would you like to do?");
    navigationText.push_back("");
    parseChoices(is, str, navigationText, choices);
  }
  if (str.find("#") != 0) {  // invalid format, needs the '#' delimiter
    throw InvalidPage();
  }
}

/**
 * Parses the input file and construct the page object.
 */
Page parsePage(std::istream & is) {
  int isLastPage;
  std::vector<unsigned> choices;
  std::vector<std::string> navigationText;
  std::vector<std::string> bodyText;
  // parse the navigation section
  parseNavigation(is, navigationText, choices, isLastPage);
  std::string str;
  while (getline(is, str)) {  // parse the story section
    bodyText.push_back(str);
  }
  if (!is.eof()) {
    throw InvalidPage();
  }
  Page pg(navigationText, bodyText, choices, isLastPage);
  return pg;
}
