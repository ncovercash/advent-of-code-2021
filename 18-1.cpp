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
using namespace std;

class Number {
  private:
    Number *parent = nullptr;
    Number *left   = nullptr;
    Number *right  = nullptr;
    int normalValue = -1;

  public:
    Number(Number *parent, int normalValue) : parent(parent), normalValue(normalValue) {};
    Number(Number *parent, Number *left, Number *right) : parent(parent), left(left), right(right) {
      left->parent = this;
      right->parent = this;
    };
    Number(Number *parent, string internals) : parent(parent) {
      // cout << "Creating Number(" << internals << ")" << endl;
      if (internals.length() > 1) {
        int level = 0;
        int commaIndex = -1;
        for (int i = 0; i < internals.length(); i++) {
          if (internals[i] == '[') {
            level++;
          } else if (internals[i] == ']') {
            level--;
          } else if (level == 1 && internals[i] == ',') {
            commaIndex = i;
            break;
          }
        }
        this->left  = new Number(this, internals.substr(1, commaIndex - 1));
        this->right = new Number(this, internals.substr(commaIndex + 1, internals.size() - commaIndex - 2));
      } else {
        this->normalValue = stoi(internals);
      }
    }

    bool isNumber() const {
      return this->normalValue != -1;
    }

    bool isPair() const {
      return this->normalValue == -1;
    }

    bool isNormalPair() const {
      return this->isPair() && this->left->isNumber() && this->right->isNumber();
    }

    void addToLeftmost(int num) {
      if (num == 0) return;
      if (this->isNumber()) {
        this->normalValue += num;
      } else {
        this->left->addToLeftmost(num);
      }
    }

    void addToRightmost(int num) {
      if (num == 0) return;
      if (this->isNumber()) {
        this->normalValue += num;
      } else {
        this->right->addToRightmost(num);
      }
    }

    void reduce() {
      pair<int, int> exploded = this->checkExplosions(1);
      if (exploded.first != -1 || exploded.second != -1) {
        cout << "Exploded into: " << *this << endl;
        this->reduce();
        return;
      }
      if (this->split()) {
        cout << "Split into: " << *this << endl;
        this->reduce();
        return;
      }
    }

    bool split() {
      if (this->normalValue >= 10) {
        this->left        = new Number(this, floor(this->normalValue / 2.0));
        this->right       = new Number(this, ceil(this->normalValue / 2.0));
        this->normalValue = -1;
        return true;
      } else if (this->isNumber()) {
        return false;
      } else {
        return this->left->split() || this->right->split();
      }
    }

    pair<int, int> checkExplosions(int level) {
      // cout << "Checking explosions on L" << level << ": " << *this << endl;
      if (this->isNumber()) return pair<int, int>(-1, -1);

      pair<int, int> leftPair = pair<int, int>(-1, -1);
      if (level >= 4 && this->left->isNormalPair()) {
        leftPair = pair<int, int>(this->left->left->normalValue, this->left->right->normalValue);
        delete this->left;
        this->left = new Number(this, 0);
      } else {
        leftPair = this->left->checkExplosions(level + 1);
      }

      if (leftPair.first != -1 || leftPair.second != -1) {
        this->right->addToLeftmost(leftPair.second);
        leftPair.second = 0;

        return leftPair;
      }

      pair<int, int> rightPair = pair<int, int>(-1, -1);
      if (level >= 4 && this->right->isNormalPair()) {
        rightPair = pair<int, int>(this->right->left->normalValue, this->right->right->normalValue);
        delete this->right;
        this->right = new Number(this, 0);
      } else {
        rightPair = this->right->checkExplosions(level + 1);
      }

      if (rightPair.first != -1 || rightPair.second != -1) {
        this->left->addToRightmost(rightPair.first);
        rightPair.first = 0;

        return rightPair;
      }

      return leftPair; // must still be <-1, -1>
    }

    int magnitude() {
      if (this->isNumber()) {
        return this->normalValue;
      }
      return 3 * this->left->magnitude() + 2 * this->right->magnitude();
    }

    static Number* add(Number *a, Number *b) {
      Number *result = new Number(nullptr, a, b);
      cout << "Reducing: " << *result << endl;
      result->reduce();
      return result;
    }

    friend ostream& operator<<(ostream& os, const Number& num);
};

ostream& operator<<(ostream& os, const Number& num) {
  if (num.isPair()) {
    os << '[' << *(num.left) << ',' << *(num.right) << ']';
  } else {
    os << num.normalValue;
  }
  return os;
}

int main(int argc, char **argv) {
  // if (argc != 2) {
  //   cout << "Please provide the puzzle input as a command-line argument" << endl;
  //   return 1;
  // }

  ifstream input("18.txt");
  if (!input.good()) {
    cout << "Could not open file." << endl;
    return 2;
  }

  Number *answer = nullptr;

  while (!input.eof()) {
    string line;
    input >> line;

    if (input.eof()) {
      break;
    }

    Number *newNumber = new Number(nullptr, line);
    if (answer == nullptr) {
      answer = newNumber;
    } else {
      answer = Number::add(answer, newNumber);
    }
  }

  cout << "Total magnitude: " << answer->magnitude() << endl;

  return 0;
}
