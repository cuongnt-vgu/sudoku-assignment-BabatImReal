#pragma once

#include "sudoku.h"

typedef struct HiddenDouble_impl
{
    Cell *p_cell;
    int value1;
    int value2;
} HiddenDouble;

// find hidden single values (the value that is unique among all the candidates for a row, a collumn, or a box)
int find_hidden_double_values(Cell **p_cells, int *hidden_double_values);

// find hidden single cells in a row, in a collumn or in a box
void find_hidden_double(Cell **p_cells, HiddenDouble *p_hidden_singles,
                        int *p_counter);

int hidden_pairs(SudokuBoard *p_board);
