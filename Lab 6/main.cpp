#include <iostream>
#include <fstream>
using namespace std;

#define MAX_SIZE 100

void readMatrix(int matrix1[MAX_SIZE][MAX_SIZE], int matrix2[MAX_SIZE][MAX_SIZE], int &size, const char *filename)
{
  ifstream fin(filename);

  // read first line into size reference
  fin >> size;

  // read first matrix
  for (int i = 0; i < size; i++)
  {
    for (int j = 0; j < size; j++)
    {
      fin >> matrix1[i][j];
    }
  }

  // read second matrix
  for (int i = 0; i < size; i++)
  {
    for (int j = 0; j < size; j++)
    {
      fin >> matrix2[i][j];
    }
  }

  fin.close();
}

void printMatrix(int matrix[MAX_SIZE][MAX_SIZE], int size)
{
  for (int i = 0; i < size; i++)
  {
    for (int j = 0; j < size; j++)
    {
      cout << matrix[i][j] << " ";
    }
    cout << endl;
  }
}

void addMatrices(int matrix1[MAX_SIZE][MAX_SIZE], int matrix2[MAX_SIZE][MAX_SIZE], int result[MAX_SIZE][MAX_SIZE], int size)
{
  for (int i = 0; i < size; i++)
  {
    for (int j = 0; j < size; j++)
    {
      result[i][j] = matrix1[i][j] + matrix2[i][j];
    }
  }
}

void multiplyMatrices(int matrix1[MAX_SIZE][MAX_SIZE], int matrix2[MAX_SIZE][MAX_SIZE], int result[MAX_SIZE][MAX_SIZE], int size)
{
  for (int i = 0; i < size; i++)
  {
    for (int j = 0; j < size; j++)
    {
      for (int k = 0; k < size; k++)
      {
        result[i][j] += matrix1[i][k] * matrix2[k][j];
      }
    }
  }
}

void subtractMatrices(int matrix1[][MAX_SIZE], int matrix2[][MAX_SIZE], int result[][MAX_SIZE], int size)
{
  for (int i = 0; i < size; i++)
  {
    for (int j = 0; j < size; j++)
    {
      result[i][j] = matrix1[i][j] - matrix2[i][j];
    }
  }
}

void updateMatrix( int matrix1[MAX_SIZE][MAX_SIZE], int row, int col, int number, int size)
{
    matrix1[row][col] = number;
}

int getMaxValue(int matrix[MAX_SIZE][MAX_SIZE], int size)
{
    int maxValue = matrix[0][0];

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (matrix[i][j] > maxValue)
            {
                maxValue = matrix[i][j];
            }
        }
    }

    return maxValue;
}

void transposeMatrix(int matrix[MAX_SIZE][MAX_SIZE], int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            // Swap row and columns
            int temp = matrix[i][j];
            matrix[i][j] = matrix[j][i];
            matrix[j][i] = temp;
        }
    }
}

int main()
{
  // declare and initialize the empty matrices
  int matrixA[MAX_SIZE][MAX_SIZE];
  int matrixB[MAX_SIZE][MAX_SIZE];
  int matrixSum[MAX_SIZE][MAX_SIZE];
  int matrixProduct[MAX_SIZE][MAX_SIZE];
  int matrixDifference[MAX_SIZE][MAX_SIZE];
  int size = MAX_SIZE;
  readMatrix(matrixA, matrixB, size, "matrix_input.txt");

  cout << "\nMatrix A:\n";
  printMatrix(matrixA, size);

  cout << "\nMatrix B:\n";
  printMatrix(matrixB, size);
  
    char choice;
  cout << "\nDo you want to change Matrix A before continuing? (Y/N): "; // ask if user wants to change matrix A
  cin >> choice;

  if (choice == 'Y' || choice == 'y') 
  {
    int row, col, number;
    cout << "Enter row index, column index, and new value: ";
    cin >> row >> col >> number;

    // decrement row and column by 1
    row--;
    col--;

    if (row > 0 && row <= size && col > 0 && col <= size) // check if the input is valid
    {
        updateMatrix(matrixA, row, col, number, size); // update Matrix A

        cout << "\nUpdated Matrix A:\n"; // print updated Matrix A
        printMatrix(matrixA, size);
    }
    else
    {
        cout << "Invalid input. Matrix A was not changed." << endl;
    }
  }

  cout << "\nMatrix Sum (A + B):\n";
  addMatrices(matrixA, matrixB, matrixSum, size);
  printMatrix(matrixSum, size);

  cout << "\nMatrix Product (A * B):\n";
  multiplyMatrices(matrixA, matrixB, matrixProduct, size);
  printMatrix(matrixProduct, size);

  cout << "\nMatrix Difference (A - B):\n";
  subtractMatrices(matrixA, matrixB, matrixDifference, size);
  printMatrix(matrixDifference, size);

  cout << "\nMax value of Matrix A: " << getMaxValue(matrixA, size) << endl;

  cout << "\nTranspose of Matrix A:\n";
  transposeMatrix(matrixA, size);
  printMatrix(matrixA, size);


  return 0;
}