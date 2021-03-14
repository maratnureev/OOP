#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <optional>
#include <iomanip>

using namespace std;

const int MATRIX_SIZE = 3;

struct Error {
    bool wasError;
    string message;
};

struct Args {
    string inputFileName;
};

Error setError(string message)
{  
    Error err;
    err.message = message;
    err.wasError = true;
    return err;
}

optional<Args> ParseArgs(int argc,  char* argv[])
{
    if (argc != 2)
    {
        cout << "Invalid args";
        return nullopt;
    }
    Args args;
    args.inputFileName = argv[1];

    return args;
}

Error ReadInputMatrix(string inputFileName, double(&matrix)[MATRIX_SIZE][MATRIX_SIZE])
{
    ifstream in(inputFileName);
    if (!in)
    {
        return setError("File is not exist " + inputFileName);
    }
    string line = "";
    if (in.is_open())
    {
        int i = 0;
        while (getline(in, line))
        {
            size_t index = 0;
            istringstream inStream(line);
            for (int j = 0; j < MATRIX_SIZE; j++)
                inStream >> matrix[i][j];
            i++;
        }
    }
    Error err;
    err.wasError = false;
    return err;
}

double CalculateReverseMatrixElem(int x, int y, const double(&minorMatrix)[MATRIX_SIZE - 1][MATRIX_SIZE - 1])
{
    int k = 0;
    if ((x + 1 + y + 1) % 2 == 0)
        k = 1;
    else
        k = -1;
    return k * (minorMatrix[0][0] * minorMatrix[1][1] - minorMatrix[0][1] * minorMatrix[1][0]);
}

void GetMinorMatrix(int x, int y, double(&minorMatrix)[MATRIX_SIZE - 1][MATRIX_SIZE - 1], const double(&matrix)[MATRIX_SIZE][MATRIX_SIZE])
{
    int iTemp = 0;

    for (int i = 0; i < MATRIX_SIZE - 1; i++)
    {
        if (iTemp == x)
            iTemp++;
        int jTemp = 0;
        for (int j = 0; j < MATRIX_SIZE - 1; j++)
        {
            if (jTemp == y)
                jTemp++;
            minorMatrix[i][j] = matrix[jTemp][iTemp];
            jTemp++;
        }
        iTemp++;
    }
}

double CalculateDeterminant(const double(&matrix)[MATRIX_SIZE][MATRIX_SIZE])
{
    double determinant = 0;
    for (int i = 0; i < MATRIX_SIZE; i++)
    {
        double possitiveDiagonal = 1;
        double negativeDiagonal = 1;
        for (int j = 0; j < MATRIX_SIZE; j++)
        {
            possitiveDiagonal *= matrix[j][(i + j) % MATRIX_SIZE];
            negativeDiagonal *= matrix[MATRIX_SIZE - j - 1][(i + j) % MATRIX_SIZE];
        }
        determinant = determinant + possitiveDiagonal - negativeDiagonal;
    }

    return determinant;
}

Error ReverseMatrix(const double(&matrix)[MATRIX_SIZE][MATRIX_SIZE])
{
    double determinant = CalculateDeterminant(matrix);
    if (determinant == 0)
    {
        return setError("Determinant is 0. Reverse matrix does not exist");
    }
    double alliedMatrix[MATRIX_SIZE][MATRIX_SIZE];
    for (int i = 0; i < MATRIX_SIZE; i++)
        for (int j = 0; j < MATRIX_SIZE; j++)
        {
            double minorMatrix[MATRIX_SIZE - 1][MATRIX_SIZE - 1];
            GetMinorMatrix(i, j, minorMatrix, matrix);
            alliedMatrix[i][j] = CalculateReverseMatrixElem(i, j, minorMatrix);
        }

    double reverseMatrix[MATRIX_SIZE][MATRIX_SIZE];
    for (int i = 0; i < MATRIX_SIZE; i++)
    {
        for (int j = 0; j < MATRIX_SIZE; j++)
        {
            reverseMatrix[i][j] = 1 / determinant * alliedMatrix[i][j];
            cout << fixed << setprecision(3) << reverseMatrix[i][j] << "\t";
        }
        cout << endl;
    }
    Error err;
    err.wasError = false;
    return err;
}

Error CalculateReverseMatrix(string inputFileName)
{
    double matrix[MATRIX_SIZE][MATRIX_SIZE];
    Error err = ReadInputMatrix(inputFileName, matrix);
    if (err.wasError)
        return err;
    err = ReverseMatrix(matrix);
    return err;
}

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "Rus");
    auto args = ParseArgs(argc, argv);
    Error err = CalculateReverseMatrix(args->inputFileName);
    if (err.wasError)
    {
        cout << err.message;
        return 1;
    }
}



