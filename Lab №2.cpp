#include <iostream>
#include <fstream>
using namespace std;


void delMemory(int** matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

void delMemory(double** matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

bool readData(double& start, double& end, double& step, int& n) {
    cout << "Input start, end of interval, step and value of n: ";
    cin >> start >> end >> step >> n;
    if (start >= end || step <= 0 || n == 0) {
        cerr << "Wrong data" << endl;
        return false;
    }
    return true;
}

double calculateY(double x, int n) {
    if (x <= 0) {
        double sumResult = 0;
        for (int i = 2; i <= n - 1; i++)
        {
            sumResult += (x - 1) / i;
        }
        return sumResult;
    }
    else {
        double productResult = 1.0;
        for (int i = 0; i <= n - 1; i++) {
            double sum = 0.0;
            for (int j = 0; j <= i; j++)
            {
                sum += (i + 1) / (j + x);
            }
            productResult *= sum;
        }
        return productResult;
    }
}

void outputData(double start, double end, double step, int n)
{
    cout << "x\ty" << endl;
    for (double x = start; x <= end; x += step)
    {
        cout << x << "\t" << calculateY(x, n) << endl;
    }
}
int main() {
    int rows, cols;
    ifstream inFile("input.txt");
    if (!inFile) {
        cout << "Could not open file input.txt" << endl;
        return 1;
    }
    inFile >> rows >> cols;

    int** arr1 = new int* [rows];
    for (int i = 0; i < rows; i++) {
        arr1[i] = new int[cols];
        for (int j = 0; j < cols; j++) {
            inFile >> arr1[i][j];
        }
    }
    inFile.close();

    double** arr2 = new double* [rows];
    for (int i = 0; i < rows; i++) {
        arr2[i] = new double[cols];
    }

    double start, end, step;
    int n;

    if (!readData(start, end, step, n)) {
        delMemory(arr1, rows);
        delMemory(arr2, rows);
        return 1;
    }

    double x = start;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (x <= end) {
                arr2[i][j] = calculateY(x, n);
                x += step;
            }
            else {
                arr2[i][j] = 0;
            }
        }
    }

    ofstream outFile("output.txt");
    if (!outFile) {
        cout << "Could not open output.txt file for writing" << endl;
        delMemory(arr1, rows);
        delMemory(arr2, rows);
        return 1;
    }

    cout << "\nOutput of the second array:" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            outFile << arr2[i][j] << " ";
            cout << arr2[i][j] << " ";
        }
        outFile << "\n";
        cout << "\n";
    }
    outFile.close();

    delMemory(arr1, rows);
    delMemory(arr2, rows);

    return 0;
}
