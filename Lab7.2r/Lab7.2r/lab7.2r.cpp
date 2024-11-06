#include <iostream>
#include <iomanip>
#include <time.h>
using namespace std;

void CreateRow(int** a, const int rowNo, const int N, const int Low, const int High, int colNo);
void CreateMatrix(int** a, const int N, const int Low, const int High, int rowNo);
void PrintRow(int** a, const int rowNo, const int N, int colNo);
void PrintMatrix(int** a, const int N, int rowNo);
void FindMaxAbove(int** a, const int N, int rowNo, int colNo, int& maxVal, int& maxRow, int& maxCol);
void FindMinBelow(int** a, const int N, int rowNo, int colNo, int& minVal, int& minRow, int& minCol);
void SwapMaxMin(int** a, const int N, int& sum, int maxRow, int maxCol, int minRow, int minCol);

int main() {
    srand((unsigned)time(NULL));
    int N;
    cout << "N = ";
    cin >> N;
    cout << endl;

    int Low = -50; // Нижня межа для генерації елементів
    int High = 50; // Верхня межа для генерації елементів

    int** a = new int* [N];
    for (int i = 0; i < N; i++)
        a[i] = new int[N];

    // Створюємо матрицю
    CreateMatrix(a, N, Low, High, 0);

    // Виводимо початкову матрицю
    cout << "Initial matrix:" << endl;
    PrintMatrix(a, N, 0);

    // Змінні для зберігання максимального та мінімального значень
    int maxVal = INT_MIN, minVal = INT_MAX;
    int maxRow, maxCol, minRow, minCol;

    // Знаходимо максимальний елемент над головною діагоналлю
    FindMaxAbove(a, N, 0, 0, maxVal, maxRow, maxCol);

    // Знаходимо мінімальний елемент під головною діагоналлю
    FindMinBelow(a, N, 1, 0, minVal, minRow, minCol);

    // Обчислюємо суму
    int sum = (maxVal == INT_MIN || minVal == INT_MAX) ? 0 : maxVal + minVal;

    // Міняємо місцями максимальний і мінімальний елементи
    if (maxVal != INT_MIN && minVal != INT_MAX) {
        SwapMaxMin(a, N, sum, maxRow, maxCol, minRow, minCol);
    }

    // Виводимо результати
    cout << "Sum of max element above and min element below diagonal = " << sum << endl;

    // Виводимо модифіковану матрицю
    cout << "Modified matrix after swapping max and min elements:" << endl;
    PrintMatrix(a, N, 0);

    // Звільнення пам'яті
    for (int i = 0; i < N; i++)
        delete[] a[i];
    delete[] a;

    return 0;
}

// Рекурсивна функція для створення рядка матриці
void CreateRow(int** a, const int rowNo, const int N, const int Low, const int High, int colNo) {
    a[rowNo][colNo] = Low + rand() % (High - Low + 1);
    if (colNo < N - 1)
        CreateRow(a, rowNo, N, Low, High, colNo + 1); // Рекурсивний виклик для наступного стовпця
}

// Рекурсивна функція для створення матриці
void CreateMatrix(int** a, const int N, const int Low, const int High, int rowNo) {
    if (rowNo < N) {
        CreateRow(a, rowNo, N, Low, High, 0); // Створюємо рядок
        CreateMatrix(a, N, Low, High, rowNo + 1); // Рекурсивний виклик для наступного рядка
    }
}

// Рекурсивна функція для виведення рядка матриці
void PrintRow(int** a, const int rowNo, const int N, int colNo) {
    cout << setw(4) << a[rowNo][colNo];
    if (colNo < N - 1)
        PrintRow(a, rowNo, N, colNo + 1); // Рекурсивний виклик для наступного стовпця
    else
        cout << endl;
}

// Рекурсивна функція для виведення матриці
void PrintMatrix(int** a, const int N, int rowNo) {
    if (rowNo < N) {
        PrintRow(a, rowNo, N, 0); // Виводимо рядок
        PrintMatrix(a, N, rowNo + 1); // Рекурсивний виклик для наступного рядка
    }
}

// Рекурсивна функція для знаходження максимального елемента над головною діагоналлю
void FindMaxAbove(int** a, const int N, int rowNo, int colNo, int& maxVal, int& maxRow, int& maxCol) {
    if (rowNo < N) {
        if (colNo < N - rowNo - 1) {
            if (a[rowNo][colNo] > maxVal) {
                maxVal = a[rowNo][colNo];
                maxRow = rowNo;
                maxCol = colNo;
            }
            FindMaxAbove(a, N, rowNo, colNo + 1); // Рекурсивний виклик для наступного стовпця
        }
        else {
            FindMaxAbove(a, N, rowNo + 1, 0); // Рекурсивний виклик для наступного рядка
        }
    }
}

// Рекурсивна функція для знаходження мінімального елемента під головною діагоналлю
void FindMinBelow(int** a, const int N, int rowNo, int colNo, int& minVal, int& minRow, int& minCol) {
    if (rowNo < N) {
        if (colNo < rowNo) {
            if (a[rowNo][colNo] < minVal) {
                minVal = a[rowNo][colNo];
                minRow = rowNo;
                minCol = colNo;
            }
            FindMinBelow(a, N, rowNo, colNo + 1); // Рекурсивний виклик для наступного стовпця
        }
        else {
            FindMinBelow(a, N, rowNo + 1, 0); // Рекурсивний виклик для наступного рядка
        }
    }
}

// Функція для обміну місцями максимального і мінімального елементів
void SwapMaxMin(int** a, const int N, int& sum, int maxRow, int maxCol, int minRow, int minCol) {
    int temp = a[maxRow][maxCol];
    a[maxRow][maxCol] = a[minRow][minCol];
    a[minRow][minCol] = temp;
}
