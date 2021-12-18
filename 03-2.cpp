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

  vector<string> lines;

  string line;

  while (!input.eof()) {
    input >> line;

    if (input.eof()) {
      break;
    }

    lines.push_back(line);

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

  vector<string> binaryOxygen = lines;
  vector<int> numZeroesOxygen = numZeroes;
  vector<int> numOnesOxygen   = numOnes;
  int currentIndex = 0;

  while (binaryOxygen.size() > 1) {
    vector<string> passing;

    char search;
    if (numZeroesOxygen[currentIndex] > numOnesOxygen[currentIndex]) {
      search = '0';
    } else {
      search = '1';
    }

    for (int i=0; i < numZeroesOxygen.size(); i++) {
      numZeroesOxygen[i] = 0;
      numOnesOxygen[i] = 0;
    }

    for (int i=0; i < binaryOxygen.size(); i++) {
      if (binaryOxygen[i][currentIndex] == search) {
        passing.push_back(binaryOxygen[i]);

        for (int j=0; j < line.length(); j++) {
          if (binaryOxygen[i][j] == '0') {
            numZeroesOxygen[j]++;
          } else if (binaryOxygen[i][j] == '1') {
            numOnesOxygen[j]++;
          }
        }
      }
    }

    binaryOxygen = passing;
    currentIndex++;
  }

  cout << "Oxygen: " << stoi(binaryOxygen[0], nullptr, 2) << endl;

  vector<string> binaryCO2 = lines;
  vector<int> numZeroesCO2 = numZeroes;
  vector<int> numOnesCO2   = numOnes;
  currentIndex = 0;

  while (binaryCO2.size() > 1) {
    vector<string> passing;

    char search;
    if (numZeroesCO2[currentIndex] > numOnesCO2[currentIndex]) {
      search = '1';
    } else {
      search = '0';
    }

    for (int i=0; i < numZeroesCO2.size(); i++) {
      numZeroesCO2[i] = 0;
      numOnesCO2[i] = 0;
    }

    for (int i=0; i < binaryCO2.size(); i++) {
      if (binaryCO2[i][currentIndex] == search) {
        passing.push_back(binaryCO2[i]);

        for (int j=0; j < line.length(); j++) {
          if (binaryCO2[i][j] == '0') {
            numZeroesCO2[j]++;
          } else if (binaryCO2[i][j] == '1') {
            numOnesCO2[j]++;
          }
        }
      }
    }

    binaryCO2 = passing;
    currentIndex++;
  }

  cout << "CO2: " << stoi(binaryCO2[0], nullptr, 2) << endl;

  cout << "Multiplied: " << stoi(binaryOxygen[0], nullptr, 2)*stoi(binaryCO2[0], nullptr, 2) << endl;

  return 0;
}
