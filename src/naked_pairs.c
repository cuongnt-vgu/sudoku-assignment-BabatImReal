#include "naked_pairs.h"
#include "sudoku.h"
#include <stdlib.h>
#include <stdio.h>


int naked_cell_array[BOARD_SIZE];

int is_naked_pair(Cell **p_cells, int value1, int value2){
    int count = 0;
    for (int i =0; i < BOARD_SIZE; i++){
        if (p_cells[i]->num_candidates == 2){
            if(is_candidate(p_cells[i], value1) && is_candidate(p_cells[i], value2)){
            count ++;
            }
        }
    }
    return (count ==2);
}

bool is_in_naked_pair_cell(NakedDouble *p_array, Cell *p){
    for (int i = 0; i < BOARD_SIZE * BOARD_SIZE; i++){
        if ((p_array[i].p_cell1 == p)||(p_array[i].p_cell2 == p)){
            return true;
        }
    }
    return false;
}

int is_naked_cell(Cell *p_cell, int value1, int value2){
    if (p_cell->num_candidates == 2){
        return (is_candidate(p_cell, value1) && is_candidate(p_cell, value2));
    }
    return 0;
}

int find_naked_double_values(Cell **p_cells, int *naked_double_values)
{
    int naked_double_count = 0;
    int naked_double_array[BOARD_SIZE];
    for (int i = 0; i < BOARD_SIZE; i++){
        naked_double_array[i] = 0;
    }
    for (int i = 0; i < BOARD_SIZE; i++){
        if (p_cells[i]->num_candidates >= 2){
            int* candidate_array = get_candidates(p_cells[i]); 
            for (int j = 0; j < p_cells[i]->num_candidates; j++){
                naked_double_array[candidate_array[j]-1] += 1; 
            }
            free(candidate_array);
        }
    }
    for (int i = 0; i < BOARD_SIZE; i++){
        if (naked_double_array[i] >= 2){
            naked_double_values[naked_double_count++] = i+1;                  
        }
    }
    return naked_double_count;
}



void find_naked_double(Cell **p_cells, NakedDouble *p_naked_double,
                        int *p_counter)
{       
    int naked_double_value_array[BOARD_SIZE];
    int num_value = find_naked_double_values(p_cells, naked_double_value_array);

    for (int i = 0; i < num_value-1; i++){
        for (int j = i+1; j < num_value; j++){
            if(is_naked_pair(p_cells, naked_double_value_array[i], naked_double_value_array[j])){
                    for (int k = 0; k < BOARD_SIZE-1; k++){
                        for (int l = k+1; l < BOARD_SIZE; l++){
                            if (is_naked_cell(p_cells[k], naked_double_value_array[i], naked_double_value_array[j]) && is_naked_cell(p_cells[l], naked_double_value_array[i], naked_double_value_array[j])){
                                NakedDouble naked_double_object;
                                naked_double_object.p_cell1 = p_cells[k];
                                naked_double_object.p_cell2 = p_cells[l];
                                naked_double_object.p_cells = p_cells;
                                naked_double_object.value1 = naked_double_value_array[i];
                                naked_double_object.value2 = naked_double_value_array[j];
                                p_naked_double[(*p_counter)++] = naked_double_object;
                            }
                        }                
                    }
            }
        }   
    }

}

int naked_pairs(SudokuBoard *p_board)
{
    NakedDouble p_naked_double[BOARD_SIZE*BOARD_SIZE];
    int p_counter = 0;
    for (int i = 0; i< BOARD_SIZE; i++){
        find_naked_double(p_board->p_cols[i], p_naked_double, &p_counter);
        find_naked_double(p_board->p_rows[i], p_naked_double, &p_counter);
        find_naked_double(p_board->p_boxes[i], p_naked_double, &p_counter);
    }
    int overlap = 0;
    NakedDouble solved_cell[BOARD_SIZE*BOARD_SIZE];
    int solved_cell_count = 0;
    for (int i = 0; i < p_counter; i++){
        Cell **p_cells = p_naked_double[i].p_cells;
        if (is_in_naked_pair_cell(solved_cell, p_naked_double[i].p_cell1))
        {
            overlap += 1;
        }
        solved_cell[solved_cell_count++] = p_naked_double[i];
        for (int k = 0; k < BOARD_SIZE; k++)
        {
            if (p_cells[k] == p_naked_double[i].p_cell1 || p_cells[k] == p_naked_double[i].p_cell2) continue; 
            int* candidate_array = get_candidates(p_cells[k]);
            int num_candidates = p_cells[k]->num_candidates;
            for (int j = 0; j < num_candidates; j++){
                if ((candidate_array[j]== p_naked_double[i].value1)){
                unset_candidate(p_cells[k], candidate_array[j]);
                }
                if ((candidate_array[j]== p_naked_double[i].value2)){
                unset_candidate(p_cells[k], candidate_array[j]);
                }

            } 
            free(candidate_array);
        }
    }
    return p_counter - overlap;
}
