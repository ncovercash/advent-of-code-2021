#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char **argv) {
  // if (argc != 2) {
  //   cout << "Please provide the puzzle input as a command-line argument" << endl;
  //   return 1;
  // }

  ifstream input("07.txt");
  if (!input.good()) {
    cout << "Could not open file." << endl;
    return 2;
  }

  string firstLine;
  getline(input, firstLine);

  replace(firstLine.begin(), firstLine.end(), ',', ' ');

  stringstream calledStream(firstLine);

  vector<int> called;

  int calledNum;
  while (calledStream >> calledNum) {
    called.push_back(calledNum);
  }

  vector<int*> boards;
  vector<bool> boardsFinished;

  string line;
  int* curBoard = new int[25];
  int curIndex = 0;

  while (!input.eof()) {
    input >> line;

    if (curIndex == 25) {
      boards.push_back(curBoard);
      boardsFinished.push_back(false);
      curIndex = 0;
      curBoard = new int[25];
    }

    if (input.eof()) {
      break;
    }

    stringstream boardRow(line);

    int cell;
    while (boardRow >> cell) {
      curBoard[curIndex] = cell;
      curIndex++;
    }
  }

  int finishedBoard = 0;
  int finishedCall;

  for (int i=0; i < called.size(); i++) {
    for (int j=0; j < boards.size(); j++) {
      if (boardsFinished[j] == true) {
        continue;
      }
      for (int k=0; k < 25; k++) {
        if (boards[j][k] == called[i]) {
          boards[j][k] = 0;
        }
      }

      // check each row
      for (int k=0; k < 25; k += 5) {
        if (boards[j][k] == 0 && boards[j][k + 1] == 0 && boards[j][k + 2] == 0 && boards[j][k + 3] == 0 && boards[j][k + 4] == 0) {
          boardsFinished[j] = true;
          finishedBoard = j;
          finishedCall = called[i];
        }
      }

      // check each column
      for (int k=0; k < 5; k++) {
        if (boards[j][k] == 0 && boards[j][k + 5] == 0 && boards[j][k + 10] == 0 && boards[j][k + 15] == 0 && boards[j][k + 20] == 0) {
          boardsFinished[j] = true;
          finishedBoard = j;
          finishedCall = called[i];
        }
      }
    }
  }
  foundBoard:
  int sum = 0;
  for (int i = 0; i < 25; i++) {
    sum += boards[finishedBoard][i];
  }

  cout << "Board " << finishedBoard << " had total " << sum << " resulting in multiplied " << sum * finishedCall << endl;


  return 0;
}
