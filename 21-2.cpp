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
#include <array>
#include <queue>
using namespace std;

#define WIN 21

template <typename T>
class Game {
  public:
    int player1Score;
    int player1Spot;
    int player2Score;
    int player2Spot;
    int nextPlayer = 1;
    Game() {};
    Game(Game *game) : player1Score(game->player1Score), player2Score(game->player2Score), player1Spot(game->player1Spot), player2Spot(game->player2Spot) {};
    Game(int s1, int s2) : player1Score(0), player2Score(0), player1Spot(s1), player2Spot(s2) {};
    void play(int n) {
      if (nextPlayer == 1) {
        player1Spot = (player1Spot - 1 + n) % 10 + 1;
        player1Score += player1Spot;
      } else {
        player2Spot = (player2Spot - 1 + n) % 10 + 1;
        player2Score += player2Spot;
      }

      nextPlayer = nextPlayer == 1 ? 2 : 1;
    }
    unordered_map<Game, long long, T> iterate() const;
    bool keepPlaying() const {
      return player1Score < WIN && player2Score < WIN;
    }
    void p() const {
      printf("%c%d@%d\t%c%d@%d\n", nextPlayer == 1 ? '*' : ' ', player1Score, player1Spot, nextPlayer == 2 ? '*' : ' ', player2Score, player2Spot);
    }
    bool operator== (const Game b) const {
      return this->player1Score == b.player1Score &&
        this->player1Spot == b.player1Spot &&
        this->player2Score == b.player2Score &&
        this->player2Spot == b.player2Spot &&
        this->nextPlayer == b.nextPlayer;
    }
};

class H {
  public:
    size_t operator()(const Game<H> &game) const {
      size_t n = 1;
      size_t prime = 13;

      n = n * prime + game.player1Score;
      n = n * prime + game.player1Spot;
      n = n * prime + game.player2Score;
      n = n * prime + game.player2Spot;
      n = n * prime + game.nextPlayer;

      return n;
    }
};

template <typename T>
unordered_map<Game<T>, long long, T> Game<T>::iterate() const {
  // 1-3 thrice produces following possibilities for totals:
  // 3: 1 times
  // 4: 3 times
  // 5: 6 times
  // 6: 7 times
  // 7: 6 times
  // 8: 3 times
  // 9: 1 times

  pair<int, int> freqs[] = {{3, 1}, {4, 3}, {5, 6}, {6, 7}, {7, 6}, {8, 3}, {9, 1}};

  unordered_map<Game, long long, T> games;

  for (pair<int, int> p : freqs) {
    Game g = *(this);
    g.play(p.first);
    games[g] = p.second;
  }

  return games;
}

int main(int argc, char **argv) {
  ifstream input("21.txt");
  if (!input.good()) {
    cout << "Could not open file." << endl;
    return 2;
  }

  vector<int> players;

  while (!input.eof()) {
    string line;
    getline(input, line);

    if (input.eof()) {
      break;
    }

    players.push_back(stoi(line.substr(28)));
  }


  unordered_map<Game<H>, long long, H> games;
  queue<Game<H>> gameQueue;
  games[Game<H>(players[0], players[1])] = 1;
  gameQueue.push(Game<H>(players[0], players[1]));

  long long p1Wins = 0;
  long long p2Wins = 0;

  while (gameQueue.size()) {
    Game<H> game = gameQueue.front();
    gameQueue.pop();

    if (games[game] == 0) {
      continue;
    } else if (game.keepPlaying()) {
      unordered_map<Game<H>, long long, H> newGames = game.iterate();
      long long num = games[game];
      games[game] = 0;
      for (const auto & [newKey, newValue] : newGames) {
        games[newKey] += num * newValue;
        gameQueue.push(newKey);
      }
    } else if (game.player1Score >= WIN) {
      p1Wins += games[game];
      games[game] = 0;
    } else {
      p2Wins += games[game];
      games[game] = 0;
    }
  }

  cout << "Player 1 wins: " << p1Wins << endl;
  cout << "Player 2 wins: " << p2Wins << endl;

  return 0;
}
