#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <limits.h>
#include <unordered_map>
#include <set>
using namespace std;

bool isLow(int r, int c, int lineLength, vector<int*> map) {
  int point = map[r][c];
  // printf("Checking row %d col %d=%d\n", r, c, point);
  if (r != 0 && map[r-1][c] <= point) {
    return false;
  }
  if (c != 0 && map[r][c-1] <= point) {
    return false;
  }
  if (r != map.size() - 1 && map[r+1][c] <= point) {
    return false;
  }
  if (c != lineLength - 1 && map[r][c+1] <= point) {
    return false;
  }
  return true;
}

int main(int argc, char **argv) {
  ifstream input("09.txt");
  if (!input.good()) {
    cout << "Could not open file." << endl;
    return 2;
  }

  vector<int*> points;
  int lineLength = 0;

  string line;

  while (!input.eof()) {
    input >> line;

    if (input.eof()) {
      break;
    }

    int *linePoints = new int[line.length()];
    lineLength = line.length();

    for (int i = 0; i < line.length(); i++) {
      linePoints[i] = line[i] - '0';
    }

    points.push_back(linePoints);
  }

  int totalRisk = 0;

  for (int r=0; r < points.size(); r++) {
    for (int c=0; c < lineLength; c++) {
      if (isLow(r, c, lineLength, points)) {
        cout << "[" << points[r][c] << "]";
        totalRisk += points[r][c] + 1;
      } else {
        cout << " " << points[r][c] << " ";
      }
    }
    cout << endl;
  }

  cout << "Total risk: " << totalRisk << endl;

  return 0;
}
