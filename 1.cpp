#include <iostream>
#include <vector>
#include <iomanip>
#include <random>
#include "windows.h"

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
    uniform_int_distribution<> dis(100, 200);

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
    vector<int> frequencyMap(101, 0); // Диапазон чисел от 100 до 200
    int maxFrequency = 0;
    int mostFrequentNumber = -1;
    bool allUnique = true;
    for (const auto& row : matrix) {
    for (int num : row) {
    frequencyMap[num - 100]++; 
    if (frequencyMap[num - 100] > 1) { // Проверка на наличие повторяющихся чисел
    allUnique = false;
    }
    if (frequencyMap[num - 100] > maxFrequency) { // Проверка на наиболее часто встречающееся число
    maxFrequency = frequencyMap[num - 100];
    mostFrequentNumber = num;
 }
    }
    }
    if (allUnique) { // Если все числа уникальны, возвращаем -1
    return -1;
    }
    return mostFrequentNumber;
}


void gameOfLife(vector<vector<int>>& grid, int generations) {
    // Получение количества строк и столбцов в матрице
    int rows = grid.size();
    int cols = grid[0].size();

    // Создание временной матрицы для хранения следующего состояния игрового поля
    vector<vector<int>> nextGrid(rows, vector<int>(cols, 0));

    // Итерация по количеству поколений
    for (int gen = 0; gen < generations; gen++) {
        // Итерация по каждой клетке на текущем игровом поле
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                // Подсчет живых соседей для текущей клетки
                int liveNeighbors = 0;
                for (int di = -1; di <= 1; di++) {
                    for (int dj = -1; dj <= 1; dj++) {
                        // Пропуск текущей клетки
                        if (di == 0 && dj == 0) {
                            continue;
                        }
                        // Вычисление координат соседней клетки
                        int x = i + di;
                        int y = j + dj;
                        // Проверка на выход за границы игрового поля и живой сосед
                        if (x >= 0 && x < rows && y >= 0 && y < cols && grid[x][y] == 1) {
                            liveNeighbors++;
                        }
                    }
                }
                // Применение правил игры жизнь для текущей клетки
                if (grid[i][j] == 1) {
                    // Клетка умирает при наличии менее 2 или более 3 живых соседей
                    if (liveNeighbors < 2 || liveNeighbors > 3) {
                        nextGrid[i][j] = 0;
                    } else {
                        nextGrid[i][j] = 1;
                    }
                } else {
                    // Клетка оживает при наличии ровно 3 живых соседей
                    if (liveNeighbors == 3) {
                        nextGrid[i][j] = 1;
                    } else {
                        nextGrid[i][j] = 0;
                    }
                }
            }
        }

        // Обновление игрового поля следующим поколением
        grid = nextGrid;
        // Очистка временной матрицы для следующего поколения
        nextGrid = vector<vector<int>>(rows, vector<int>(cols, 0));

        // Очистка консоли для вывода нового состояния игрового поля
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif

        // Вывод текущего состояния игрового поля в отдельном терминале
        #ifdef _WIN32
            system("start cmd /c cls && mode con: cols=10 lines=20 && ");
        #else
            system("clear && printf '\e[3;1H'");
        #endif
        for (const auto& row : grid) {
            for (int cell : row) {
                if (cell == 0) {
                    cout << "*";
                } else {
                    cout << "1 ";
                }
            }
            cout << endl;
        }
        cout << endl;

        // Задержка на 1 секунду
        #ifdef _WIN32
            Sleep(1000);
        #else
            usleep(1000000);
        #endif
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

    int rows = 15, cols = 20;
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
