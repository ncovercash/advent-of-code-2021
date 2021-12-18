#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <ctype.h>
#include <algorithm>
#include <limits.h>
#include <unordered_map>
#include <set>
#include <stack>
using namespace std;

bool isLowercase(string in) {
  if (in == "end" || in == "start") return false;
  for (char c : in) {
    if (!islower(c)) {
      // cout << c << " is not lowercase" << endl;
      return false;
    }
  }
  return true;
}

void traverse(string key, bool hasTwice, const unordered_map<string, vector<string> > adjacencyLists, set<string> little, vector<string> curPath, set<vector<string> > &paths) {
  curPath.push_back(key);
  // cout << "Visited " << key << endl;

  if (key == "end") {
    bool printedFirst = false;
    for (string point : curPath) {
      cout << (printedFirst ? "->" : "") << point;
      printedFirst = true;
    }
    cout << endl;
    paths.insert(curPath);
    return;
  }

  vector<string> candidates = adjacencyLists.at(key);

  if (isLowercase(key)) {
    little = set<string>(little);
    little.insert(key);
  }

  for (string candidate : candidates) {
    bool hasTwiceThisTime = false;
    if (candidate == "start") {
      continue;
    }
    if (isLowercase(candidate) && little.contains(candidate)) {
      if (hasTwice) {
        continue;
      } else {
        hasTwiceThisTime = true;
      }
    }
    // // check for duplication
    // bool hasBeenHere = false;
    // for (int i = 0; i < curPath.size() - 1; i++) {
    //   if (curPath[i] == key && curPath[i+1] == candidate) {
    //     hasBeenHere = true;
    //     break;
    //   }
    // }
    // if (hasBeenHere) {
    //   continue;
    // }

    traverse(candidate, hasTwiceThisTime || hasTwice, adjacencyLists, set<string>(little), vector<string>(curPath), paths);
  }

  // cout << "Left " << key << endl;
}

int main(int argc, char **argv) {
  ifstream input("12.txt");
  if (!input.good()) {
    cout << "Could not open file." << endl;
    return 2;
  }

  // set<string> keys;
  unordered_map<string, vector<string> > adjacencyLists;

  while (!input.eof()) {
    string line;
    input >> line;

    if (input.eof()) {
      break;
    }

    replace(line.begin(), line.end(), '-', ' ');

    stringstream path(line);
    string first, second;
    path >> first;
    path >> second;

    // keys.insert(first);
    // keys.insert(second);
    adjacencyLists[first].push_back(second);
    adjacencyLists[second].push_back(first);
  }

  set<vector<string> > paths;

  traverse("start", false, adjacencyLists, set<string>(), vector<string>(), paths);

  cout << "There were " << paths.size() << " paths" << endl;

  for (vector<string> curPath : paths) {
    bool printedFirst = false;
    for (string point : curPath) {
      cout << (printedFirst ? "," : "") << point;
      printedFirst = true;
    }
    cout << endl;
  }

  return 0;
}
