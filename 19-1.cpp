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

class Scanner;

array<int, 3> subtract(array<int, 3> a, array<int, 3> b) {
  return array<int, 3>{{a[0] - b[0], a[1] - b[1], a[2] - b[2]}};
}

array<int, 3> add(array<int, 3> a, array<int, 3> b) {
  return array<int, 3>{{a[0] + b[0], a[1] + b[1], a[2] + b[2]}};
}

class Map {
  public:
    set<array<int, 3>> points;
    vector<Scanner*> scanners;
    unordered_map<Scanner*, int> names;
    unordered_map<Scanner*, int> transformations;
    unordered_map<Scanner*, array<int, 3>> offsets;



    void consume(Map *b) {
      Scanner* link = nullptr;
      for (Scanner* bScanner : b->scanners) {
        for (Scanner* aScanner : this->scanners) {
          if (aScanner == bScanner) {
            link = aScanner;
            goto foundScanner;
          }
        }
      }
      foundScanner:
      if (link == nullptr) {
        cout << "No link found" << endl;
        throw "No link found";
      }
      if (this->transformations[link] != b->transformations[link]) {
        printf("Different transformations (%d, %d) for this link\n", this->transformations[link], b->transformations[link]);
        throw "Different transformations for this link";
      }

      array<int, 3> totalOffset = subtract(this->offsets[link], b->offsets[link]);
      for (array<int, 3> point : b->points) {
        this->points.insert(add(point, totalOffset));
      }

      for (Scanner *scanner : b->scanners) {
        if (scanner == link) continue;
        this->scanners.push_back(scanner);
        this->names[scanner] = b->names[scanner];
        this->transformations[scanner] = b->transformations[scanner];
        this->offsets[scanner] = add(b->offsets[scanner], totalOffset);
      }
    }

    void print() {
      printf("Map scanners:\n");
      for (Scanner *scanner : this->scanners) {
        printf("  Scanner %d (trans %d) at (%d, %d, %d)\n", this->names[scanner], this->transformations[scanner], this->offsets[scanner][0], this->offsets[scanner][1], this->offsets[scanner][2]);
      }
      printf(" Points (%lu):\n", this->points.size());
      for (array<int, 3> point : this->points) {
        // printf("  (%d, %d, %d)\n", point[0], point[1], point[2]);
      }
    }
};

class Scanner {
  private:
    vector<array<int, 3>> points;
  public:
    int name;
    Scanner(int name) : name(name) {}
    void addPoint(int x, int y, int z) {
      this->points.push_back(array<int, 3>{{x, y, z}});
    }
    vector<array<int, 3>> transform(int xIndex, int yIndex, int zIndex, bool xNegated, bool yNegated, bool zNegated) {
      vector<array<int, 3>> newPoints;
      int xC = xNegated ? -1 : 1;
      int yC = yNegated ? -1 : 1;
      int zC = zNegated ? -1 : 1;
      for (array<int, 3> originalPoint : this->points) {
        newPoints.push_back(
          array<int, 3>{{
            xC*originalPoint[xIndex],
            yC*originalPoint[yIndex],
            zC*originalPoint[zIndex]
          }}
        );
      }
      return newPoints;
    }
    vector<array<int, 3>>* getAllTransformations() {
      vector<array<int, 3>> *transformations = new vector<array<int, 3>>[24];
      // spun around positive Z
      transformations[0] = transform(0, 1, 2, false, false, false);
      transformations[1] = transform(1, 0, 2,  true, false, false);
      transformations[2] = transform(0, 1, 2,  true,  true, false);
      transformations[3] = transform(1, 0, 2, false,  true, false);
      // spun around negative Z
      transformations[4] = transform(1, 0, 2,  true,  true,  true);
      transformations[5] = transform(0, 1, 2, false,  true,  true);
      transformations[6] = transform(1, 0, 2, false, false,  true);
      transformations[7] = transform(0, 1, 2,  true, false,  true);
      // spun around positive X
      transformations[8] = transform(1, 2, 0, false, false, false);
      transformations[9] = transform(2, 1, 0,  true, false, false);
      transformations[10] = transform(1, 2, 0,  true,  true, false);
      transformations[11] = transform(2, 1, 0, false,  true, false);
      // spun around negative X
      transformations[12] = transform(1, 2, 0, false,  true,  true);
      transformations[13] = transform(2, 1, 0, false, false,  true);
      transformations[14] = transform(1, 2, 0,  true, false,  true);
      transformations[15] = transform(2, 1, 0,  true,  true,  true);
      // spun around positive Y
      transformations[16] = transform(2, 0, 1,  true,  true, false);
      transformations[17] = transform(0, 2, 1, false,  true, false);
      transformations[18] = transform(2, 0, 1, false, false, false);
      transformations[19] = transform(0, 2, 1,  true, false, false);
      // spun around negative Y
      transformations[20] = transform(0, 2, 1, false, false,  true);
      transformations[21] = transform(2, 0, 1,  true, false,  true);
      transformations[22] = transform(0, 2, 1,  true,  true,  true);
      transformations[23] = transform(2, 0, 1, false,  true,  true);

      return transformations;
    }

    vector<array<int, 3>> getTransformation(int i) {
      switch (i) {
        case 0: return transform(0, 1, 2, false, false, false);
        case 1: return transform(1, 0, 2,  true, false, false);
        case 2: return transform(0, 1, 2,  true,  true, false);
        case 3: return transform(1, 0, 2, false,  true, false);
        case 4: return transform(1, 0, 2,  true,  true,  true);
        case 5: return transform(0, 1, 2, false,  true,  true);
        case 6: return transform(1, 0, 2, false, false,  true);
        case 7: return transform(0, 1, 2,  true, false,  true);
        case 8: return transform(1, 2, 0, false, false, false);
        case 9: return transform(2, 1, 0,  true, false, false);
        case 10: return transform(1, 2, 0,  true,  true, false);
        case 11: return transform(2, 1, 0, false,  true, false);
        case 12: return transform(1, 2, 0, false,  true,  true);
        case 13: return transform(2, 1, 0, false, false,  true);
        case 14: return transform(1, 2, 0,  true, false,  true);
        case 15: return transform(2, 1, 0,  true,  true,  true);
        case 16: return transform(2, 0, 1,  true,  true, false);
        case 17: return transform(0, 2, 1, false,  true, false);
        case 18: return transform(2, 0, 1, false, false, false);
        case 19: return transform(0, 2, 1,  true, false, false);
        case 20: return transform(0, 2, 1, false, false,  true);
        case 21: return transform(2, 0, 1,  true, false,  true);
        case 22: return transform(0, 2, 1,  true,  true,  true);
        default: return transform(2, 0, 1, false,  true,  true);
      }
    }

    static Map *getOverlap(Scanner *a, int initialTransformation, Scanner *b) {
      vector<array<int, 3>> basisPoints = a->getTransformation(initialTransformation);

      for (int i=0; i < 24; i++) {
        // printf("Testing %d[%d] <-> %d[%d]\n", a->name, initialTransformation, b->name, i);
        vector<array<int, 3>> transformation = b->getTransformation(i);

        unordered_map<int, vector<array<int, 3>>> xOffsets;

        for (array<int, 3> point : transformation) {
          for (array<int, 3> basisPoint : basisPoints) {
            xOffsets[basisPoint[0] - point[0]].push_back(point);
          }
        }

        bool foundXOffset = false;
        int xOffset = 0;

        for (const auto & [key, value] : xOffsets) {
          if (value.size() >= 12) {
            // printf("Found X offset at %d with %d matches\n", key, (int)value.size());
            xOffset = key;
            transformation = value;
            foundXOffset = true;
            break;
          }
        }

        if (!foundXOffset) {
          continue;
        }

        unordered_map<int, vector<array<int, 3>>> yOffsets;

        for (array<int, 3> point : transformation) {
          for (array<int, 3> basisPoint : basisPoints) {
            yOffsets[basisPoint[1] - point[1]].push_back(point);
          }
        }

        bool foundYOffset = false;
        int yOffset = 0;

        for (const auto & [key, value] : yOffsets) {
          if (value.size() >= 12) {
            // printf("Found Y offset at %d with %d matches\n", key, (int)value.size());
            yOffset = key;
            transformation = value;
            foundYOffset = true;
            break;
          }
        }

        if (!foundYOffset) {
          continue;
        }

        unordered_map<int, vector<array<int, 3>>> zOffsets;

        for (array<int, 3> point : transformation) {
          for (array<int, 3> basisPoint : basisPoints) {
            zOffsets[basisPoint[2] - point[2]].push_back(point);
          }
        }

        bool foundZOffset = false;
        int zOffset = 0;

        for (const auto & [key, value] : zOffsets) {
          if (value.size() >= 12) {
            // printf("Found Z offset at %d with %d matches\n", key, (int)value.size());
            zOffset = key;
            transformation = value;
            foundZOffset = true;
            break;
          }
        }

        if (!foundZOffset) {
          continue;
        }

        printf("Scanner b is at (%d,%d,%d) relative to Scanner a\n", xOffset, yOffset, zOffset);

        array<int, 3> offset = array<int, 3>{{xOffset, yOffset, zOffset}};

        Map *map = new Map;
        map->transformations[a] = initialTransformation;
        map->transformations[b] = i;

        map->offsets[a] = {{0,0,0}};
        map->offsets[b] = offset;

        map->scanners.push_back(a);
        map->scanners.push_back(b);

        map->names[a] = a->name;
        map->names[b] = b->name;

        for (array<int, 3> point : basisPoints) {
          map->points.insert(point);
        }

        for (array<int, 3> point : b->getTransformation(i)) {
          // skip dupes
          if (find(transformation.begin(), transformation.end(), point) == transformation.end()) {
            map->points.insert(add(point, offset));
          } else {
            printf("Found dupe point %d(%5d, %5d, %5d)\t%d(%5d, %5d, %5d)\n", a->name, add(point, offset)[0], add(point, offset)[1], add(point, offset)[2], b->name, point[0], point[1], point[2]);
          }
        }

        return map;
      }
      return nullptr;
    }

    int length() {
      return this->points.size();
    }
};

int main(int argc, char **argv) {
  ifstream input("19.txt");
  if (!input.good()) {
    cout << "Could not open file." << endl;
    return 2;
  }

  vector<Scanner*> scanners;

  Scanner *currentScanner = new Scanner(scanners.size());
  scanners.push_back(currentScanner);

  while (!input.eof()) {
    string line;
    getline(input, line);

    if (input.eof()) {
      break;
    }

    if (line[1] == '-') {
      if (currentScanner->length()) {
        currentScanner = new Scanner(scanners.size());
        scanners.push_back(currentScanner);
      }
    } else {
      replace(line.begin(), line.end(), ',', ' ');
      stringstream stream(line);

      int x, y, z;
      if (stream >> x >> y >> z) {
        currentScanner->addPoint(x, y, z);
      }
    }
  }

  Map *overallMap = nullptr;

  set<int> associated;

  while (associated.size() != scanners.size()) {
    tryAgain:
    for (int i = 0; i < scanners.size(); i++) {
      for (int j = 0; j < scanners.size(); j++) {
        if (i == j) continue;
        if (associated.contains(i) && associated.contains(j)) continue;
        // no distinct maps
        if (overallMap != nullptr && !associated.contains(i) && !associated.contains(j)) continue;

        printf("%d <-> %d?\n", i, j);

        Map *m;
        if (overallMap == nullptr) {
          m = Scanner::getOverlap(scanners[i], 0, scanners[j]);
        } else if (associated.contains(i)) {
          m = Scanner::getOverlap(scanners[i], overallMap->transformations[scanners[i]], scanners[j]);
        } else {
          m = Scanner::getOverlap(scanners[j], overallMap->transformations[scanners[j]], scanners[i]);
        }

        if (m != nullptr) {
          try {
            if (overallMap == nullptr) {
              overallMap = m;
            } else {
              overallMap->consume(m);
              delete m;
            }

            cout << "Found association between scanner " << i << " and " << j << endl;
            associated.insert(i);
            associated.insert(j);

            cout << "---NEW MAP---" << endl;
            overallMap->print();
            goto tryAgain;
          } catch (...) {
            cout << "Unable to consume map." << endl;
          }
        }
      }
    }
  }

  // cout << "Total magnitude: " << answer->magnitude() << endl;

  return 0;
}
