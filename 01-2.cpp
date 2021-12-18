#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char **argv) {
  if (argc != 2) {
    cout << "Please provide the puzzle input as a command-line argument" << endl;
    return 1;
  }

  ifstream input(argv[1]);
  if (!input.good()) {
    cout << "Could not open file." << endl;
    return 2;
  }

  int lastLastLastInput = -1; // can assume positive based on problem
  int lastLastInput     = -1; // can assume positive based on problem
  int lastInput         = -1; // can assume positive based on problem
  int currInput;
  int numIncreases = 0;

  while (!input.eof()) {
    input >> currInput;

    if (input.eof()) {
      break;
    }

    // first two readings do not count
    if (lastLastLastInput < 0) {
      lastLastLastInput = lastLastInput;
      lastLastInput     = lastInput;
      lastInput         = currInput;
      continue;
    }

    int lastTotal = lastLastLastInput + lastLastInput + lastInput;
    int currTotal = lastLastInput + lastInput + currInput;

    if (currTotal > lastTotal) {
      numIncreases++;
    }

    lastLastLastInput = lastLastInput;
    lastLastInput     = lastInput;
    lastInput         = currInput;
  }

  cout << numIncreases << endl;

  return 0;
}
