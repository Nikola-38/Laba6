#include <iostream>
#include <vector>
#include <iomanip>
#include <random>

using namespace std;

// Функция для создания и заполнения квадратной матрицы
vector<vector<int>> createSquareMatrix(int N) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(-100, 100);

    vector<vector<int>> matrix(N, vector<int>(N));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            matrix[i][j] = dis(gen);
        }
    }
    return matrix;
}

vector<vector<int>> createRectangleMatrix2(int M, int N) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(-100, 100);

    vector<vector<int>> matrix(M, vector<int>(N));
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            matrix[i][j] = dis(gen);
        }
    }
    return matrix;
}

// Задание 1
// Функция для нахождения строк с наибольшим количеством положительных чисел
vector<vector<int>> findMaxPositiveRows(const vector<vector<int>>& matrix) {
    int maxPositive = 0;
    vector<vector<int>> maxPositiveRows;
    for (int i = 0; i < matrix.size(); i++) {
        int positiveCount = 0;
        for (int j = 0; j < matrix[i].size(); j++) {
            if (matrix[i][j] > 0) {
                positiveCount++;
            }
        }
        if (positiveCount > maxPositive) {
            maxPositive = positiveCount;
            maxPositiveRows = {matrix[i]};
        } else if (positiveCount == maxPositive) {
            maxPositiveRows.push_back(matrix[i]);
        }
    }
    return maxPositiveRows;
}

//Задание 2
// Функция для нахождения числа, встречающегося чаще всего в матрице
int findMostFrequentNumber(const vector<vector<int>>& matrix) {
    vector<int> frequencyMap(201, 0); // Диапазон чисел от -100 до 100
    int maxFrequency = 0;
    int mostFrequentNumber = -1;
    bool allUnique = true;
    for (const auto& row : matrix) {
        for (int num : row) {
            frequencyMap[num + 100]++; // Смещение для учета отрицательных чисел
            if (frequencyMap[num + 100] > 1) {
                allUnique = false;
            }
            if (frequencyMap[num + 100] > maxFrequency) {
                maxFrequency = frequencyMap[num + 100];
                mostFrequentNumber = num;
            }
        }
    }
    if (allUnique) {
        return -1;
    }
    return mostFrequentNumber;
}

//Задание 3
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
    system("chcp 65001");

    int choice;
    cout << "Выберите задание (1-3): ";
    cin >> choice;
    switch (choice) {
        case 1: {
    cout << "Задача 1:" << endl;
    cout << "Напишите размер квадратной матрицы: " << endl;
    int N;
    cin >> N;
    vector<vector<int>> matrix1 = createSquareMatrix(N);
    cout << "Исходная матрица:" << endl;
    for (const auto& row : matrix1) {
        for (int num : row) {
            cout << setw(5) << num;
        }
        cout << endl;
    }
    vector<vector<int>> maxPositiveRows = findMaxPositiveRows(matrix1);
    cout << "Строки с наибольшим количеством положительных чисел:" << endl;
    for (const auto& row : maxPositiveRows) {
        for (int num : row) {
            cout << num << " ";
        }
        cout << endl;
    }
    break;
        }

    case 2: {
    int M, N;
    cout << "Задача 2:" << endl;
    cout << "Введите количество строк в матрице:  " << endl;
    cin >> M;
    cout << "Введите количество столбцов в матрице:  " << endl;
    cin >> N;
    vector<vector<int>> matrix2 = createRectangleMatrix2(M, N);
    cout << "Исходная матрица:" << endl;
    for (const auto& row : matrix2) {
        for (int num : row) {
            cout << setw(5) << num;
        }
        cout << endl;
    }
    int mostFrequentNumber = findMostFrequentNumber(matrix2);
    if (mostFrequentNumber == -1) {
        cout << "В матрице нет повторяющихся чисел" << endl;
    } else {
        cout << "Число, встречающееся чаще всего: " << mostFrequentNumber << endl;
    }
    break;
        }

    case 3: {
     cout << "Задача 3:" << endl;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 1);

    int rows = 10, cols = 30;
    vector<vector<int>> gameGrid(rows, vector<int>(cols, 0));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            gameGrid[i][j] = dis(gen);
        }
    }
    gameOfLife(gameGrid, 50);
   break;
        }
    }
    return 0;

}
