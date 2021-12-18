#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <limits.h>
#include <unordered_map>
#include <set>
using namespace std;

int main(int argc, char **argv) {
  ifstream input("06.txt");
  if (!input.good()) {
    cout << "Could not open file." << endl;
    return 2;
  }

  vector<int> feesh;

  string line;

  while (!input.eof()) {
    input >> line;

    if (input.eof()) {
      break;
    }

    replace(line.begin(), line.end(), ',', ' ');

    stringstream school(line);

    int fish;
    while (school >> fish) {
      feesh.push_back(fish);
    }
  }

  for (int t=0; t < 256; t++) {
    // reverse to avoid processing new fish
    for (int i = feesh.size()-1; i >= 0; i--) {
      if (feesh[i] == 0) {
        feesh[i] += 7;
        feesh.push_back(8);
      }
      feesh[i]--;
    }
  }

  cout << "Number of fish after 80 days: " << feesh.size() << endl;

  return 0;
}
