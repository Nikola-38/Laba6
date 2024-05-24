#include <iostream>
#include <vector>
#include <ctime>
#include <iomanip>

using namespace std;

// Функция для создания и заполнения прямоугольной матрицы
vector<vector<int>> createRectangleMatrix(int M, int N) {
    vector<vector<int>> matrix(M, vector<int>(N));
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            matrix[i][j] = rand() % 101 + 100;
        }
    }
    return matrix;
}

// Функция для нахождения числа, встречающегося чаще всего в матрице
int findMostFrequentNumber(const vector<vector<int>>& matrix) {
    vector<int> frequencyMap(101, 0);
    int maxFrequency = 0;
    int mostFrequentNumber = -1;
    bool allUnique = true;
    for (const auto& row : matrix) {
        for (int num : row) {
            frequencyMap[num - 100]++;
            if (frequencyMap[num - 100] > 1) {
                allUnique = false;
            }
            if (frequencyMap[num - 100] > maxFrequency) {
                maxFrequency = frequencyMap[num - 100];
                mostFrequentNumber = num;
            }
        }
    }
    if (allUnique) {
        return -1;
    }
    return mostFrequentNumber;
}

int main() {
    system("chcp 65001");
    srand(static_cast<unsigned int>(time(nullptr)));
    int M, N;
    cout << "Введите количество строк в матрице:  " << endl;
    cin >> M;
    cout << "Введите количество столбцов в матрице:  " << endl;
    cin >> N;
    cout << "Задача 2:" << endl;
    vector<vector<int>> matrix2 = createRectangleMatrix(M, N);
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

    return 0;
}
