#pragma once

#include "sudoku.h"

typedef struct NakedTriple_impl
{
    Cell *p_cell1;
    Cell *p_cell2;
    Cell *p_cell3;
    Cell **p_cells;
    int value1;
    int value2;
    int value3;
} NakedTriple;

int is_naked_triple_set(Cell **p_cells, int value1, int value2, int value3);

bool is_in_naked_triple_list(NakedTriple *p_array, Cell *p);

int is_naked_triple_cell(Cell *p_cell, int value1, int value2, int value3);

// find hidden single values (the value that is unique among all the candidates for a row, a collumn, or a box)
int find_naked_triple_values(Cell **p_cells, int *naked_triple_values);

// find hidden single cells in a row, in a collumn or in a box
void find_naked_triple(Cell **p_cells, NakedTriple *p_naked_triple,
                        int *p_counter);

int naked_triple(SudokuBoard *p_board);