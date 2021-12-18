#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <limits.h>
#include <unordered_map>
#include <set>
#include <stack>
using namespace std;

void ping(vector<vector<int> > &octopi, int i, int j, vector<pair<int, int> > &willFlash) {
  // OOB
  if (i < 0 || j < 0 || i >= octopi.size() || j >= octopi[i].size()) {
    return;
  }
  octopi[i][j]++;
  if (octopi[i][j] > 9) {
    for (pair<int, int> flashing : willFlash) {
      if (flashing.first == i && flashing.second == j) {
        return;
      }
    }
    willFlash.push_back(pair<int, int>(i, j));
    // eight adjacent
    ping(octopi, i - 1, j - 1, willFlash);
    ping(octopi, i - 1,     j, willFlash);
    ping(octopi, i - 1, j + 1, willFlash);
    ping(octopi,     i, j - 1, willFlash);
    ping(octopi,     i, j + 1, willFlash);
    ping(octopi, i + 1, j - 1, willFlash);
    ping(octopi, i + 1,     j, willFlash);
    ping(octopi, i + 1, j + 1, willFlash);
  }
}

int main(int argc, char **argv) {
  // if (argc != 2) {
  //   cout << "Please provide the puzzle input as a command-line argument" << endl;
  //   return 1;
  // }

  ifstream input("11.txt");
  if (!input.good()) {
    cout << "Could not open file." << endl;
    return 2;
  }

  vector<vector<int> > octopi;

  while (!input.eof()) {
    string line;
    input >> line;

    if (input.eof()) {
      break;
    }

    vector<int> lineOctopi;

    for (int i = 0; i < line.length(); i++) {
      lineOctopi.push_back(line[i] - '0');
    }

    octopi.push_back(lineOctopi);
  }

  int flashes = 0;

  for (int step = 0; step < 100; step++) {
    vector<pair<int, int> > willFlash;
    for (int i = 0; i < octopi.size(); i++) {
      for (int j = 0; j < octopi[i].size(); j++) {
        ping(octopi, i, j, willFlash);
      }
    }

    flashes += willFlash.size();

    for (pair<int, int> flashing : willFlash) {
      octopi[flashing.first][flashing.second] = 0;
    }
  }

  cout << "Total flashes: " << flashes << endl;

  return 0;
}
