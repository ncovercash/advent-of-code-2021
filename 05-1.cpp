#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <limits.h>
#include <unordered_map>
#include <set>
using namespace std;

class Vent {
  public:
    static int minX, maxX, minY, maxY;

    // static unordered_map<int, vector<Vent*>> horizontals;
    // static unordered_map<int, vector<Vent*>> verticals;

    // bool horizontal, vertical;
    int x1, y1, x2, y2;

    Vent(int x1, int y1, int x2, int y2) {
      if (x1 == x2) {
        // vertical = true;
        this->x1 = this->x2 = x1;
        this->y1 = min(y1, y2);
        this->y2 = max(y1, y2);
      } else if (y1 == y2) {
        // horizontal = true;
        this->y1 = this->y2 = y1;
        this->x1 = min(x1, x2);
        this->x2 = max(x1, x2);
      } else {
        throw "Not horizontal or vertical";
      }

      printf("%d,%d -> %d,%d\n", this->x1, this->y1, this->x2, this->y2);

      // horizontal = this->y1 == this->y2;
      // vertical   = this->x1 == this->x2;

      Vent::minX = min(Vent::minX, x1);
      Vent::maxX = max(Vent::maxX, x2);
      Vent::minY = min(Vent::minY, y1);
      Vent::maxY = max(Vent::maxY, y2);

      // if (horizontal) {
      //   Vent::horizontals.try_emplace(this->y1, vector<Vent*>());
      //   Vent::horizontals[this->y1].push_back(this);
      // } else {
      //   Vent::verticals.try_emplace(this->x1, vector<Vent*>());
      //   Vent::verticals[this->x1].push_back(this);
      // }
    };

    bool overlaps(int x, int y) {
      return (x1 <= x && x <= x2 && y1 <= y && y <= y2);
      // return (vertical && y1 <= y && y <= y2) || (horizontal && x1 <= x && x <= x2);
    }
};

int Vent::minX = INT_MAX;
int Vent::maxX = INT_MIN;
int Vent::minY = INT_MAX;
int Vent::maxY = INT_MIN;

// unordered_map<int, vector<Vent*>> Vent::horizontals;
// unordered_map<int, vector<Vent*>> Vent::verticals;

int main(int argc, char **argv) {
  ifstream input("05.txt");
  if (!input.good()) {
    cout << "Could not open file." << endl;
    return 2;
  }

  vector<Vent*> vents;

  string line;
  int curVent[4];
  int curIndex = 0;

  while (!input.eof()) {
    input >> line;

    if (curIndex == 4) {
      try {
        vents.push_back(new Vent(curVent[0], curVent[1], curVent[2], curVent[3]));
      } catch (...) {}
      curIndex = 0;
    }

    if (input.eof()) {
      break;
    }

    replace(line.begin(), line.end(), ',', ' ');

    stringstream ventStream(line);

    int coordinate;
    while (ventStream >> coordinate) {
      curVent[curIndex] = coordinate;
      curIndex++;
    }
  }

  int numPoints = 0;

  for (int x = Vent::minX; x <= Vent::maxX; x++) {
    for (int y = Vent::minY; y <= Vent::maxY; y++) {
      printf("x: %d/%d, y: %d/%d        \r", x, Vent::maxX, y, Vent::maxY);
      int numOverlaps = 0;
      for (Vent* vent : vents) {
        if (vent->overlaps(x, y)) {
          numOverlaps++;
          if (numOverlaps >= 2) {
            // printf("\n(%d,%d)\n is in (%d,%d -> %d,%d)\n", x, y, vent->x1, vent->y1, vent->x2, vent->y2);

            numPoints++;
            break;
          }
        }
      }
    }
  }

  cout << "Number of points with multiple vents: " << numPoints << endl;

  return 0;
}
