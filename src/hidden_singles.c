#include "hidden_singles.h"
#include "sudoku.h"
#include <stdlib.h>


int find_hidden_single_values(Cell **p_cells, int *hidden_single_values)
{   
    int hidden_single_count = 0;
    int hidden_single_array[BOARD_SIZE];
    for (int i = 0; i < BOARD_SIZE; i++){
        hidden_single_array[i] = 0;
    }

    for (int i = 0; i < BOARD_SIZE; i++){
        if (p_cells[i]->num_candidates > 1){
            int* candidate_array = get_candidates(p_cells[i]);
            for (int j = 0; j < p_cells[i]->num_candidates; j++){
                hidden_single_array[candidate_array[j]-1] +=1;
            }
            free(candidate_array);
        }
    }
    for (int j = 0; j < BOARD_SIZE; j++){
        if (hidden_single_array[j] == 1){
            hidden_single_values[hidden_single_count++] = j+1;
        }
    }
    return hidden_single_count;
}

// find hidden single cells in a row, in a collumn or in a box
void find_hidden_single(Cell **p_cells, HiddenSingle *p_hidden_singles,
                        int *p_counter){
    int hidden_single_values_array[BOARD_SIZE];
    int num_value = find_hidden_single_values(p_cells, hidden_single_values_array);
    
    for (int i=0; i < num_value; i++){
        for (int j = 0; j < BOARD_SIZE; j++){
            if (is_candidate(p_cells[j], hidden_single_values_array[i])){
                HiddenSingle hidden_singles_object;
                hidden_singles_object.value = hidden_single_values_array[i];
                hidden_singles_object.p_cell = p_cells[j];
                p_hidden_singles[(*p_counter)++] = hidden_singles_object;
            }
        }
    }
}

int hidden_singles(SudokuBoard *p_board)
{       
    HiddenSingle p_hidden_singles[BOARD_SIZE*BOARD_SIZE];
    int p_counter=0;
    for (int i=0; i < BOARD_SIZE; i++)
    {
        find_hidden_single(p_board->p_cols[i], p_hidden_singles, &p_counter);
        find_hidden_single(p_board->p_rows[i], p_hidden_singles, &p_counter);
        find_hidden_single(p_board->p_boxes[i], p_hidden_singles, &p_counter);
    }

    int overlap = p_counter;
    for (int i = 0; i < p_counter; i++){
        int not_overlap = 0;
        Cell *p_cell = p_hidden_singles[i].p_cell;
        int* candidate_array = get_candidates(p_cell);
        int num_candidates = p_cell->num_candidates;
        for (int j = 0; j < num_candidates; j++){
            if (candidate_array[j] != p_hidden_singles[i].value)
            {
                unset_candidate(p_cell, candidate_array[j]);
                not_overlap = 1;
            }
        }
        overlap -= not_overlap;
        free(candidate_array);
    }

    return p_counter-overlap;
}