#include <iostream>
#define N 9 //grid de 9x9 
using namespace std;

//initializam gridul principal
int grid[N][N] = {
   {0, 0, 0, 0, 0, 4, 0, 9, 0},
   {8, 0, 2, 9, 7, 0, 0, 0, 0},
   {9, 0, 1, 2, 0, 0, 3, 0, 0},
   {0, 0, 0, 0, 4, 9, 1, 5, 7},
   {0, 1, 3, 0, 5, 0, 9, 2, 0},
   {5, 7, 9, 1, 2, 0, 0, 0, 0},
   {0, 0, 7, 0, 0, 2, 6, 0, 3},
   {0, 0, 0, 0, 3, 8, 2, 0, 5},
   {0, 2, 0, 5, 0, 0, 0, 0, 0}
};

//facem check daca este  numarul prezent in coloana
bool prezentCol(int col, int num) {
    for (int row = 0; row < N; row++)
        if (grid[row][col] == num)
            return true;
    return false;
}

//facem check daca este  numarul prezent pe rand
bool prezentRand(int row, int num) {
    for (int col = 0; col < N; col++)
        if (grid[row][col] == num)
            return true;
    return false;
}
bool prezentInBox(int boxStartRow, int boxStartCol, int num) {
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
bool liber(int& row, int& col) {
    for (row = 0; row < N; row++)
        for (col = 0; col < N; col++)
            if (grid[row][col] == 0) //daca e 0 atunci e gol
                return true;
    return false;
}
bool valid(int row, int col, int num) {
    //cand nu e gasit itemul in col, rand si suntem in boxul 3x3
    return !prezentRand(row, num) && !prezentCol(col, num) && !prezentInBox(row - row % 3,
        col - col % 3, num);
}
bool sudokuSolver() {
    int row, col;
    if (!liber(row, col))
        return true; //cand toate locurile din grid sunt completate
    for (int num = 1; num <= 9; num++) { //numerele valide sunt doar de la 1 la 9
        if (valid(row, col, num)) { // controlam validarea, daca numerele sunt conform cerintelor, ele ajung in grid
            grid[row][col] = num;
            if (sudokuSolver()) //recursiv va lucra si pentru alte boxuri din grid
                return true;
            grid[row][col] = 0;
        }
    }
    return false;
}
int main() {
    if (sudokuSolver() == true)//daca solutia exista va afisa rezultatul
        sudokuGrid();
    else // daca solutia nu exista va afisa mesajul de mai jos
        cout << "Nu exista solutii";
}