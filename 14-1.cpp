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

int main(int argc, char **argv) {
  ifstream input("14.txt");
  if (!input.good()) {
    cout << "Could not open file." << endl;
    return 2;
  }

  unordered_map<string, string> rules;
  string polymer;

  input >> polymer;

  while (!input.eof()) {
    string line;
    getline(input, line);

    if (input.eof()) {
      break;
    }

    stringstream stream(line);
    string a, arrow, b;
    if (stream >> a >> arrow >> b) {
      rules[a] = b;
    }
  }

  for (int step=1; step <= 10; step++) {
    string newPolymer = "";
    for (int i=0; i < polymer.size(); i++) {
      newPolymer += polymer[i];
      if (i != polymer.size()-1) {
        newPolymer += rules[polymer.substr(i, 2)];
      }
    }
    cout << "After step " << step << ": " << newPolymer << endl;
    polymer = newPolymer;
  }

  int frequencies[26] = {0};
  for (char c : polymer) {
    frequencies[(int)c - 'A']++;
  }

  int maxFreq = frequencies[0];
  int minFreq = frequencies[0];

  for (int i=1; i < 26; i++) {
    printf("min=%4d, max=%4d, %d: %d\n", minFreq, maxFreq, i, frequencies[i]);
    if (minFreq == 0) minFreq = frequencies[i];
    maxFreq = max(maxFreq, frequencies[i]);
    if (frequencies[i] != 0) minFreq = min(minFreq, frequencies[i]);
  }

  cout << "Max: " << maxFreq << endl;
  cout << "Min: " << minFreq << endl;
  cout << "Diff: " << maxFreq-minFreq << endl;

  return 0;
}
