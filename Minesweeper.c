#include <stdio.h>
#include <stdlib.h>
#include "Minesweeper.h"

//gcc -Wall Minesweeper.c -o Minesweeper
enum difficulty;


int select_difficulty() {

    int difficulty_selected = FALSE;
    int diff_level;
    
    do {
        printf("please select a difficulty level: 0 = SIMPLE, 1 = EASY, 2 = MEDIUM, 3 = HARD\n");
        scanf("%d", &diff_level);

        if(diff_level >= 0 && diff_level <= 3) {
            switch(diff_level) {
                case(0):
                    difficulty_selected = TRUE;
                    break;
                
                case(1):
                    difficulty_selected = TRUE;
                    break;
                
                case(2):
                    difficulty_selected = TRUE;
                    break;
                
                case(3):
                    difficulty_selected = TRUE;
                    break;
            }
                
        }
        else {
            printf("Selected difficulty level is invalid please try again\n");
        }
    }
    while( (difficulty_selected = FALSE) );
    
    return diff_level;



}

void print_board(enum difficulty game_difficulty) {
    
    printf("print board");

}

int main() {
enum difficulty game_difficulty = select_difficulty();
printf("main\n");
print_board(game_difficulty);

};
