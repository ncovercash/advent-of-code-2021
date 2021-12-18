#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <limits.h>
#include <unordered_map>
#include <set>
using namespace std;

int getTotalDistanceFromPoint(vector<int> crabs, int point) {
  int total = 0;
  for (int crab: crabs) {
    int n = abs(crab - point);
    total += n*(n + 1) / 2;
  }
  return total;
}

int main(int argc, char **argv) {
  // if (argc != 2) {
  //   cout << "Please provide the puzzle input as a command-line argument" << endl;
  //   return 1;
  // }

  ifstream input("07.txt");
  if (!input.good()) {
    cout << "Could not open file." << endl;
    return 2;
  }

  vector<int> crabs;
  int minPos, maxPos;

  string line;

  while (!input.eof()) {
    input >> line;

    if (input.eof()) {
      break;
    }

    replace(line.begin(), line.end(), ',', ' ');

    stringstream list(line);

    int crab;
    while (list >> crab) {
      if (crabs.size() == 0) {
        minPos = maxPos = crab;
      }
      crabs.push_back(crab);
      minPos = min(crab, minPos);
      maxPos = max(crab, maxPos);
    }
  }

  // binary search but slopes
  while (minPos < maxPos) {
    int mid = (minPos + maxPos) / 2;

    int leftFuel  = getTotalDistanceFromPoint(crabs, mid - 1);
    int midFuel   = getTotalDistanceFromPoint(crabs, mid);
    int rightFuel = getTotalDistanceFromPoint(crabs, mid + 1);

    if (midFuel <= leftFuel && midFuel <= rightFuel) {
      minPos = maxPos = mid;
    } else if (leftFuel > midFuel) {
      minPos = mid;
    } else {
      maxPos = mid;
    }
  }

  cout << "Best position " << minPos << " takes " << getTotalDistanceFromPoint(crabs, minPos) << endl;

  return 0;
}
