#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <ctype.h>
#include <math.h>
#include <algorithm>
#include <limits.h>
#include <unordered_map>
#include <set>
#include <stack>
#include <array>
using namespace std;

set<array<int, 2>> foldX(int x, set<array<int, 2>> points) {
  set<array<int, 2>> newPoints;
  for (array<int, 2> point : points) {
    newPoints.insert(array<int, 2>{{x - abs(x - point[0]), point[1]}});
  }
  return newPoints;
}

set<array<int, 2>> foldY(int y, set<array<int, 2>> points) {
  set<array<int, 2>> newPoints;
  for (array<int, 2> point : points) {
    newPoints.insert(array<int, 2>{{point[0], y - abs(y - point[1])}});
  }
  return newPoints;
}

int main(int argc, char **argv) {
  ifstream input("13.txt");
  if (!input.good()) {
    cout << "Could not open file." << endl;
    return 2;
  }

  set<array<int, 2>> points;

  while (!input.eof()) {
    string line;
    getline(input, line);

    if (input.eof()) {
      break;
    }

    if (isdigit(line[0])) {
      replace(line.begin(), line.end(), ',', ' ');
      stringstream stream(line);

      int x, y;
      if (stream >> x >> y) {
        points.insert(array<int, 2>{{x, y}});
      }
    } else if (line[0] == 'f') {
      int coordinate = stoi(line.substr(13));
      if (line[11] == 'x') {
        points = foldX(coordinate, points);
      } else {
        points = foldY(coordinate, points);
      }
      break; // just do first
    }
  }

  cout << "Total number of points: " << points.size() << endl;

  return 0;
}
