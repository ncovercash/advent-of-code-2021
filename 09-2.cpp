#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <limits.h>
#include <unordered_map>
#include <unordered_set>
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

void addAdjacents(pair<int, int> point, int lineLength, vector<int*> map, vector<pair<int,int>> &pointsToInvestigate);
class H {
  public:
  size_t operator()(const pair<const int, const int> &pair) const {
    int x = pair.first;
    int y = pair.second;
    return x >= y ? x * x + x + y : y * y + x;
  }
};
int getBasinSize(int r, int c, int lineLength, vector<int*> map) {
  unordered_set<pair<int, int>, H> realPoints;
  vector<pair<int, int>> pointsToInvestigate;
  pointsToInvestigate.push_back(pair<int,int>(r,c));

  for (int i=0; i < pointsToInvestigate.size(); i++) {
    if (realPoints.contains(pointsToInvestigate[i])) {
      continue;
    }
    realPoints.insert(pointsToInvestigate[i]);
    addAdjacents(pointsToInvestigate[i], lineLength, map, pointsToInvestigate);
  }

  return realPoints.size();
}

bool inBasin(int r, int c, int lineLength, vector<int*> &map) {
  if (r < 0 || c < 0 || c >= lineLength || r >= map.size()) return false;
  if (map[r][c] == 9) return false;
  return true;
}

void addAdjacents(pair<int, int> point, int lineLength, vector<int*> map, vector<pair<int,int>> &pointsToInvestigate) {
  int r = point.first;
  int c = point.second;
  if (inBasin(r + 1,     c, lineLength, map)) pointsToInvestigate.push_back(pair<int, int>(r + 1,     c));
  if (inBasin(    r, c + 1, lineLength, map)) pointsToInvestigate.push_back(pair<int, int>(    r, c + 1));
  if (inBasin(r - 1,     c, lineLength, map)) pointsToInvestigate.push_back(pair<int, int>(r - 1,     c));
  if (inBasin(    r, c - 1, lineLength, map)) pointsToInvestigate.push_back(pair<int, int>(    r, c - 1));
}

int main(int argc, char **argv) {
  // if (argc != 2) {
  //   cout << "Please provide the puzzle input as a command-line argument" << endl;
  //   return 1;
  // }

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

  vector<int> basins;

  for (int r=0; r < points.size(); r++) {
    for (int c=0; c < lineLength; c++) {
      if (isLow(r, c, lineLength, points)) {
        basins.push_back(getBasinSize(r, c, lineLength, points));
      }
    }
  }

  sort(basins.begin(), basins.end());
  int last = basins.size() - 3;
  int product = basins[last] * basins[last + 1] * basins[last + 2];

  cout << "Total product of basin sizes: " << product << endl;

  return 0;
}
