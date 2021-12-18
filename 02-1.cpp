#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char **argv) {
  ifstream input("02.txt");
  if (!input.good()) {
    cout << "Could not open file." << endl;
    return 2;
  }

  int horizontal = 0;
  int depth      = 0;

  string direction;
  int amount;

  while (!input.eof()) {
    input >> direction >> amount;

    if (input.eof()) {
      break;
    }

    if (direction == "forward") {
      horizontal += amount;
    } else if (direction == "up") {
      depth -= amount;
    } else if (direction == "down") {
      depth += amount;
    } else {
      cout << "Invalid direction: " << direction << endl;
    }
  }

  cout << "Horizontal: " << horizontal << endl;
  cout << "Depth: " << depth << endl;
  cout << "Multiplied: " << horizontal * depth << endl;

  return 0;
}
