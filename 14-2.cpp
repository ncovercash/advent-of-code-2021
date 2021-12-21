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
#include <list>
#include <stack>
#include <array>
using namespace std;

int main(int argc, char **argv) {
  ifstream input("14.txt");
  if (!input.good()) {
    cout << "Could not open file." << endl;
    return 2;
  }

  unordered_map<string, char> rules;
  unordered_map<string, long long> pairs;

  string str;
  input >> str;
  for (int i=0; i < str.length() - 1; i++) {
    pairs[str.substr(i, 2)]++;
  }

  while (!input.eof()) {
    string line;
    getline(input, line);

    if (input.eof()) {
      break;
    }

    stringstream stream(line);
    string a, arrow, b;
    if (stream >> a >> arrow >> b) {
      rules[a] = b[0];
    }
  }

  for (int step=1; step <= 40; step++) {
    unordered_map<string, long long> newPairs;
    for (pair<string, long long> pair : pairs) {
      if (rules[pair.first] != '\0') {
        string pair1 = pair.first;
        pair1[1] = rules[pair.first];
        string pair2 = pair.first;
        pair2[0] = rules[pair.first];

        newPairs[pair1] += pair.second;
        newPairs[pair2] += pair.second;
      } else {
        newPairs[pair.first] += pair.second;
      }
    }
    pairs = newPairs;
    cout << "Step " << step << " complete" << endl;
  }

  long long frequencies[27] = {0};
  for (pair<string, long long> pair : pairs) {
    // frequencies[(int)pair.first[0] - 'A'] += pair.second;
    // add just seconds of each pair
    frequencies[(int)pair.first[1] - 'A'] += pair.second;
  }
  // frequencies[(int)str[0] - 'A'] += 1; // first char never changes

  long long maxFreq = frequencies[0];
  long long minFreq = frequencies[0];

  for (int i=1; i < 26; i++) {
    printf("min=%4lld, max=%4lld, %d: %lld\n", minFreq, maxFreq, i, frequencies[i]);
    if (minFreq == 0) minFreq = frequencies[i];
    maxFreq = max(maxFreq, frequencies[i]);
    if (frequencies[i] != 0) minFreq = min(minFreq, frequencies[i]);
  }

  cout << "Max: " << maxFreq << endl;
  cout << "Min: " << minFreq << endl;
  cout << "Diff: " << maxFreq-minFreq << endl;

  return 0;
}
