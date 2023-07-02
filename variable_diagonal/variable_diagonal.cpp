#include "variable_diagonal.h"

int** BuildDiagonalArray(size_t lines, size_t columns) {
    int** table = new int*[lines];
    for (size_t i = 0; i < lines; ++i) {
        table[i] = new int[columns];
    }
    int counter = 0;
    size_t x = 0;
    size_t y = 0;
    for (size_t i = 0; i < lines + columns - 1; i++) {
        for (size_t j = 0; j < lines; ++j) {
            x = i < columns ? 0 : i - columns + 1;
            y = i < columns ? i - j : columns - j - 1;
            table[j + x][y] = counter;
            counter++;
            if (i < columns && y == 0) {
                break;
            } else if (i >= columns && j + x == lines - 1) {
                break;
            }
        }
    }
    return table;
}
