#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void sortLines(istream & f) {
  string str;
  vector<string> lines;
  while (getline(f, str)) {
    lines.push_back(str);
  }
  if (!f.eof()) {
    cerr << "An error occured reading a line!\n" << endl;
    exit(EXIT_FAILURE);
  }
  sort(lines.begin(), lines.end());
  vector<string>::iterator it = lines.begin();
  while (it < lines.end()) {
    cout << *it << endl;
    ++it;
  }
}

int main(int argc, char ** argv) {
  if (argc == 1) {
    sortLines(cin);
  }
  if (argc > 1) {
    for (int i = 1; i < argc; i++) {
      ifstream f(argv[i], ifstream::in);
      if (!f.is_open()) {
        cerr << "Unable to open the file!\n" << endl;
        return EXIT_FAILURE;
      }
      sortLines(f);
    }
  }
  return EXIT_SUCCESS;
}
