#ifndef MATRIX_H
#define MATRIX_H

#include <Arduino.h>

void print_number(LedControl matrix, int number);



const bool numbers [10][5][3] {
    {
        {1,1,1},
        {1,0,1},
        {1,0,1},
        {1,0,1},
        {1,1,1},
    },
    {
        {0,0,1},
        {0,0,1},
        {0,0,1},
        {0,0,1},
        {0,0,1},
    },
    {
        {1,1,1},
        {0,0,1},
        {1,1,1},
        {1,0,0},
        {1,1,1},
    },
    {
        {1,1,1},
        {0,0,1},
        {1,1,1},
        {0,0,1},
        {1,1,1},
    },
    {
        {1,0,1},
        {1,0,1},
        {1,1,1},
        {0,0,1},
        {0,0,1},
    },
    {
        {1,1,1},
        {1,0,0},
        {1,1,1},
        {0,0,1},
        {1,1,1},
    },
    {
        {1,1,1},
        {1,0,0},
        {1,1,1},
        {1,0,1},
        {1,1,1},
    },
    {
        {1,1,1},
        {0,0,1},
        {0,0,1},
        {0,0,1},
        {0,0,1},
    },
    {
        {1,1,1},
        {1,0,1},
        {1,1,1},
        {1,0,1},
        {1,1,1},
    },
    {
        {1,1,1},
        {1,0,1},
        {1,1,1},
        {0,0,1},
        {0,0,1},
    }
};

void matrix_print_number(LedControl matrix, int number){

    bool repr [8][8] {
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
    };

    int units = number % 10;
    int tens = number / 10;

    for (int i = 0; i < 5; i++){
        for (int j = 0; j < 3; j++){
            repr[i+2][j+1] = numbers[tens][i][j];
            repr[i+2][j+5] = numbers[units][i][j];
        }
    }

    // Print matrix
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            matrix.setLed(0, i, j, repr[i][j]);
        }
    }
}

void clear_matrix(LedControl matrix){
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            matrix.setLed(0, i, j, 0);
        }
    }
}

#endif