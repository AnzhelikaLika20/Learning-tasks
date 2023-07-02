#include "const_diagonal.h"

void BuildDiagonalArray(TableType table) {
    int counter = 0;
    int i = 0;
    int j = 0;
    int prev_j = j;
    int prev_i = 0;
    while (counter < LINES * COLUMNS) {
        if (i == LINES) {
            j = COLUMNS - 1;
            i = prev_i + 1;
            prev_i = i;
        } else if (j < 0) {
            i = 0;
            j = prev_j + 1;
            prev_j = j;
        } else {
            table[i][j] = counter;
            counter++;
            i++;
            j--;
        }
    }
}
