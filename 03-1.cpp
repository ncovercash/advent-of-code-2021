#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main(int argc, char **argv) {
  ifstream input("03.txt");
  if (!input.good()) {
    cout << "Could not open file." << endl;
    return 2;
  }

  vector<int> numZeroes;
  vector<int> numOnes;

  string line;

  while (!input.eof()) {
    input >> line;

    if (input.eof()) {
      break;
    }

    while (numZeroes.size() < line.length()) {
      numZeroes.push_back(0);
      numOnes.push_back(0);
    }

    for (int i=0; i < line.length(); i++) {
      if (line[i] == '0') {
        numZeroes[i]++;
      } else if (line[i] == '1') {
        numOnes[i]++;
      }
    }
  }

  int gamma   = 0;
  int epsilon = 0;

  for (int i=0; i < numZeroes.size(); i++) {
    gamma   <<= 1;
    epsilon <<= 1;
    if (numOnes[i] > numZeroes[i]) {
      cout << 1;
      gamma |= 0x1;
    } else {
      cout << 0;
      epsilon |= 0x1;
    }
  }

  cout << "Gamma: " << gamma << endl;
  cout << "Epsilon: " << epsilon << endl;
  cout << "Multiplied: " << gamma * epsilon << endl;

  return 0;
}
