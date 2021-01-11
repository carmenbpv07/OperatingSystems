#include <iostream>
#include <thread>
#include <vector>

using namespace std;

/** Chapter 4: Threads & Concurrency
    Programming Projects P-25
    Project 1 — Sudoku Solution Validator
    To compile: g++ -std=c++11 sudoku.cpp -o sudoku -pthread
    To execute: ./sudoku
**/

vector<vector<int>> sudoku(9, vector<int>(9));
vector<bool> results(3, 1);

void row_checker() {
  for (int i = 0; i < 9; i++) {
    vector<bool> checker(11);
    for (int j = 0; j < 9; j++) {
      if (checker[sudoku[i][j]] == 0) {
        checker[sudoku[i][j]] = 1;
      } else {
        results[0] = 0;
        return;
      }
    }
  }
}

void column_checker() {
  for (int i = 0; i < 9; i++) {
    vector<bool> checker(10);
    for (int j = 0; j < 9; j++) {
      if (checker[sudoku[j][i]] == 0) {
        checker[sudoku[j][i]] = 1;
      } else {
        results[1] = 0;
        return;
      }
    }
  }
}

void grid_checker(int x, int y) {
  vector<int> checker(10);
  for (int i = x; i < x + 3; i++) {
    for (int j = y; j < y + 3; j++) {
      if (checker[sudoku[i][j]] == 0) {
        checker[sudoku[i][j]] = 1;
      } else {
        results[2] = 0;
        return;
      }
    }
  }
}

bool sudoku_validator() {
  for (int i = 0; i < 3; i++) {
    if (results[i] == 0) {
      return 0;
    }
  }
  return 1;
}

int main() {
  sudoku = {
    {6, 2, 4, 5, 3, 9, 1, 8, 7},
    {5, 1, 9, 7, 2, 8, 6, 3, 4},
    {8, 3, 7, 6, 1, 4, 2, 9, 5},
    {1, 4, 3, 8, 6, 5, 7, 2, 9},
    {9, 5, 8, 2, 4, 7, 3, 6, 1},
    {7, 6, 2, 3, 9, 1, 4, 5, 8},
    {3, 7, 1, 9, 5, 6, 8, 4, 2},
    {4, 9, 6, 1, 8, 2, 5, 7, 3},
    {2, 8, 5, 4, 7, 3, 9, 1, 6}
  };

  thread row_validator(row_checker);
  thread column_validator(column_checker);
  thread grids[9];
  int t = 0;
  for (int i = 0; i <= 6; i += 3) {
    for (int j = 0; j <= 6; j += 3) {
      grids[t] = thread(grid_checker, i, j);
      t++;
    }
  }
  for (int i = 0; i < 9; i++) {
    grids[i].join();
  }
  row_validator.join();
  column_validator.join();
  if (sudoku_validator()) {
    cout << "Sudoku solution is valid\n";
  } else {
    cout << "Sudoku solution is invalid\n";
  }

  return 0;
}