#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char **argv) {
  ifstream input("01.txt");
  if (!input.good()) {
    cout << "Could not open file." << endl;
    return 2;
  }

  int lastInput = -1; // can assume positive based on problem
  int currInput;
  int numIncreases = 0;

  while (!input.eof()) {
    input >> currInput;

    if (input.eof()) {
      break;
    }

    // first reading does not count
    if (lastInput < 0) {
      lastInput = currInput;
      continue;
    }

    if (currInput > lastInput) {
      numIncreases++;
    }

    lastInput = currInput;
  }

  cout << numIncreases << endl;

  return 0;
}
