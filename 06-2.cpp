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
  // if (argc != 2) {
  //   cout << "Please provide the puzzle input as a command-line argument" << endl;
  //   return 1;
  // }

  ifstream input("06.txt");
  if (!input.good()) {
    cout << "Could not open file." << endl;
    return 2;
  }

  long long feesh[9] = {0};

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
      feesh[fish]++;
    }
  }

  for (int t=0; t < 256; t++) {
    cout << "Day " << t << endl;

    cout << "[";
    for (int i = 0; i < 9; i++) {
      cout << feesh[i] << ",";
    }
    cout << "]" << endl;

    // time marches on
    long long newFish = feesh[0];
    feesh[0] = feesh[1];
    feesh[1] = feesh[2];
    feesh[2] = feesh[3];
    feesh[3] = feesh[4];
    feesh[4] = feesh[5];
    feesh[5] = feesh[6];
    feesh[6] = feesh[7] + newFish;
    feesh[7] = feesh[8];
    feesh[8] = newFish;
  }

  long long totalFish = 0;
  for (long long numAge : feesh) {
    totalFish += numAge;
  }

  cout << "Number of fish after 256 days: " << totalFish << endl;

  return 0;
}
