#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

// Функция для создания и заполнения квадратной матрицы
vector<vector<int>> createSquareMatrix(int N) {
    vector<vector<int>> matrix(N, vector<int>(N));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            matrix[i][j] = rand() % 201 - 100;
        }
    }
    return matrix;
}

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

int main() {
    system("chcp 65001");

    cout << "Напишите размер квадратной матрицы: "<< endl;
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

    return 0;
}


