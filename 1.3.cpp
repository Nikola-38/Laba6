#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

// Функция для реализации клеточного автомата Джона Конвея
void gameOfLife(vector<vector<int>>& grid, int generations) {
    int rows = grid.size();
    int cols = grid[0].size();

    vector<vector<int>> nextGrid(rows, vector<int>(cols, 0));

    for (int gen = 0; gen < generations; gen++) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                int liveNeighbors = 0;
                for (int di = -1; di <= 1; di++) {
                    for (int dj = -1; dj <= 1; dj++) {
                        if (di == 0 && dj == 0) {
                            continue;
                        }
                        int x = i + di;
                        int y = j + dj;
                        if (x >= 0 && x < rows && y >= 0 && y < cols && grid[x][y] == 1) {
                            liveNeighbors++;
                        }
                    }
                }
                if (grid[i][j] == 1) {
                    if (liveNeighbors < 2 || liveNeighbors > 3) {
                        nextGrid[i][j] = 0;
                    } else {
                        nextGrid[i][j] = 1;
                    }
                } else {
                    if (liveNeighbors == 3) {
                        nextGrid[i][j] = 1;
                    }
                }
            }
        }
        grid = nextGrid;
        nextGrid = vector<vector<int>>(rows, vector<int>(cols, 0));
        system("cls");
        for (const auto& row : grid) {
            for (int cell : row) {
                cout << cell << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
}

int main() {
    system("CHCP 65001");
    srand(static_cast<unsigned int>(time(nullptr)));

    cout << "Задача 3:" << endl;
    int rows = 20, cols = 30;
    vector<vector<int>> gameGrid(rows, vector<int>(cols, 0));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            gameGrid[i][j] = rand() % 2;
        }
    }
    gameOfLife(gameGrid, 100);

    return 0;
}


