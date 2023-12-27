#pragma once

#include "sudoku.h"

typedef struct NakedDouble_impl
{
    Cell *p_cell1;
    Cell *p_cell2;
    Cell **p_cells;
    int value1;
    int value2;
} NakedDouble;

int is_naked_pair(Cell **p_cells, int value1, int value2);

bool is_in_naked_pair_cell(NakedDouble *p_array, Cell *p);

int is_naked_cell(Cell *p_cell, int value1, int value2);

// find hidden single values (the value that is unique among all the candidates for a row, a collumn, or a box)
int find_naked_double_values(Cell **p_cells, int *naked_double_values);

// find hidden single cells in a row, in a collumn or in a box
void find_naked_double(Cell **p_cells, NakedDouble *p_naked_singles,
                        int *p_counter);

int naked_pairs(SudokuBoard *p_board);