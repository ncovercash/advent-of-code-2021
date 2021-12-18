#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <limits.h>
#include <unordered_map>
#include <set>
#include <stack>
using namespace std;

int main(int argc, char **argv) {
  // if (argc != 2) {
  //   cout << "Please provide the puzzle input as a command-line argument" << endl;
  //   return 1;
  // }

  ifstream input("10.txt");
  if (!input.good()) {
    cout << "Could not open file." << endl;
    return 2;
  }

  vector<long long> scores;

  readNextLine:
  while (!input.eof()) {
    string line;
    input >> line;

    if (input.eof()) {
      break;
    }

    stack<char> bracketStack;

    for (int i = 0; i < line.length(); i++) {
      switch (line[i]) {
        case '[':
        case '(':
        case '{':
        case '<':
          bracketStack.push(line[i]);
          break;
        case ']':
          if (bracketStack.empty() || bracketStack.top() != '[') {
            goto readNextLine;
          }
          bracketStack.pop();
          break;
        case '}':
          if (bracketStack.empty() || bracketStack.top() != '{') {
            goto readNextLine;
          }
          bracketStack.pop();
          break;
        case ')':
          if (bracketStack.empty() || bracketStack.top() != '(') {
            goto readNextLine;
          }
          bracketStack.pop();
          break;
        case '>':
          if (bracketStack.empty() || bracketStack.top() != '<') {
            goto readNextLine;
          }
          bracketStack.pop();
          break;
      }
    }
    // valid
    if (bracketStack.empty()) {
      goto readNextLine;
    }
    long long lineScore = 0;
    while (!bracketStack.empty()) {
      switch (bracketStack.top()) {
        case '(': lineScore = 5*lineScore + 1; break;
        case '[': lineScore = 5*lineScore + 2; break;
        case '{': lineScore = 5*lineScore + 3; break;
        case '<': lineScore = 5*lineScore + 4; break;
      }
      bracketStack.pop();
    }
    cout << line << ": " << lineScore << endl;

    scores.push_back(lineScore);
  }

  sort(scores.begin(), scores.end());

  cout << "Median score: " << scores[scores.size()/2] << endl;

  return 0;
}
