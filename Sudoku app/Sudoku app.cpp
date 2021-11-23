#include <iostream>
#define N 9 //vor fi 9 subgriduri 
using namespace std;

//initializam gridul principal
int grid[N][N] = {
   {3, 0, 6, 5, 0, 8, 4, 0, 0},
   {5, 2, 0, 0, 0, 0, 0, 0, 0},
   {0, 8, 7, 0, 0, 0, 0, 3, 1},
   {0, 0, 3, 0, 1, 0, 0, 8, 0},
   {9, 0, 0, 8, 6, 3, 0, 0, 5},
   {0, 5, 0, 0, 9, 0, 6, 0, 0},
   {1, 3, 0, 0, 0, 0, 2, 5, 0},
   {0, 0, 0, 0, 0, 0, 0, 7, 4},
   {0, 0, 5, 2, 0, 6, 3, 0, 0}
};

//facem check daca este  numarul prezent in coloana
bool isPresentInCol(int col, int num) {
    for (int row = 0; row < N; row++)
        if (grid[row][col] == num)
            return true;
    return false;
}

//facem check daca este  numarul prezent pe rand
bool isPresentInRow(int row, int num) {
    for (int col = 0; col < N; col++)
        if (grid[row][col] == num)
            return true;
    return false;
}
bool isPresentInBox(int boxStartRow, int boxStartCol, int num) {
    //facem check daca numarul e prezent intr-un tabel de 3x3 sau nu
    for (int row = 0; row < 3; row++)
        for (int col = 0; col < 3; col++)
            if (grid[row + boxStartRow][col + boxStartCol] == num)
                return true;
    return false;
}
//afisare a tabelului sudoku dupa rezolvare(builder al tabelului)
void sudokuGrid() {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            if (col == 3 || col == 6)
                cout << " | ";
            cout << grid[row][col] << " ";
        }
        if (row == 2 || row == 5) {
            cout << endl;
            for (int i = 0; i < N; i++)
                cout << "---";
        }
        cout << endl;
    }
}//gasim locurile goale si facem update la randuri si coloane
bool findEmptyPlace(int& row, int& col) {
    for (row = 0; row < N; row++)
        for (col = 0; col < N; col++)
            if (grid[row][col] == 0) //daca e 0 atunci e gol
                return true;
    return false;
}
bool isValidPlace(int row, int col, int num) {
    //cand nu e gasit itemul in col, rand si suntem in boxul 3x3
    return !isPresentInRow(row, num) && !isPresentInCol(col, num) && !isPresentInBox(row - row % 3,
        col - col % 3, num);
}
bool solveSudoku() {
    int row, col;
    if (!findEmptyPlace(row, col))
        return true; //cand toate locurile din grid sunt completate
    for (int num = 1; num <= 9; num++) { //numerele valide sunt doar de la 1 la 9
        if (isValidPlace(row, col, num)) { // controlam validarea, daca numerele sunt conform cerintelor, ele ajung in grid
            grid[row][col] = num;
            if (solveSudoku()) //recursiv va lucra si pentru alte boxuri din grid
                return true;
            grid[row][col] = 0;
        }
    }
    return false;
}
int main() {
    if (solveSudoku() == true)//daca solutia exista va afisa rezultatul
        sudokuGrid();
    else // daca solutia nu exista va afisa mesajul de mai jos
        cout << "Nu exista solutii";
}