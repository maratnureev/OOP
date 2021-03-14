#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <optional>
#include <iomanip>
#include <stack>

using namespace std;

const int MATRIX_SIZE = 102;
const char WALL_SYMBOL = '#';
const char FILL_SYMBOL = '_';
const char START_SYMBOL = 'O';

struct Coords {
    int x;
    int y;
};

struct Args {
    string inputFileName;
    string outputFileName;
};

struct Error {
    bool wasError;
    string message;
};

Error setError(string message)
{
    Error err;
err.message = message;
err.wasError = true;
return err;
}

optional<Args> ParseArgs(int argc, char* argv[])
{
    if (argc != 3)
    {
        cout << "Invalid args";
        return nullopt;
    }
    Args args;
    args.inputFileName = argv[1];
    args.outputFileName = argv[2];

    return args;
}

Error PrintField(string outputFileName, const char(&field)[MATRIX_SIZE][MATRIX_SIZE])
{
    ofstream out(outputFileName);
    if (!out)
    {
        return setError("File is not exist " + outputFileName);
    }
    for (int i = 1; i < MATRIX_SIZE - 1; i++)
    {
        for (int j = 1; j < MATRIX_SIZE - 1; j++)
            out << field[i][j];
        out << endl;
    }
    Error err;
    err.wasError = false;
    return err;
}

void Push(int i, int j, stack <Coords>& steck)
{
    Coords coords;
    coords.x = i;
    coords.y = j;
    steck.push(coords);
}

Error ReadInputField(string inputFileName, char(&field)[MATRIX_SIZE][MATRIX_SIZE])
{
    ifstream in(inputFileName);
    if (!in)
    {
        return setError("File is not exist " + inputFileName);
    }
    string line = "";
    if (in.is_open())
    {
        int i = 1;
        while (getline(in, line))
        {
            if (i > 100)
                break;
            size_t index = 0;
            istringstream inStream(line);
            for (int j = 1; j < MATRIX_SIZE - 1; j++)
                inStream.get(field[i][j]);
            i++;
        }
    }
    Error err;
    err.wasError = false;
    return err;
}

void SetWalls(char(&field)[MATRIX_SIZE][MATRIX_SIZE])
{
    for (int i = 0; i < MATRIX_SIZE; i++)
    {
        field[0][i] = WALL_SYMBOL;
        field[MATRIX_SIZE - 1][i] = WALL_SYMBOL;
        field[i][0] = WALL_SYMBOL;
        field[i][MATRIX_SIZE - 1] = WALL_SYMBOL;
    }
}

void Fill(char(&field)[MATRIX_SIZE][MATRIX_SIZE], stack <Coords>& steck)
{
    Coords coords = steck.top();
    steck.pop();
    int x = coords.x;
    int y = coords.y;
    if (field[x][y] != START_SYMBOL)
        field[x][y] = FILL_SYMBOL;
    if ((field[x + 1][y] != WALL_SYMBOL) && (field[x + 1][y] != START_SYMBOL) && (field[x + 1][y] != FILL_SYMBOL))
        Push(x + 1, y, steck);
    if ((field[x - 1][y] != WALL_SYMBOL) && (field[x - 1][y] != START_SYMBOL) && (field[x - 1][y] != FILL_SYMBOL))
        Push(x - 1, y, steck);
    if ((field[x][y + 1] != WALL_SYMBOL) && (field[x][y + 1] != START_SYMBOL) && (field[x][y + 1] != FILL_SYMBOL))
        Push(x, y + 1, steck);
    if ((field[x][y - 1] != WALL_SYMBOL) && (field[x][y - 1] != START_SYMBOL) && (field[x][y - 1] != FILL_SYMBOL))
        Push(x, y - 1, steck);
}

void InitField(char(&field)[MATRIX_SIZE][MATRIX_SIZE])
{
    for (int i = 0; i < MATRIX_SIZE; i++)
        for (int j = 0; j < MATRIX_SIZE; j++)
            field[i][j] = ' ';
    SetWalls(field);
}

Error FillField(string inputFileName, string outputFileName)
{
    char field[MATRIX_SIZE][MATRIX_SIZE];
    InitField(field);
    Error err = ReadInputField(inputFileName, field);
    if (err.wasError)
        return err;
    stack <Coords> steck;
    for (int i = 1; i < MATRIX_SIZE - 1; i++)
        for (int j = 1; j < MATRIX_SIZE - 1; j++)
            if (field[i][j] == START_SYMBOL)
                Push(i, j, steck);

    while (!steck.empty())
    {
        Fill(field, steck);
    }

    err = PrintField(outputFileName, field);
    return err;
}

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "rus");
    auto args = ParseArgs(argc, argv);
    
    Error err = FillField(args->inputFileName, args->outputFileName);
    if (err.wasError)
    {
        cout << err.message;
        return 1;
    }
}
