//EECS 348 Lab 8 Main File
//C++ programming with matrices
//Input: matricies
//Outputs: modified matrix
//Collaborators: ChatGPT
//Author: Jacob Fonyi
//Date: 4/1/25

#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <stdexcept>

using namespace std;

class MatrixOperations {
private:
    vector<vector<int>> matrix1;
    vector<vector<int>> matrix2;
    int size;

    void printMatrix(const vector<vector<int>>& matrix) {
        for (const auto& row : matrix) {
            for (int val : row) {
                cout << setw(5) << val;
            }
            cout << endl;
        }
    }

public:
    void loadMatricesFromFile(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            throw runtime_error("Error opening file");
        }

        file >> size;
        matrix1.resize(size, vector<int>(size));
        matrix2.resize(size, vector<int>(size));

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                file >> matrix1[i][j];
            }
        }

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                file >> matrix2[i][j];
            }
        }

        cout << "Matrix 1:" << endl;
        printMatrix(matrix1);
        cout << "\nMatrix 2:" << endl;
        printMatrix(matrix2);
    }

    void addMatrices() {
        vector<vector<int>> result(size, vector<int>(size));
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                result[i][j] = matrix1[i][j] + matrix2[i][j];
            }
        }
        cout << "\nSum of matrices:" << endl;
        printMatrix(result);
    }

    void multiplyMatrices() {
        vector<vector<int>> result(size, vector<int>(size, 0));
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                for (int k = 0; k < size; k++) {
                    result[i][j] += matrix1[i][k] * matrix2[k][j];
                }
            }
        }
        cout << "\nProduct of matrices:" << endl;
        printMatrix(result);
    }

    void sumDiagonals(const vector<vector<int>>& matrix) {
        int mainDiag = 0, secondaryDiag = 0;
        for (int i = 0; i < size; i++) {
            mainDiag += matrix[i][i];
            secondaryDiag += matrix[i][size - 1 - i];
        }
        cout << "\nMain diagonal sum: " << mainDiag << endl;
        cout << "Secondary diagonal sum: " << secondaryDiag << endl;
    }

    void swapRows(vector<vector<int>>& matrix, int row1, int row2) {
        if (row1 < 0 || row1 >= size || row2 < 0 || row2 >= size) {
            throw out_of_range("Invalid row index");
        }
        swap(matrix[row1], matrix[row2]);
        cout << "\nMatrix after swapping rows " << row1 << " and " << row2 << ":" << endl;
        printMatrix(matrix);
    }

    void swapColumns(vector<vector<int>>& matrix, int col1, int col2) {
        if (col1 < 0 || col1 >= size || col2 < 0 || col2 >= size) {
            throw out_of_range("Invalid column index");
        }
        for (int i = 0; i < size; i++) {
            swap(matrix[i][col1], matrix[i][col2]);
        }
        cout << "\nMatrix after swapping columns " << col1 << " and " << col2 << ":" << endl;
        printMatrix(matrix);
    }

    void updateElement(vector<vector<int>>& matrix, int row, int col, int newValue) {
        if (row < 0 || row >= size || col < 0 || col >= size) {
            throw out_of_range("Invalid row or column index");
        }
        matrix[row][col] = newValue;
        cout << "\nMatrix after updating element at (" << row << "," << col << "):" << endl;
        printMatrix(matrix);
    }

    vector<vector<int>>& getMatrix1() { return matrix1; }
    vector<vector<int>>& getMatrix2() { return matrix2; }
    int getSize() const { return size; }
};

void displayMenu() {
    cout << "\nMatrix Operations Menu:" << endl;
    cout << "1. Load matrices from file" << endl;
    cout << "2. Add matrices" << endl;
    cout << "3. Multiply matrices" << endl;
    cout << "4. Sum diagonals of matrix 1" << endl;
    cout << "5. Swap rows in matrix 1" << endl;
    cout << "6. Swap columns in matrix 1" << endl;
    cout << "7. Update element in matrix 1" << endl;
    cout << "8. Exit" << endl;
    cout << "Enter your choice: ";
}

int main() {
    MatrixOperations ops;
    string filename;
    int choice;

    while (true) {
        displayMenu();
        cin >> choice;

        try {
            switch (choice) {
                case 1:
                    cout << "Enter filename: ";
                    cin >> filename;
                    ops.loadMatricesFromFile(filename);
                    break;
                case 2:
                    ops.addMatrices();
                    break;
                case 3:
                    ops.multiplyMatrices();
                    break;
                case 4:
                    ops.sumDiagonals(ops.getMatrix1());
                    break;
                case 5: {
                    int row1, row2;
                    cout << "Enter two row indices to swap (0-based): ";
                    cin >> row1 >> row2;
                    ops.swapRows(ops.getMatrix1(), row1, row2);
                    break;
                }
                case 6: {
                    int col1, col2;
                    cout << "Enter two column indices to swap (0-based): ";
                    cin >> col1 >> col2;
                    ops.swapColumns(ops.getMatrix1(), col1, col2);
                    break;
                }
                case 7: {
                    int row, col, value;
                    cout << "Enter row, column, and new value: ";
                    cin >> row >> col >> value;
                    ops.updateElement(ops.getMatrix1(), row, col, value);
                    break;
                }
                case 8:
                    cout << "Exiting program." << endl;
                    return 0;
                default:
                    cout << "Invalid choice. Please try again." << endl;
            }
        } catch (const exception& e) {
            cout << "Error: " << e.what() << endl;
        }
    }

    return 0;
}
