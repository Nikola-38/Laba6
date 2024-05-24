#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

// Метод Гаусса с выбором главного элемента
void gaussElimination(double A[][5], double b[], double x[], int n) {
    double maxVal, temp;
    int maxRow;

    // Прямой ход
    for (int i = 0; i < n - 1; i++) {
        maxVal = fabs(A[i][i]);
        maxRow = i;
        for (int j = i + 1; j < n; j++) {
            if (fabs(A[j][i]) > maxVal) {
                maxVal = fabs(A[j][i]);
                maxRow = j;
            }
        }

        // Меняем местами строки
        if (maxRow != i) {
            for (int j = 0; j < n; j++) {
                temp = A[i][j];
                A[i][j] = A[maxRow][j];
                A[maxRow][j] = temp;
            }
            temp = b[i];
            b[i] = b[maxRow];
            b[maxRow] = temp;
        }

        // Прямой ход
        for (int j = i + 1; j < n; j++) {
            double factor = A[j][i] / A[i][i];
            for (int k = i; k < n; k++) {
                A[j][k] -= factor * A[i][k];
            }
            b[j] -= factor * b[i];
        }
    }

    // Обратный ход
    x[n - 1] = b[n - 1] / A[n - 1][n - 1];
    for (int i = n - 2; i >= 0; i--) {
        double sum = b[i];
        for (int j = i + 1; j < n; j++) {
            sum -= A[i][j] * x[j];
        }
        x[i] = sum / A[i][i];
    }
}


// Метод простых итераций
void simpleIteration(double A[][5], double b[], double x[], int n, double epsilon) {
    double xNew[4], maxDiff;
    int iter = 0;

    do {
        for (int i = 0; i < n; i++) {
            double sum = b[i];
            for (int j = 0; j < n; j++) {
                if (j != i) {
                    sum -= A[i][j] * x[j];
                }
            }
            xNew[i] = sum / A[i][i];
        }

        maxDiff = 0.0;
        for (int i = 0; i < n; i++) {
            if (fabs(xNew[i] - x[i]) > maxDiff) {
                maxDiff = fabs(xNew[i] - x[i]);
            }
            x[i] = xNew[i];
        }
        iter++;
    } while (maxDiff > epsilon);

    cout << "Число итераций: " << iter << endl;
}

int main() {
    double A[4][5] = {
        {-0.88, -0.04, 0.21, -18, -1.24},
        {0.25, -1.23, 0.1, -0.09, 0.91},
        {-0.21, 0.1, 0.8, -0.13, 2.56},
        {0.15, -1.31, 0.06, 0.91, -0.88}
    };
    double b[4] = {-1.24, 0.91, 2.56, -0.88};
    double x[4] = {0.0};

    // Решение методом Гаусса
    cout << "Решение методом Гаусса:" << endl;
    gaussElimination(A, b, x, 4);
    cout << "x1 = " << x[0] << endl;
    cout << "x2 = " << x[1] << endl;
    cout << "x3 = " << x[2] << endl;
    cout << "x4 = " << x[3] << endl;

    // Решение методом простых итераций
    cout << "\nРешение методом простых итераций:" << endl;
    simpleIteration(A, b, x, 4, 0.001);
    cout << "x1 = " << x[0] << endl;
    cout << "x2 = " << x[1] << endl;
    cout << "x3 = " << x[2] << endl;
    cout << "x4 = " << x[3] << endl;

    return 0;
}
