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

  int score = 0;

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
            score += 57;
            goto readNextLine;
          }
          bracketStack.pop();
          break;
        case '}':
          if (bracketStack.empty() || bracketStack.top() != '{') {
            score += 1197;
            goto readNextLine;
          }
          bracketStack.pop();
          break;
        case ')':
          if (bracketStack.empty() || bracketStack.top() != '(') {
            score += 3;
            goto readNextLine;
          }
          bracketStack.pop();
          break;
        case '>':
          if (bracketStack.empty() || bracketStack.top() != '<') {
            score += 25137;
            goto readNextLine;
          }
          bracketStack.pop();
          break;
      }
    }
  }

  cout << "Total score: " << score << endl;

  return 0;
}
