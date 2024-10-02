#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Minesweeper.h"

//gcc -Wall Minesweeper.c -o Minesweeper

/**
 * 
 * @brief prompts the user to select a difficulty for the game. 0 = SIMPLE, 1 = EASY, 2 = MEDIUM, 3 = HARD. This function will loop until a valid difficulty is selected.
 * 
 * @return returns an int respresenting the selected difficulty.  
 * 
*/
int select_difficulty() {

    int difficulty_selected = FALSE;
    int diff_level;
    
    while( (difficulty_selected == FALSE) ) {
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
    
    
    return diff_level;



}

/**
 * 
 * @brief will use random numbers to determine where bombs are placed on the board, up to a certain number of bombs
 * 
 * @param game_board_arr the game_board struct that will have bombs set to it by this function.
 * 
 * @return returns nothing.  
 * 
*/
void set_bombs(struct game_board* game_board_arr, int col_in, int row_in) {

    int bombs_set = 0;

    switch(game_board_arr->board_difficulty) {

        case(SIMPLE):

            srand(time(0));
            
            while(bombs_set != game_board_arr->number_of_bombs) {

                for (int i = 0; i < game_board_arr->cols; i++)
                {
                    
                    for (int j = 0; j < game_board_arr->rows; j++)
                    {
                        
                        int mod_val = rand() % 2;

                        if(mod_val == 1 && (i != col_in && j != row_in)) {
                            game_board_arr->board_ptr[i].cells_ptr[j].has_bomb = TRUE;
                            bombs_set++;
                        }

                        if(bombs_set == game_board_arr->number_of_bombs) {
                            break;
                        }

                    }

                    if(bombs_set == game_board_arr->number_of_bombs) {
                            break;
                    }

                }
            
            }

            break;


        case(EASY):

            srand(time(0));

            while(bombs_set != game_board_arr->number_of_bombs) {

                for (int i = 0; i < game_board_arr->cols; i++)
                {
                    
                    for (int j = 0; j < game_board_arr->rows; j++)
                    {
                        
                        int mod_val = rand() % 2;

                        if(mod_val == 1 && (i != col_in && j != row_in)) {
                            game_board_arr->board_ptr[i].cells_ptr[j].has_bomb = TRUE;
                            bombs_set++;
                        }

                        if(bombs_set == game_board_arr->number_of_bombs) {
                            break;
                        }

                    }

                    if(bombs_set == game_board_arr->number_of_bombs) {
                            break;
                    }

                }
            
            }

            break;

        case(MEDIUM):

            srand(time(0));;

            while(bombs_set != game_board_arr->number_of_bombs) {

                for (int i = 0; i < game_board_arr->cols; i++)
                {
                    
                    for (int j = 0; j < game_board_arr->rows; j++)
                    {
                        
                        int mod_val = rand() % 2;

                        if(mod_val == 1 && (i != col_in && j != row_in)) {
                            game_board_arr->board_ptr[i].cells_ptr[j].has_bomb = TRUE;
                            bombs_set++;
                        }

                        if(bombs_set == game_board_arr->number_of_bombs) {
                            break;
                        }

                    }

                    if(bombs_set == game_board_arr->number_of_bombs) {
                            break;
                    }

                }
            
            }

            break;

        case(HARD):

            srand(time(0));

            while(bombs_set != game_board_arr->number_of_bombs) {

                for (int i = 0; i < game_board_arr->cols; i++)
                {
                    
                    for (int j = 0; j < game_board_arr->rows; j++)
                    {
                        
                        int mod_val = rand() % 2;

                        if(mod_val == 1 && (i != col_in && j != row_in)) {
                            game_board_arr->board_ptr[i].cells_ptr[j].has_bomb = TRUE;
                            bombs_set++;
                        }

                        if(bombs_set == game_board_arr->number_of_bombs) {
                            break;
                        }

                    }

                    if(bombs_set == game_board_arr->number_of_bombs) {
                            break;
                    }

                }
            
            }

            break;

    }
}


/**
 * 
 * @brief Will initialize the game board based on the selected difficulty.
 * 
 * @param game_difficulty this will determine the size of the structure created.
 * 
 * @return returns a pointer to the game board.
 * 
 * TODO - add memory freeing if malloc fails
 *      - figure out where missing return is
 * 
*/
void* create_game_board_array(enum difficulty game_difficulty) {

    //declare struct that will be returned by function.
    struct game_board* game_array = NULL;

    //error handling for difficulties outside of enum.
    if (game_difficulty < 0 || game_difficulty > 3) {
        printf("Error: game difficulty out of bounds.\n");
        return game_array;
        exit(1);
    }

    switch(game_difficulty) {
        case(SIMPLE):
            
            //initialize game_array struct
            game_array = (struct game_board*)malloc(sizeof(struct game_board)*1);

            //check for malloc success
            if (game_array == NULL) {
                printf("Error: memory allocation failed.\n");
                free(game_array);
                exit(1);
            }

            //populate data members
            game_array->rows = 5;
            game_array->cols = 5;
            game_array->number_of_bombs = 3;
            game_array->g_stat = MENU;
            game_array->board_difficulty = game_difficulty;

            //allocate memory to store the game_cell array pointers
            game_array->board_ptr = (struct dynamic_array*)malloc(sizeof(struct dynamic_array)*game_array->cols);

            //check for malloc success
            if (game_array->board_ptr == NULL) {
                printf("Error: memory allocation failed.\n");
                free(game_array->board_ptr);
                free(game_array);
                exit(1);
            }

            //allocate the memory for the game_cell structs, and populate its data members.
            for(int x = 0; x < game_array->cols; x++) {

                game_array->board_ptr[x].cells_ptr = (struct game_cell*)malloc(sizeof(struct game_cell)*game_array->rows);
                
                //check for malloc success
                if (game_array->board_ptr[x].cells_ptr == NULL) {

                    printf("Error: memory allocation failed.\n");

                    for(int x = 0; x < game_array->cols; x++) {
                        free(game_array->board_ptr[x].cells_ptr);
                    }
                    free(game_array->board_ptr);
                    free(game_array);
                    exit(1);
                }

                for(int y = 0; y < game_array->rows; y++) {

                    game_array->board_ptr[x].cells_ptr[y].c_stat = HIDDEN;
                    game_array->board_ptr[x].cells_ptr[y].visited = FALSE;
                    game_array->board_ptr[x].cells_ptr[y].display_char = ' ';

                }

            }

            break;

        case(EASY):

            //initialize game_array struct
            game_array = (struct game_board*)malloc(sizeof(struct game_board)*1);

            //check for malloc success
            if (game_array == NULL) {
                printf("Error: memory allocation failed.\n");
                free(game_array);
                exit(1);
            }

            //populate data members
            game_array->rows = 9;
            game_array->cols = 9;
            game_array->number_of_bombs = 10;
            game_array->g_stat = MENU;
            game_array->board_difficulty = game_difficulty;

            //allocate memory to store the game_cell array pointers
            game_array->board_ptr = (struct dynamic_array*)malloc(sizeof(struct dynamic_array)*game_array->cols);

            //check for malloc success
            if (game_array->board_ptr == NULL) {
                printf("Error: memory allocation failed.\n");
                free(game_array->board_ptr);
                free(game_array);
                exit(1);
            }

            //allocate the memory for the game_cell structs, and populate its data members.
            for(int x = 0; x < game_array->cols; x++) {

                game_array->board_ptr[x].cells_ptr = (struct game_cell*)malloc(sizeof(struct game_cell)*game_array->rows);
                
                //check for malloc success
                if (game_array->board_ptr[x].cells_ptr == NULL) {

                    printf("Error: memory allocation failed.\n");

                    for(int x = 0; x < game_array->cols; x++) {
                        free(game_array->board_ptr[x].cells_ptr);
                    }
                    free(game_array->board_ptr);
                    free(game_array);
                    exit(1);
                }

                for(int y = 0; y < game_array->rows; y++) {

                    game_array->board_ptr[x].cells_ptr[y].c_stat = HIDDEN;
                    game_array->board_ptr[x].cells_ptr[y].display_char = ' ';

                }

            }

            break;

        case(MEDIUM):

            //initialize game_array struct
            game_array = (struct game_board*)malloc(sizeof(struct game_board)*1);

            //check for malloc success
            if (game_array == NULL) {
                printf("Error: memory allocation failed.\n");
                free(game_array);
                exit(1);
            }

            //populate data members
            game_array->rows = 16;
            game_array->cols = 16;
            game_array->number_of_bombs = 40;
            game_array->g_stat = MENU;
            game_array->board_difficulty = game_difficulty;

            //allocate memory to store the game_cell array pointers
            game_array->board_ptr = (struct dynamic_array*)malloc(sizeof(struct dynamic_array)*game_array->cols);

            //check for malloc success
            if (game_array->board_ptr == NULL) {
                printf("Error: memory allocation failed.\n");
                free(game_array->board_ptr);
                free(game_array);
                exit(1);
            }

            //allocate the memory for the game_cell structs, and populate its data members.
            for(int x = 0; x < game_array->cols; x++) {

                game_array->board_ptr[x].cells_ptr = (struct game_cell*)malloc(sizeof(struct game_cell)*game_array->rows);
                
                //check for malloc success
                if (game_array->board_ptr[x].cells_ptr == NULL) {

                    printf("Error: memory allocation failed.\n");

                    for(int x = 0; x < game_array->cols; x++) {
                        free(game_array->board_ptr[x].cells_ptr);
                    }
                    free(game_array->board_ptr);
                    free(game_array);
                    exit(1);
                }

                for(int y = 0; y < game_array->rows; y++) {

                    game_array->board_ptr[x].cells_ptr[y].c_stat = HIDDEN;
                    game_array->board_ptr[x].cells_ptr[y].display_char = ' ';

                }

            }

            break;

        case(HARD):

            //initialize game_array struct
            game_array = (struct game_board*)malloc(sizeof(struct game_board)*1);

            //check for malloc success
            if (game_array == NULL) {
                printf("Error: memory allocation failed.\n");
                free(game_array);
                exit(1);
            }

            //populate data members
            game_array->rows = 16;
            game_array->cols = 30;
            game_array->number_of_bombs = 99;
            game_array->g_stat = MENU;
            game_array->board_difficulty = game_difficulty;

            //allocate memory to store the game_cell array pointers
            game_array->board_ptr = (struct dynamic_array*)malloc(sizeof(struct dynamic_array)*game_array->cols);

            //check for malloc success
            if (game_array->board_ptr == NULL) {
                printf("Error: memory allocation failed.\n");
                free(game_array->board_ptr);
                free(game_array);
                exit(1);
            }

            //allocate the memory for the game_cell structs, and populate its data members.
            for(int x = 0; x < game_array->cols; x++) {

                game_array->board_ptr[x].cells_ptr = (struct game_cell*)malloc(sizeof(struct game_cell)*game_array->rows);
                
                //check for malloc success
                if (game_array->board_ptr[x].cells_ptr == NULL) {

                    printf("Error: memory allocation failed.\n");

                    for(int x = 0; x < game_array->cols; x++) {
                        free(game_array->board_ptr[x].cells_ptr);
                    }
                    free(game_array->board_ptr);
                    free(game_array);
                    exit(1);
                }

                for(int y = 0; y < game_array->rows; y++) {

                    game_array->board_ptr[x].cells_ptr[y].c_stat = HIDDEN;
                    game_array->board_ptr[x].cells_ptr[y].display_char = ' ';

                }

            }

            break;
    }

    return game_array;

}

/**
 * 
 * @brief prints the board to the screen, populated with the game data.
 * 
 * @param game_board_data the array that stores the data for the game that will be played.
 * 
 * @return returns nothing
 * 
 */
void print_board(struct game_board* game_board_arr) {

    switch(game_board_arr->board_difficulty) {
        case(SIMPLE):
            printf("game difficulty: SIMPLE\n\n");
            printf("     0   1   2   3   4\n");
            printf("   /-------------------\\");
            printf("\n 0 | %c | %c | %c | %c | %c |", game_board_arr->board_ptr[0].cells_ptr[0].display_char, game_board_arr->board_ptr[1].cells_ptr[0].display_char, game_board_arr->board_ptr[2].cells_ptr[0].display_char, game_board_arr->board_ptr[3].cells_ptr[0].display_char, game_board_arr->board_ptr[4].cells_ptr[0].display_char);
            printf("\n   |---|---|---|---|---|");
            printf("\n 1 | %c | %c | %c | %c | %c |", game_board_arr->board_ptr[0].cells_ptr[1].display_char, game_board_arr->board_ptr[1].cells_ptr[1].display_char, game_board_arr->board_ptr[2].cells_ptr[1].display_char, game_board_arr->board_ptr[3].cells_ptr[1].display_char, game_board_arr->board_ptr[4].cells_ptr[1].display_char);
            printf("\n   |---|---|---|---|---|");
            printf("\n 2 | %c | %c | %c | %c | %c |", game_board_arr->board_ptr[0].cells_ptr[2].display_char, game_board_arr->board_ptr[1].cells_ptr[2].display_char, game_board_arr->board_ptr[2].cells_ptr[2].display_char, game_board_arr->board_ptr[3].cells_ptr[2].display_char, game_board_arr->board_ptr[4].cells_ptr[2].display_char);
            printf("\n   |---|---|---|---|---|");
            printf("\n 3 | %c | %c | %c | %c | %c |", game_board_arr->board_ptr[0].cells_ptr[3].display_char, game_board_arr->board_ptr[1].cells_ptr[3].display_char, game_board_arr->board_ptr[2].cells_ptr[3].display_char, game_board_arr->board_ptr[3].cells_ptr[3].display_char, game_board_arr->board_ptr[4].cells_ptr[3].display_char);
            printf("\n   |---|---|---|---|---|");
            printf("\n 4 | %c | %c | %c | %c | %c |", game_board_arr->board_ptr[0].cells_ptr[4].display_char, game_board_arr->board_ptr[1].cells_ptr[4].display_char, game_board_arr->board_ptr[2].cells_ptr[4].display_char, game_board_arr->board_ptr[3].cells_ptr[4].display_char, game_board_arr->board_ptr[4].cells_ptr[4].display_char);
            printf("\n   \\-------------------/");

            break;

        case(EASY):
            printf("game difficulty: EASY\n");
            printf("     0   1   2   3   4   5   6   7   8\n");
            printf("   /-----------------------------------\\");
            printf("\n 0 | %c | %c | %c | %c | %c | %c | %c | %c | %c |", game_board_arr->board_ptr[0].cells_ptr[0].display_char, game_board_arr->board_ptr[1].cells_ptr[0].display_char, game_board_arr->board_ptr[2].cells_ptr[0].display_char, game_board_arr->board_ptr[3].cells_ptr[0].display_char, game_board_arr->board_ptr[4].cells_ptr[0].display_char, game_board_arr->board_ptr[5].cells_ptr[0].display_char, game_board_arr->board_ptr[6].cells_ptr[0].display_char, game_board_arr->board_ptr[7].cells_ptr[0].display_char, game_board_arr->board_ptr[8].cells_ptr[0].display_char);
            printf("\n   |---|---|---|---|---|---|---|---|---|");
            printf("\n 1 | %c | %c | %c | %c | %c | %c | %c | %c | %c |", game_board_arr->board_ptr[0].cells_ptr[1].display_char, game_board_arr->board_ptr[1].cells_ptr[1].display_char, game_board_arr->board_ptr[2].cells_ptr[1].display_char, game_board_arr->board_ptr[3].cells_ptr[1].display_char, game_board_arr->board_ptr[4].cells_ptr[1].display_char, game_board_arr->board_ptr[5].cells_ptr[1].display_char, game_board_arr->board_ptr[6].cells_ptr[1].display_char, game_board_arr->board_ptr[7].cells_ptr[1].display_char, game_board_arr->board_ptr[8].cells_ptr[1].display_char);
            printf("\n   |---|---|---|---|---|---|---|---|---|");
            printf("\n 2 | %c | %c | %c | %c | %c | %c | %c | %c | %c |", game_board_arr->board_ptr[0].cells_ptr[2].display_char, game_board_arr->board_ptr[1].cells_ptr[2].display_char, game_board_arr->board_ptr[2].cells_ptr[2].display_char, game_board_arr->board_ptr[3].cells_ptr[2].display_char, game_board_arr->board_ptr[4].cells_ptr[2].display_char, game_board_arr->board_ptr[5].cells_ptr[2].display_char, game_board_arr->board_ptr[6].cells_ptr[2].display_char, game_board_arr->board_ptr[7].cells_ptr[2].display_char, game_board_arr->board_ptr[8].cells_ptr[2].display_char);
            printf("\n   |---|---|---|---|---|---|---|---|---|");
            printf("\n 3 | %c | %c | %c | %c | %c | %c | %c | %c | %c |", game_board_arr->board_ptr[0].cells_ptr[3].display_char, game_board_arr->board_ptr[1].cells_ptr[3].display_char, game_board_arr->board_ptr[2].cells_ptr[3].display_char, game_board_arr->board_ptr[3].cells_ptr[3].display_char, game_board_arr->board_ptr[4].cells_ptr[3].display_char, game_board_arr->board_ptr[5].cells_ptr[3].display_char, game_board_arr->board_ptr[6].cells_ptr[3].display_char, game_board_arr->board_ptr[7].cells_ptr[3].display_char, game_board_arr->board_ptr[8].cells_ptr[3].display_char);
            printf("\n   |---|---|---|---|---|---|---|---|---|");
            printf("\n 4 | %c | %c | %c | %c | %c | %c | %c | %c | %c |", game_board_arr->board_ptr[0].cells_ptr[4].display_char, game_board_arr->board_ptr[1].cells_ptr[4].display_char, game_board_arr->board_ptr[2].cells_ptr[4].display_char, game_board_arr->board_ptr[3].cells_ptr[4].display_char, game_board_arr->board_ptr[4].cells_ptr[4].display_char, game_board_arr->board_ptr[5].cells_ptr[4].display_char, game_board_arr->board_ptr[6].cells_ptr[4].display_char, game_board_arr->board_ptr[7].cells_ptr[4].display_char, game_board_arr->board_ptr[8].cells_ptr[4].display_char);
            printf("\n   |---|---|---|---|---|---|---|---|---|");
            printf("\n 5 | %c | %c | %c | %c | %c | %c | %c | %c | %c |", game_board_arr->board_ptr[0].cells_ptr[5].display_char, game_board_arr->board_ptr[1].cells_ptr[5].display_char, game_board_arr->board_ptr[2].cells_ptr[5].display_char, game_board_arr->board_ptr[3].cells_ptr[5].display_char, game_board_arr->board_ptr[4].cells_ptr[5].display_char, game_board_arr->board_ptr[5].cells_ptr[5].display_char, game_board_arr->board_ptr[6].cells_ptr[5].display_char, game_board_arr->board_ptr[7].cells_ptr[5].display_char, game_board_arr->board_ptr[8].cells_ptr[5].display_char);
            printf("\n   |---|---|---|---|---|---|---|---|---|");
            printf("\n 6 | %c | %c | %c | %c | %c | %c | %c | %c | %c |", game_board_arr->board_ptr[0].cells_ptr[6].display_char, game_board_arr->board_ptr[1].cells_ptr[6].display_char, game_board_arr->board_ptr[2].cells_ptr[6].display_char, game_board_arr->board_ptr[3].cells_ptr[6].display_char, game_board_arr->board_ptr[4].cells_ptr[6].display_char, game_board_arr->board_ptr[5].cells_ptr[6].display_char, game_board_arr->board_ptr[6].cells_ptr[6].display_char, game_board_arr->board_ptr[7].cells_ptr[6].display_char, game_board_arr->board_ptr[8].cells_ptr[6].display_char);
            printf("\n   |---|---|---|---|---|---|---|---|---|");
            printf("\n 7 | %c | %c | %c | %c | %c | %c | %c | %c | %c |", game_board_arr->board_ptr[0].cells_ptr[7].display_char, game_board_arr->board_ptr[1].cells_ptr[7].display_char, game_board_arr->board_ptr[2].cells_ptr[7].display_char, game_board_arr->board_ptr[3].cells_ptr[7].display_char, game_board_arr->board_ptr[4].cells_ptr[7].display_char, game_board_arr->board_ptr[5].cells_ptr[7].display_char, game_board_arr->board_ptr[6].cells_ptr[7].display_char, game_board_arr->board_ptr[7].cells_ptr[7].display_char, game_board_arr->board_ptr[8].cells_ptr[7].display_char);
            printf("\n   |---|---|---|---|---|---|---|---|---|");
            printf("\n 8 | %c | %c | %c | %c | %c | %c | %c | %c | %c |", game_board_arr->board_ptr[0].cells_ptr[8].display_char, game_board_arr->board_ptr[1].cells_ptr[8].display_char, game_board_arr->board_ptr[2].cells_ptr[8].display_char, game_board_arr->board_ptr[3].cells_ptr[8].display_char, game_board_arr->board_ptr[4].cells_ptr[8].display_char, game_board_arr->board_ptr[5].cells_ptr[8].display_char, game_board_arr->board_ptr[6].cells_ptr[8].display_char, game_board_arr->board_ptr[7].cells_ptr[8].display_char, game_board_arr->board_ptr[8].cells_ptr[8].display_char);
            printf("\n   \\-----------------------------------/");
            break;

        case(MEDIUM):
            printf("game difficulty: MEDIUM\n");
            printf("     0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15\n");
            printf("   /---------------------------------------------------------------\\");
            printf("\n 0 | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c |", game_board_arr->board_ptr[0].cells_ptr[0].display_char, game_board_arr->board_ptr[1].cells_ptr[0].display_char, game_board_arr->board_ptr[2].cells_ptr[0].display_char, game_board_arr->board_ptr[3].cells_ptr[0].display_char, game_board_arr->board_ptr[4].cells_ptr[0].display_char, game_board_arr->board_ptr[5].cells_ptr[0].display_char, game_board_arr->board_ptr[6].cells_ptr[0].display_char, game_board_arr->board_ptr[7].cells_ptr[0].display_char, game_board_arr->board_ptr[8].cells_ptr[0].display_char, game_board_arr->board_ptr[9].cells_ptr[0].display_char, game_board_arr->board_ptr[10].cells_ptr[0].display_char, game_board_arr->board_ptr[11].cells_ptr[0].display_char, game_board_arr->board_ptr[12].cells_ptr[0].display_char, game_board_arr->board_ptr[13].cells_ptr[0].display_char, game_board_arr->board_ptr[14].cells_ptr[0].display_char, game_board_arr->board_ptr[15].cells_ptr[0].display_char);
            printf("\n   |---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|");
            printf("\n 1 | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c |", game_board_arr->board_ptr[0].cells_ptr[1].display_char, game_board_arr->board_ptr[1].cells_ptr[1].display_char, game_board_arr->board_ptr[2].cells_ptr[1].display_char, game_board_arr->board_ptr[3].cells_ptr[1].display_char, game_board_arr->board_ptr[4].cells_ptr[1].display_char, game_board_arr->board_ptr[5].cells_ptr[1].display_char, game_board_arr->board_ptr[6].cells_ptr[1].display_char, game_board_arr->board_ptr[7].cells_ptr[1].display_char, game_board_arr->board_ptr[8].cells_ptr[1].display_char, game_board_arr->board_ptr[9].cells_ptr[1].display_char, game_board_arr->board_ptr[10].cells_ptr[1].display_char, game_board_arr->board_ptr[11].cells_ptr[1].display_char, game_board_arr->board_ptr[12].cells_ptr[1].display_char, game_board_arr->board_ptr[13].cells_ptr[1].display_char, game_board_arr->board_ptr[14].cells_ptr[1].display_char, game_board_arr->board_ptr[15].cells_ptr[1].display_char);
            printf("\n   |---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|");
            printf("\n 2 | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c |", game_board_arr->board_ptr[0].cells_ptr[2].display_char, game_board_arr->board_ptr[1].cells_ptr[2].display_char, game_board_arr->board_ptr[2].cells_ptr[2].display_char, game_board_arr->board_ptr[3].cells_ptr[2].display_char, game_board_arr->board_ptr[4].cells_ptr[2].display_char, game_board_arr->board_ptr[5].cells_ptr[2].display_char, game_board_arr->board_ptr[6].cells_ptr[2].display_char, game_board_arr->board_ptr[7].cells_ptr[2].display_char, game_board_arr->board_ptr[8].cells_ptr[2].display_char, game_board_arr->board_ptr[9].cells_ptr[2].display_char, game_board_arr->board_ptr[10].cells_ptr[2].display_char, game_board_arr->board_ptr[11].cells_ptr[2].display_char, game_board_arr->board_ptr[12].cells_ptr[2].display_char, game_board_arr->board_ptr[13].cells_ptr[2].display_char, game_board_arr->board_ptr[14].cells_ptr[2].display_char, game_board_arr->board_ptr[15].cells_ptr[2].display_char);
            printf("\n   |---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|");
            printf("\n 3 | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c |", game_board_arr->board_ptr[0].cells_ptr[3].display_char, game_board_arr->board_ptr[1].cells_ptr[3].display_char, game_board_arr->board_ptr[2].cells_ptr[3].display_char, game_board_arr->board_ptr[3].cells_ptr[3].display_char, game_board_arr->board_ptr[4].cells_ptr[3].display_char, game_board_arr->board_ptr[5].cells_ptr[3].display_char, game_board_arr->board_ptr[6].cells_ptr[3].display_char, game_board_arr->board_ptr[7].cells_ptr[3].display_char, game_board_arr->board_ptr[8].cells_ptr[3].display_char, game_board_arr->board_ptr[9].cells_ptr[3].display_char, game_board_arr->board_ptr[10].cells_ptr[3].display_char, game_board_arr->board_ptr[11].cells_ptr[3].display_char, game_board_arr->board_ptr[12].cells_ptr[3].display_char, game_board_arr->board_ptr[13].cells_ptr[3].display_char, game_board_arr->board_ptr[14].cells_ptr[3].display_char, game_board_arr->board_ptr[15].cells_ptr[3].display_char);
            printf("\n   |---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|");
            printf("\n 4 | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c |", game_board_arr->board_ptr[0].cells_ptr[4].display_char, game_board_arr->board_ptr[1].cells_ptr[4].display_char, game_board_arr->board_ptr[2].cells_ptr[4].display_char, game_board_arr->board_ptr[3].cells_ptr[4].display_char, game_board_arr->board_ptr[4].cells_ptr[4].display_char, game_board_arr->board_ptr[5].cells_ptr[4].display_char, game_board_arr->board_ptr[6].cells_ptr[4].display_char, game_board_arr->board_ptr[7].cells_ptr[4].display_char, game_board_arr->board_ptr[8].cells_ptr[4].display_char, game_board_arr->board_ptr[9].cells_ptr[4].display_char, game_board_arr->board_ptr[10].cells_ptr[4].display_char, game_board_arr->board_ptr[11].cells_ptr[4].display_char, game_board_arr->board_ptr[12].cells_ptr[4].display_char, game_board_arr->board_ptr[13].cells_ptr[4].display_char, game_board_arr->board_ptr[14].cells_ptr[4].display_char, game_board_arr->board_ptr[15].cells_ptr[4].display_char);
            printf("\n   |---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|");
            printf("\n 5 | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c |", game_board_arr->board_ptr[0].cells_ptr[5].display_char, game_board_arr->board_ptr[1].cells_ptr[5].display_char, game_board_arr->board_ptr[2].cells_ptr[5].display_char, game_board_arr->board_ptr[3].cells_ptr[5].display_char, game_board_arr->board_ptr[4].cells_ptr[5].display_char, game_board_arr->board_ptr[5].cells_ptr[5].display_char, game_board_arr->board_ptr[6].cells_ptr[5].display_char, game_board_arr->board_ptr[7].cells_ptr[5].display_char, game_board_arr->board_ptr[8].cells_ptr[5].display_char, game_board_arr->board_ptr[9].cells_ptr[5].display_char, game_board_arr->board_ptr[10].cells_ptr[5].display_char, game_board_arr->board_ptr[11].cells_ptr[5].display_char, game_board_arr->board_ptr[12].cells_ptr[5].display_char, game_board_arr->board_ptr[13].cells_ptr[5].display_char, game_board_arr->board_ptr[14].cells_ptr[5].display_char, game_board_arr->board_ptr[15].cells_ptr[5].display_char);
            printf("\n   |---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|");
            printf("\n 6 | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c |", game_board_arr->board_ptr[0].cells_ptr[6].display_char, game_board_arr->board_ptr[1].cells_ptr[6].display_char, game_board_arr->board_ptr[2].cells_ptr[6].display_char, game_board_arr->board_ptr[3].cells_ptr[6].display_char, game_board_arr->board_ptr[4].cells_ptr[6].display_char, game_board_arr->board_ptr[5].cells_ptr[6].display_char, game_board_arr->board_ptr[6].cells_ptr[6].display_char, game_board_arr->board_ptr[7].cells_ptr[6].display_char, game_board_arr->board_ptr[8].cells_ptr[6].display_char, game_board_arr->board_ptr[9].cells_ptr[6].display_char, game_board_arr->board_ptr[10].cells_ptr[6].display_char, game_board_arr->board_ptr[11].cells_ptr[6].display_char, game_board_arr->board_ptr[12].cells_ptr[6].display_char, game_board_arr->board_ptr[13].cells_ptr[6].display_char, game_board_arr->board_ptr[14].cells_ptr[6].display_char, game_board_arr->board_ptr[15].cells_ptr[6].display_char);
            printf("\n   |---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|");
            printf("\n 7 | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c |", game_board_arr->board_ptr[0].cells_ptr[7].display_char, game_board_arr->board_ptr[1].cells_ptr[7].display_char, game_board_arr->board_ptr[2].cells_ptr[7].display_char, game_board_arr->board_ptr[3].cells_ptr[7].display_char, game_board_arr->board_ptr[4].cells_ptr[7].display_char, game_board_arr->board_ptr[5].cells_ptr[7].display_char, game_board_arr->board_ptr[6].cells_ptr[7].display_char, game_board_arr->board_ptr[7].cells_ptr[7].display_char, game_board_arr->board_ptr[8].cells_ptr[7].display_char, game_board_arr->board_ptr[9].cells_ptr[7].display_char, game_board_arr->board_ptr[10].cells_ptr[7].display_char, game_board_arr->board_ptr[11].cells_ptr[7].display_char, game_board_arr->board_ptr[12].cells_ptr[7].display_char, game_board_arr->board_ptr[13].cells_ptr[7].display_char, game_board_arr->board_ptr[14].cells_ptr[7].display_char, game_board_arr->board_ptr[15].cells_ptr[7].display_char);
            printf("\n   |---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|");
            printf("\n 8 | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c |", game_board_arr->board_ptr[0].cells_ptr[8].display_char, game_board_arr->board_ptr[1].cells_ptr[8].display_char, game_board_arr->board_ptr[2].cells_ptr[8].display_char, game_board_arr->board_ptr[3].cells_ptr[8].display_char, game_board_arr->board_ptr[4].cells_ptr[8].display_char, game_board_arr->board_ptr[5].cells_ptr[8].display_char, game_board_arr->board_ptr[6].cells_ptr[8].display_char, game_board_arr->board_ptr[7].cells_ptr[8].display_char, game_board_arr->board_ptr[8].cells_ptr[8].display_char, game_board_arr->board_ptr[9].cells_ptr[8].display_char, game_board_arr->board_ptr[10].cells_ptr[8].display_char, game_board_arr->board_ptr[11].cells_ptr[8].display_char, game_board_arr->board_ptr[12].cells_ptr[8].display_char, game_board_arr->board_ptr[13].cells_ptr[8].display_char, game_board_arr->board_ptr[14].cells_ptr[8].display_char, game_board_arr->board_ptr[15].cells_ptr[8].display_char);
            printf("\n   |---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|");
            printf("\n 9 | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c |", game_board_arr->board_ptr[0].cells_ptr[9].display_char, game_board_arr->board_ptr[1].cells_ptr[9].display_char, game_board_arr->board_ptr[2].cells_ptr[9].display_char, game_board_arr->board_ptr[3].cells_ptr[9].display_char, game_board_arr->board_ptr[4].cells_ptr[9].display_char, game_board_arr->board_ptr[5].cells_ptr[9].display_char, game_board_arr->board_ptr[6].cells_ptr[9].display_char, game_board_arr->board_ptr[7].cells_ptr[9].display_char, game_board_arr->board_ptr[8].cells_ptr[9].display_char, game_board_arr->board_ptr[9].cells_ptr[9].display_char, game_board_arr->board_ptr[10].cells_ptr[9].display_char, game_board_arr->board_ptr[11].cells_ptr[9].display_char, game_board_arr->board_ptr[12].cells_ptr[9].display_char, game_board_arr->board_ptr[13].cells_ptr[9].display_char, game_board_arr->board_ptr[14].cells_ptr[9].display_char, game_board_arr->board_ptr[15].cells_ptr[9].display_char);
            printf("\n   |---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|");
            printf("\n10 | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c |", game_board_arr->board_ptr[0].cells_ptr[10].display_char, game_board_arr->board_ptr[1].cells_ptr[10].display_char, game_board_arr->board_ptr[2].cells_ptr[10].display_char, game_board_arr->board_ptr[3].cells_ptr[10].display_char, game_board_arr->board_ptr[4].cells_ptr[10].display_char, game_board_arr->board_ptr[5].cells_ptr[10].display_char, game_board_arr->board_ptr[6].cells_ptr[10].display_char, game_board_arr->board_ptr[7].cells_ptr[10].display_char, game_board_arr->board_ptr[8].cells_ptr[10].display_char, game_board_arr->board_ptr[9].cells_ptr[10].display_char, game_board_arr->board_ptr[10].cells_ptr[10].display_char, game_board_arr->board_ptr[11].cells_ptr[10].display_char, game_board_arr->board_ptr[12].cells_ptr[10].display_char, game_board_arr->board_ptr[13].cells_ptr[10].display_char, game_board_arr->board_ptr[14].cells_ptr[10].display_char, game_board_arr->board_ptr[15].cells_ptr[10].display_char);
            printf("\n   |---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|");
            printf("\n11 | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c |", game_board_arr->board_ptr[0].cells_ptr[11].display_char, game_board_arr->board_ptr[1].cells_ptr[11].display_char, game_board_arr->board_ptr[2].cells_ptr[11].display_char, game_board_arr->board_ptr[3].cells_ptr[11].display_char, game_board_arr->board_ptr[4].cells_ptr[11].display_char, game_board_arr->board_ptr[5].cells_ptr[11].display_char, game_board_arr->board_ptr[6].cells_ptr[11].display_char, game_board_arr->board_ptr[7].cells_ptr[11].display_char, game_board_arr->board_ptr[8].cells_ptr[11].display_char, game_board_arr->board_ptr[9].cells_ptr[11].display_char, game_board_arr->board_ptr[10].cells_ptr[11].display_char, game_board_arr->board_ptr[11].cells_ptr[11].display_char, game_board_arr->board_ptr[12].cells_ptr[11].display_char, game_board_arr->board_ptr[13].cells_ptr[11].display_char, game_board_arr->board_ptr[14].cells_ptr[11].display_char, game_board_arr->board_ptr[15].cells_ptr[11].display_char);
            printf("\n   |---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|");
            printf("\n12 | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c |", game_board_arr->board_ptr[0].cells_ptr[12].display_char, game_board_arr->board_ptr[1].cells_ptr[12].display_char, game_board_arr->board_ptr[2].cells_ptr[12].display_char, game_board_arr->board_ptr[3].cells_ptr[12].display_char, game_board_arr->board_ptr[4].cells_ptr[12].display_char, game_board_arr->board_ptr[5].cells_ptr[12].display_char, game_board_arr->board_ptr[6].cells_ptr[12].display_char, game_board_arr->board_ptr[7].cells_ptr[12].display_char, game_board_arr->board_ptr[8].cells_ptr[12].display_char, game_board_arr->board_ptr[9].cells_ptr[12].display_char, game_board_arr->board_ptr[10].cells_ptr[12].display_char, game_board_arr->board_ptr[11].cells_ptr[12].display_char, game_board_arr->board_ptr[12].cells_ptr[12].display_char, game_board_arr->board_ptr[13].cells_ptr[12].display_char, game_board_arr->board_ptr[14].cells_ptr[12].display_char, game_board_arr->board_ptr[15].cells_ptr[12].display_char);
            printf("\n   |---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|");
            printf("\n13 | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c |", game_board_arr->board_ptr[0].cells_ptr[13].display_char, game_board_arr->board_ptr[1].cells_ptr[13].display_char, game_board_arr->board_ptr[2].cells_ptr[13].display_char, game_board_arr->board_ptr[3].cells_ptr[13].display_char, game_board_arr->board_ptr[4].cells_ptr[13].display_char, game_board_arr->board_ptr[5].cells_ptr[13].display_char, game_board_arr->board_ptr[6].cells_ptr[13].display_char, game_board_arr->board_ptr[7].cells_ptr[13].display_char, game_board_arr->board_ptr[8].cells_ptr[13].display_char, game_board_arr->board_ptr[9].cells_ptr[13].display_char, game_board_arr->board_ptr[10].cells_ptr[13].display_char, game_board_arr->board_ptr[11].cells_ptr[13].display_char, game_board_arr->board_ptr[12].cells_ptr[13].display_char, game_board_arr->board_ptr[13].cells_ptr[13].display_char, game_board_arr->board_ptr[14].cells_ptr[13].display_char, game_board_arr->board_ptr[15].cells_ptr[13].display_char);
            printf("\n   |---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|");
            printf("\n14 | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c |", game_board_arr->board_ptr[0].cells_ptr[14].display_char, game_board_arr->board_ptr[1].cells_ptr[14].display_char, game_board_arr->board_ptr[2].cells_ptr[14].display_char, game_board_arr->board_ptr[3].cells_ptr[14].display_char, game_board_arr->board_ptr[4].cells_ptr[14].display_char, game_board_arr->board_ptr[5].cells_ptr[14].display_char, game_board_arr->board_ptr[6].cells_ptr[14].display_char, game_board_arr->board_ptr[7].cells_ptr[14].display_char, game_board_arr->board_ptr[8].cells_ptr[14].display_char, game_board_arr->board_ptr[9].cells_ptr[14].display_char, game_board_arr->board_ptr[10].cells_ptr[14].display_char, game_board_arr->board_ptr[11].cells_ptr[14].display_char, game_board_arr->board_ptr[12].cells_ptr[14].display_char, game_board_arr->board_ptr[13].cells_ptr[14].display_char, game_board_arr->board_ptr[14].cells_ptr[14].display_char, game_board_arr->board_ptr[15].cells_ptr[14].display_char);
            printf("\n   |---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|");
            printf("\n15 | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c |", game_board_arr->board_ptr[0].cells_ptr[15].display_char, game_board_arr->board_ptr[1].cells_ptr[15].display_char, game_board_arr->board_ptr[2].cells_ptr[15].display_char, game_board_arr->board_ptr[3].cells_ptr[15].display_char, game_board_arr->board_ptr[4].cells_ptr[15].display_char, game_board_arr->board_ptr[5].cells_ptr[15].display_char, game_board_arr->board_ptr[6].cells_ptr[15].display_char, game_board_arr->board_ptr[7].cells_ptr[15].display_char, game_board_arr->board_ptr[8].cells_ptr[15].display_char, game_board_arr->board_ptr[9].cells_ptr[15].display_char, game_board_arr->board_ptr[10].cells_ptr[15].display_char, game_board_arr->board_ptr[11].cells_ptr[15].display_char, game_board_arr->board_ptr[12].cells_ptr[15].display_char, game_board_arr->board_ptr[13].cells_ptr[15].display_char, game_board_arr->board_ptr[14].cells_ptr[15].display_char, game_board_arr->board_ptr[15].cells_ptr[15].display_char);
            printf("\n   \\---------------------------------------------------------------/");
            break;

        case(HARD):
            printf("game difficulty: HARD\n");
            printf("     0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25  26  27  28  29\n");
            printf("   /-----------------------------------------------------------------------------------------------------------------------\\");
            printf("\n 0 | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c |", game_board_arr->board_ptr[0].cells_ptr[0].display_char, game_board_arr->board_ptr[1].cells_ptr[0].display_char, game_board_arr->board_ptr[2].cells_ptr[0].display_char, game_board_arr->board_ptr[3].cells_ptr[0].display_char, game_board_arr->board_ptr[4].cells_ptr[0].display_char, game_board_arr->board_ptr[5].cells_ptr[0].display_char, game_board_arr->board_ptr[6].cells_ptr[0].display_char, game_board_arr->board_ptr[7].cells_ptr[0].display_char, game_board_arr->board_ptr[8].cells_ptr[0].display_char, game_board_arr->board_ptr[9].cells_ptr[0].display_char, game_board_arr->board_ptr[10].cells_ptr[0].display_char, game_board_arr->board_ptr[11].cells_ptr[0].display_char, game_board_arr->board_ptr[12].cells_ptr[0].display_char, game_board_arr->board_ptr[13].cells_ptr[0].display_char, game_board_arr->board_ptr[14].cells_ptr[0].display_char, game_board_arr->board_ptr[15].cells_ptr[0].display_char, game_board_arr->board_ptr[16].cells_ptr[0].display_char, game_board_arr->board_ptr[17].cells_ptr[0].display_char, game_board_arr->board_ptr[18].cells_ptr[0].display_char, game_board_arr->board_ptr[19].cells_ptr[0].display_char, game_board_arr->board_ptr[20].cells_ptr[0].display_char, game_board_arr->board_ptr[21].cells_ptr[0].display_char, game_board_arr->board_ptr[22].cells_ptr[0].display_char, game_board_arr->board_ptr[23].cells_ptr[0].display_char, game_board_arr->board_ptr[24].cells_ptr[0].display_char, game_board_arr->board_ptr[25].cells_ptr[0].display_char, game_board_arr->board_ptr[26].cells_ptr[0].display_char, game_board_arr->board_ptr[27].cells_ptr[0].display_char, game_board_arr->board_ptr[28].cells_ptr[0].display_char, game_board_arr->board_ptr[29].cells_ptr[0].display_char);
            printf("\n   |---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|");
            printf("\n 1 | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c |", game_board_arr->board_ptr[0].cells_ptr[1].display_char, game_board_arr->board_ptr[1].cells_ptr[1].display_char, game_board_arr->board_ptr[2].cells_ptr[1].display_char, game_board_arr->board_ptr[3].cells_ptr[1].display_char, game_board_arr->board_ptr[4].cells_ptr[1].display_char, game_board_arr->board_ptr[5].cells_ptr[1].display_char, game_board_arr->board_ptr[6].cells_ptr[1].display_char, game_board_arr->board_ptr[7].cells_ptr[1].display_char, game_board_arr->board_ptr[8].cells_ptr[1].display_char, game_board_arr->board_ptr[9].cells_ptr[1].display_char, game_board_arr->board_ptr[10].cells_ptr[1].display_char, game_board_arr->board_ptr[11].cells_ptr[1].display_char, game_board_arr->board_ptr[12].cells_ptr[1].display_char, game_board_arr->board_ptr[13].cells_ptr[1].display_char, game_board_arr->board_ptr[14].cells_ptr[1].display_char, game_board_arr->board_ptr[15].cells_ptr[1].display_char, game_board_arr->board_ptr[16].cells_ptr[1].display_char, game_board_arr->board_ptr[17].cells_ptr[1].display_char, game_board_arr->board_ptr[18].cells_ptr[1].display_char, game_board_arr->board_ptr[19].cells_ptr[1].display_char, game_board_arr->board_ptr[20].cells_ptr[1].display_char, game_board_arr->board_ptr[21].cells_ptr[1].display_char, game_board_arr->board_ptr[22].cells_ptr[1].display_char, game_board_arr->board_ptr[23].cells_ptr[1].display_char, game_board_arr->board_ptr[24].cells_ptr[1].display_char, game_board_arr->board_ptr[25].cells_ptr[1].display_char, game_board_arr->board_ptr[26].cells_ptr[1].display_char, game_board_arr->board_ptr[27].cells_ptr[1].display_char, game_board_arr->board_ptr[28].cells_ptr[1].display_char, game_board_arr->board_ptr[29].cells_ptr[1].display_char);
            printf("\n   |---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|");
            printf("\n 2 | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c |", game_board_arr->board_ptr[0].cells_ptr[2].display_char, game_board_arr->board_ptr[1].cells_ptr[2].display_char, game_board_arr->board_ptr[2].cells_ptr[2].display_char, game_board_arr->board_ptr[3].cells_ptr[2].display_char, game_board_arr->board_ptr[4].cells_ptr[2].display_char, game_board_arr->board_ptr[5].cells_ptr[2].display_char, game_board_arr->board_ptr[6].cells_ptr[2].display_char, game_board_arr->board_ptr[7].cells_ptr[2].display_char, game_board_arr->board_ptr[8].cells_ptr[2].display_char, game_board_arr->board_ptr[9].cells_ptr[2].display_char, game_board_arr->board_ptr[10].cells_ptr[2].display_char, game_board_arr->board_ptr[11].cells_ptr[2].display_char, game_board_arr->board_ptr[12].cells_ptr[2].display_char, game_board_arr->board_ptr[13].cells_ptr[2].display_char, game_board_arr->board_ptr[14].cells_ptr[2].display_char, game_board_arr->board_ptr[15].cells_ptr[2].display_char, game_board_arr->board_ptr[16].cells_ptr[2].display_char, game_board_arr->board_ptr[17].cells_ptr[2].display_char, game_board_arr->board_ptr[18].cells_ptr[2].display_char, game_board_arr->board_ptr[19].cells_ptr[2].display_char, game_board_arr->board_ptr[20].cells_ptr[2].display_char, game_board_arr->board_ptr[21].cells_ptr[2].display_char, game_board_arr->board_ptr[22].cells_ptr[2].display_char, game_board_arr->board_ptr[23].cells_ptr[2].display_char, game_board_arr->board_ptr[24].cells_ptr[2].display_char, game_board_arr->board_ptr[25].cells_ptr[2].display_char, game_board_arr->board_ptr[26].cells_ptr[2].display_char, game_board_arr->board_ptr[27].cells_ptr[2].display_char, game_board_arr->board_ptr[28].cells_ptr[2].display_char, game_board_arr->board_ptr[29].cells_ptr[2].display_char);
            printf("\n   |---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|");
            printf("\n 3 | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c |", game_board_arr->board_ptr[0].cells_ptr[3].display_char, game_board_arr->board_ptr[1].cells_ptr[3].display_char, game_board_arr->board_ptr[2].cells_ptr[3].display_char, game_board_arr->board_ptr[3].cells_ptr[3].display_char, game_board_arr->board_ptr[4].cells_ptr[3].display_char, game_board_arr->board_ptr[5].cells_ptr[3].display_char, game_board_arr->board_ptr[6].cells_ptr[3].display_char, game_board_arr->board_ptr[7].cells_ptr[3].display_char, game_board_arr->board_ptr[8].cells_ptr[3].display_char, game_board_arr->board_ptr[9].cells_ptr[3].display_char, game_board_arr->board_ptr[10].cells_ptr[3].display_char, game_board_arr->board_ptr[11].cells_ptr[3].display_char, game_board_arr->board_ptr[12].cells_ptr[3].display_char, game_board_arr->board_ptr[13].cells_ptr[3].display_char, game_board_arr->board_ptr[14].cells_ptr[3].display_char, game_board_arr->board_ptr[15].cells_ptr[3].display_char, game_board_arr->board_ptr[16].cells_ptr[3].display_char, game_board_arr->board_ptr[17].cells_ptr[3].display_char, game_board_arr->board_ptr[18].cells_ptr[3].display_char, game_board_arr->board_ptr[19].cells_ptr[3].display_char, game_board_arr->board_ptr[20].cells_ptr[3].display_char, game_board_arr->board_ptr[21].cells_ptr[3].display_char, game_board_arr->board_ptr[22].cells_ptr[3].display_char, game_board_arr->board_ptr[23].cells_ptr[3].display_char, game_board_arr->board_ptr[24].cells_ptr[3].display_char, game_board_arr->board_ptr[25].cells_ptr[3].display_char, game_board_arr->board_ptr[26].cells_ptr[3].display_char, game_board_arr->board_ptr[27].cells_ptr[3].display_char, game_board_arr->board_ptr[28].cells_ptr[3].display_char, game_board_arr->board_ptr[29].cells_ptr[3].display_char);
            printf("\n   |---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|");
            printf("\n 4 | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c |", game_board_arr->board_ptr[0].cells_ptr[4].display_char, game_board_arr->board_ptr[1].cells_ptr[4].display_char, game_board_arr->board_ptr[2].cells_ptr[4].display_char, game_board_arr->board_ptr[3].cells_ptr[4].display_char, game_board_arr->board_ptr[4].cells_ptr[4].display_char, game_board_arr->board_ptr[5].cells_ptr[4].display_char, game_board_arr->board_ptr[6].cells_ptr[4].display_char, game_board_arr->board_ptr[7].cells_ptr[4].display_char, game_board_arr->board_ptr[8].cells_ptr[4].display_char, game_board_arr->board_ptr[9].cells_ptr[4].display_char, game_board_arr->board_ptr[10].cells_ptr[4].display_char, game_board_arr->board_ptr[11].cells_ptr[4].display_char, game_board_arr->board_ptr[12].cells_ptr[4].display_char, game_board_arr->board_ptr[13].cells_ptr[4].display_char, game_board_arr->board_ptr[14].cells_ptr[4].display_char, game_board_arr->board_ptr[15].cells_ptr[4].display_char, game_board_arr->board_ptr[16].cells_ptr[4].display_char, game_board_arr->board_ptr[17].cells_ptr[4].display_char, game_board_arr->board_ptr[18].cells_ptr[4].display_char, game_board_arr->board_ptr[19].cells_ptr[4].display_char, game_board_arr->board_ptr[20].cells_ptr[4].display_char, game_board_arr->board_ptr[21].cells_ptr[4].display_char, game_board_arr->board_ptr[22].cells_ptr[4].display_char, game_board_arr->board_ptr[23].cells_ptr[4].display_char, game_board_arr->board_ptr[24].cells_ptr[4].display_char, game_board_arr->board_ptr[25].cells_ptr[4].display_char, game_board_arr->board_ptr[26].cells_ptr[4].display_char, game_board_arr->board_ptr[27].cells_ptr[4].display_char, game_board_arr->board_ptr[28].cells_ptr[4].display_char, game_board_arr->board_ptr[29].cells_ptr[4].display_char);
            printf("\n   |---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|");
            printf("\n 5 | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c |", game_board_arr->board_ptr[0].cells_ptr[5].display_char, game_board_arr->board_ptr[1].cells_ptr[5].display_char, game_board_arr->board_ptr[2].cells_ptr[5].display_char, game_board_arr->board_ptr[3].cells_ptr[5].display_char, game_board_arr->board_ptr[4].cells_ptr[5].display_char, game_board_arr->board_ptr[5].cells_ptr[5].display_char, game_board_arr->board_ptr[6].cells_ptr[5].display_char, game_board_arr->board_ptr[7].cells_ptr[5].display_char, game_board_arr->board_ptr[8].cells_ptr[5].display_char, game_board_arr->board_ptr[9].cells_ptr[5].display_char, game_board_arr->board_ptr[10].cells_ptr[5].display_char, game_board_arr->board_ptr[11].cells_ptr[5].display_char, game_board_arr->board_ptr[12].cells_ptr[5].display_char, game_board_arr->board_ptr[13].cells_ptr[5].display_char, game_board_arr->board_ptr[14].cells_ptr[5].display_char, game_board_arr->board_ptr[15].cells_ptr[5].display_char, game_board_arr->board_ptr[16].cells_ptr[5].display_char, game_board_arr->board_ptr[17].cells_ptr[5].display_char, game_board_arr->board_ptr[18].cells_ptr[5].display_char, game_board_arr->board_ptr[19].cells_ptr[5].display_char, game_board_arr->board_ptr[20].cells_ptr[5].display_char, game_board_arr->board_ptr[21].cells_ptr[5].display_char, game_board_arr->board_ptr[22].cells_ptr[5].display_char, game_board_arr->board_ptr[23].cells_ptr[5].display_char, game_board_arr->board_ptr[24].cells_ptr[5].display_char, game_board_arr->board_ptr[25].cells_ptr[5].display_char, game_board_arr->board_ptr[26].cells_ptr[5].display_char, game_board_arr->board_ptr[27].cells_ptr[5].display_char, game_board_arr->board_ptr[28].cells_ptr[5].display_char, game_board_arr->board_ptr[29].cells_ptr[5].display_char);
            printf("\n   |---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|");
            printf("\n 6 | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c |", game_board_arr->board_ptr[0].cells_ptr[6].display_char, game_board_arr->board_ptr[1].cells_ptr[6].display_char, game_board_arr->board_ptr[2].cells_ptr[6].display_char, game_board_arr->board_ptr[3].cells_ptr[6].display_char, game_board_arr->board_ptr[4].cells_ptr[6].display_char, game_board_arr->board_ptr[5].cells_ptr[6].display_char, game_board_arr->board_ptr[6].cells_ptr[6].display_char, game_board_arr->board_ptr[7].cells_ptr[6].display_char, game_board_arr->board_ptr[8].cells_ptr[6].display_char, game_board_arr->board_ptr[9].cells_ptr[6].display_char, game_board_arr->board_ptr[10].cells_ptr[6].display_char, game_board_arr->board_ptr[11].cells_ptr[6].display_char, game_board_arr->board_ptr[12].cells_ptr[6].display_char, game_board_arr->board_ptr[13].cells_ptr[6].display_char, game_board_arr->board_ptr[14].cells_ptr[6].display_char, game_board_arr->board_ptr[15].cells_ptr[6].display_char, game_board_arr->board_ptr[16].cells_ptr[6].display_char, game_board_arr->board_ptr[17].cells_ptr[6].display_char, game_board_arr->board_ptr[18].cells_ptr[6].display_char, game_board_arr->board_ptr[19].cells_ptr[6].display_char, game_board_arr->board_ptr[20].cells_ptr[6].display_char, game_board_arr->board_ptr[21].cells_ptr[6].display_char, game_board_arr->board_ptr[22].cells_ptr[6].display_char, game_board_arr->board_ptr[23].cells_ptr[6].display_char, game_board_arr->board_ptr[24].cells_ptr[6].display_char, game_board_arr->board_ptr[25].cells_ptr[6].display_char, game_board_arr->board_ptr[26].cells_ptr[6].display_char, game_board_arr->board_ptr[27].cells_ptr[6].display_char, game_board_arr->board_ptr[28].cells_ptr[6].display_char, game_board_arr->board_ptr[29].cells_ptr[6].display_char);
            printf("\n   |---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|");
            printf("\n 7 | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c |", game_board_arr->board_ptr[0].cells_ptr[7].display_char, game_board_arr->board_ptr[1].cells_ptr[7].display_char, game_board_arr->board_ptr[2].cells_ptr[7].display_char, game_board_arr->board_ptr[3].cells_ptr[7].display_char, game_board_arr->board_ptr[4].cells_ptr[7].display_char, game_board_arr->board_ptr[5].cells_ptr[7].display_char, game_board_arr->board_ptr[6].cells_ptr[7].display_char, game_board_arr->board_ptr[7].cells_ptr[7].display_char, game_board_arr->board_ptr[8].cells_ptr[7].display_char, game_board_arr->board_ptr[9].cells_ptr[7].display_char, game_board_arr->board_ptr[10].cells_ptr[7].display_char, game_board_arr->board_ptr[11].cells_ptr[7].display_char, game_board_arr->board_ptr[12].cells_ptr[7].display_char, game_board_arr->board_ptr[13].cells_ptr[7].display_char, game_board_arr->board_ptr[14].cells_ptr[7].display_char, game_board_arr->board_ptr[15].cells_ptr[7].display_char, game_board_arr->board_ptr[16].cells_ptr[7].display_char, game_board_arr->board_ptr[17].cells_ptr[7].display_char, game_board_arr->board_ptr[18].cells_ptr[7].display_char, game_board_arr->board_ptr[19].cells_ptr[7].display_char, game_board_arr->board_ptr[20].cells_ptr[7].display_char, game_board_arr->board_ptr[21].cells_ptr[7].display_char, game_board_arr->board_ptr[22].cells_ptr[7].display_char, game_board_arr->board_ptr[23].cells_ptr[7].display_char, game_board_arr->board_ptr[24].cells_ptr[7].display_char, game_board_arr->board_ptr[25].cells_ptr[7].display_char, game_board_arr->board_ptr[26].cells_ptr[7].display_char, game_board_arr->board_ptr[27].cells_ptr[7].display_char, game_board_arr->board_ptr[28].cells_ptr[7].display_char, game_board_arr->board_ptr[29].cells_ptr[7].display_char);
            printf("\n   |---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|");
            printf("\n 8 | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c |", game_board_arr->board_ptr[0].cells_ptr[8].display_char, game_board_arr->board_ptr[1].cells_ptr[8].display_char, game_board_arr->board_ptr[2].cells_ptr[8].display_char, game_board_arr->board_ptr[3].cells_ptr[8].display_char, game_board_arr->board_ptr[4].cells_ptr[8].display_char, game_board_arr->board_ptr[5].cells_ptr[8].display_char, game_board_arr->board_ptr[6].cells_ptr[8].display_char, game_board_arr->board_ptr[7].cells_ptr[8].display_char, game_board_arr->board_ptr[8].cells_ptr[8].display_char, game_board_arr->board_ptr[9].cells_ptr[8].display_char, game_board_arr->board_ptr[10].cells_ptr[8].display_char, game_board_arr->board_ptr[11].cells_ptr[8].display_char, game_board_arr->board_ptr[12].cells_ptr[8].display_char, game_board_arr->board_ptr[13].cells_ptr[8].display_char, game_board_arr->board_ptr[14].cells_ptr[8].display_char, game_board_arr->board_ptr[15].cells_ptr[8].display_char, game_board_arr->board_ptr[16].cells_ptr[8].display_char, game_board_arr->board_ptr[17].cells_ptr[8].display_char, game_board_arr->board_ptr[18].cells_ptr[8].display_char, game_board_arr->board_ptr[19].cells_ptr[8].display_char, game_board_arr->board_ptr[20].cells_ptr[8].display_char, game_board_arr->board_ptr[21].cells_ptr[8].display_char, game_board_arr->board_ptr[22].cells_ptr[8].display_char, game_board_arr->board_ptr[23].cells_ptr[8].display_char, game_board_arr->board_ptr[24].cells_ptr[8].display_char, game_board_arr->board_ptr[25].cells_ptr[8].display_char, game_board_arr->board_ptr[26].cells_ptr[8].display_char, game_board_arr->board_ptr[27].cells_ptr[8].display_char, game_board_arr->board_ptr[28].cells_ptr[8].display_char, game_board_arr->board_ptr[29].cells_ptr[8].display_char);
            printf("\n   |---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|");
            printf("\n 9 | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c |", game_board_arr->board_ptr[0].cells_ptr[9].display_char, game_board_arr->board_ptr[1].cells_ptr[9].display_char, game_board_arr->board_ptr[2].cells_ptr[9].display_char, game_board_arr->board_ptr[3].cells_ptr[9].display_char, game_board_arr->board_ptr[4].cells_ptr[9].display_char, game_board_arr->board_ptr[5].cells_ptr[9].display_char, game_board_arr->board_ptr[6].cells_ptr[9].display_char, game_board_arr->board_ptr[7].cells_ptr[9].display_char, game_board_arr->board_ptr[8].cells_ptr[9].display_char, game_board_arr->board_ptr[9].cells_ptr[9].display_char, game_board_arr->board_ptr[10].cells_ptr[9].display_char, game_board_arr->board_ptr[11].cells_ptr[9].display_char, game_board_arr->board_ptr[12].cells_ptr[9].display_char, game_board_arr->board_ptr[13].cells_ptr[9].display_char, game_board_arr->board_ptr[14].cells_ptr[9].display_char, game_board_arr->board_ptr[15].cells_ptr[9].display_char, game_board_arr->board_ptr[16].cells_ptr[9].display_char, game_board_arr->board_ptr[17].cells_ptr[9].display_char, game_board_arr->board_ptr[18].cells_ptr[9].display_char, game_board_arr->board_ptr[19].cells_ptr[9].display_char, game_board_arr->board_ptr[20].cells_ptr[9].display_char, game_board_arr->board_ptr[21].cells_ptr[9].display_char, game_board_arr->board_ptr[22].cells_ptr[9].display_char, game_board_arr->board_ptr[23].cells_ptr[9].display_char, game_board_arr->board_ptr[24].cells_ptr[9].display_char, game_board_arr->board_ptr[25].cells_ptr[9].display_char, game_board_arr->board_ptr[26].cells_ptr[9].display_char, game_board_arr->board_ptr[27].cells_ptr[9].display_char, game_board_arr->board_ptr[28].cells_ptr[9].display_char, game_board_arr->board_ptr[29].cells_ptr[9].display_char);
            printf("\n   |---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|");
            printf("\n10 | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c |", game_board_arr->board_ptr[0].cells_ptr[10].display_char, game_board_arr->board_ptr[1].cells_ptr[10].display_char, game_board_arr->board_ptr[2].cells_ptr[10].display_char, game_board_arr->board_ptr[3].cells_ptr[10].display_char, game_board_arr->board_ptr[4].cells_ptr[10].display_char, game_board_arr->board_ptr[5].cells_ptr[10].display_char, game_board_arr->board_ptr[6].cells_ptr[10].display_char, game_board_arr->board_ptr[7].cells_ptr[10].display_char, game_board_arr->board_ptr[8].cells_ptr[10].display_char, game_board_arr->board_ptr[9].cells_ptr[10].display_char, game_board_arr->board_ptr[10].cells_ptr[10].display_char, game_board_arr->board_ptr[11].cells_ptr[10].display_char, game_board_arr->board_ptr[12].cells_ptr[10].display_char, game_board_arr->board_ptr[13].cells_ptr[10].display_char, game_board_arr->board_ptr[14].cells_ptr[10].display_char, game_board_arr->board_ptr[15].cells_ptr[10].display_char, game_board_arr->board_ptr[16].cells_ptr[10].display_char, game_board_arr->board_ptr[17].cells_ptr[10].display_char, game_board_arr->board_ptr[18].cells_ptr[10].display_char, game_board_arr->board_ptr[19].cells_ptr[10].display_char, game_board_arr->board_ptr[20].cells_ptr[10].display_char, game_board_arr->board_ptr[21].cells_ptr[10].display_char, game_board_arr->board_ptr[22].cells_ptr[10].display_char, game_board_arr->board_ptr[23].cells_ptr[10].display_char, game_board_arr->board_ptr[24].cells_ptr[10].display_char, game_board_arr->board_ptr[25].cells_ptr[10].display_char, game_board_arr->board_ptr[26].cells_ptr[10].display_char, game_board_arr->board_ptr[27].cells_ptr[10].display_char, game_board_arr->board_ptr[28].cells_ptr[10].display_char, game_board_arr->board_ptr[29].cells_ptr[10].display_char);
            printf("\n   |---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|");
            printf("\n11 | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c |", game_board_arr->board_ptr[0].cells_ptr[11].display_char, game_board_arr->board_ptr[1].cells_ptr[11].display_char, game_board_arr->board_ptr[2].cells_ptr[11].display_char, game_board_arr->board_ptr[3].cells_ptr[11].display_char, game_board_arr->board_ptr[4].cells_ptr[11].display_char, game_board_arr->board_ptr[5].cells_ptr[11].display_char, game_board_arr->board_ptr[6].cells_ptr[11].display_char, game_board_arr->board_ptr[7].cells_ptr[11].display_char, game_board_arr->board_ptr[8].cells_ptr[11].display_char, game_board_arr->board_ptr[9].cells_ptr[11].display_char, game_board_arr->board_ptr[10].cells_ptr[11].display_char, game_board_arr->board_ptr[11].cells_ptr[11].display_char, game_board_arr->board_ptr[12].cells_ptr[11].display_char, game_board_arr->board_ptr[13].cells_ptr[11].display_char, game_board_arr->board_ptr[14].cells_ptr[11].display_char, game_board_arr->board_ptr[15].cells_ptr[11].display_char, game_board_arr->board_ptr[16].cells_ptr[11].display_char, game_board_arr->board_ptr[17].cells_ptr[11].display_char, game_board_arr->board_ptr[18].cells_ptr[11].display_char, game_board_arr->board_ptr[19].cells_ptr[11].display_char, game_board_arr->board_ptr[20].cells_ptr[11].display_char, game_board_arr->board_ptr[21].cells_ptr[11].display_char, game_board_arr->board_ptr[22].cells_ptr[11].display_char, game_board_arr->board_ptr[23].cells_ptr[11].display_char, game_board_arr->board_ptr[24].cells_ptr[11].display_char, game_board_arr->board_ptr[25].cells_ptr[11].display_char, game_board_arr->board_ptr[26].cells_ptr[11].display_char, game_board_arr->board_ptr[27].cells_ptr[11].display_char, game_board_arr->board_ptr[28].cells_ptr[11].display_char, game_board_arr->board_ptr[29].cells_ptr[11].display_char);
            printf("\n   |---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|");
            printf("\n12 | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c |", game_board_arr->board_ptr[0].cells_ptr[12].display_char, game_board_arr->board_ptr[1].cells_ptr[12].display_char, game_board_arr->board_ptr[2].cells_ptr[12].display_char, game_board_arr->board_ptr[3].cells_ptr[12].display_char, game_board_arr->board_ptr[4].cells_ptr[12].display_char, game_board_arr->board_ptr[5].cells_ptr[12].display_char, game_board_arr->board_ptr[6].cells_ptr[12].display_char, game_board_arr->board_ptr[7].cells_ptr[12].display_char, game_board_arr->board_ptr[8].cells_ptr[12].display_char, game_board_arr->board_ptr[9].cells_ptr[12].display_char, game_board_arr->board_ptr[10].cells_ptr[12].display_char, game_board_arr->board_ptr[11].cells_ptr[12].display_char, game_board_arr->board_ptr[12].cells_ptr[12].display_char, game_board_arr->board_ptr[13].cells_ptr[12].display_char, game_board_arr->board_ptr[14].cells_ptr[12].display_char, game_board_arr->board_ptr[15].cells_ptr[12].display_char, game_board_arr->board_ptr[16].cells_ptr[12].display_char, game_board_arr->board_ptr[17].cells_ptr[12].display_char, game_board_arr->board_ptr[18].cells_ptr[12].display_char, game_board_arr->board_ptr[19].cells_ptr[12].display_char, game_board_arr->board_ptr[20].cells_ptr[12].display_char, game_board_arr->board_ptr[21].cells_ptr[12].display_char, game_board_arr->board_ptr[22].cells_ptr[12].display_char, game_board_arr->board_ptr[23].cells_ptr[12].display_char, game_board_arr->board_ptr[24].cells_ptr[12].display_char, game_board_arr->board_ptr[25].cells_ptr[12].display_char, game_board_arr->board_ptr[26].cells_ptr[12].display_char, game_board_arr->board_ptr[27].cells_ptr[12].display_char, game_board_arr->board_ptr[28].cells_ptr[12].display_char, game_board_arr->board_ptr[29].cells_ptr[12].display_char);
            printf("\n   |---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|");
            printf("\n13 | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c |", game_board_arr->board_ptr[0].cells_ptr[13].display_char, game_board_arr->board_ptr[1].cells_ptr[13].display_char, game_board_arr->board_ptr[2].cells_ptr[13].display_char, game_board_arr->board_ptr[3].cells_ptr[13].display_char, game_board_arr->board_ptr[4].cells_ptr[13].display_char, game_board_arr->board_ptr[5].cells_ptr[13].display_char, game_board_arr->board_ptr[6].cells_ptr[13].display_char, game_board_arr->board_ptr[7].cells_ptr[13].display_char, game_board_arr->board_ptr[8].cells_ptr[13].display_char, game_board_arr->board_ptr[9].cells_ptr[13].display_char, game_board_arr->board_ptr[10].cells_ptr[13].display_char, game_board_arr->board_ptr[11].cells_ptr[13].display_char, game_board_arr->board_ptr[12].cells_ptr[13].display_char, game_board_arr->board_ptr[13].cells_ptr[13].display_char, game_board_arr->board_ptr[14].cells_ptr[13].display_char, game_board_arr->board_ptr[15].cells_ptr[13].display_char, game_board_arr->board_ptr[16].cells_ptr[13].display_char, game_board_arr->board_ptr[17].cells_ptr[13].display_char, game_board_arr->board_ptr[18].cells_ptr[13].display_char, game_board_arr->board_ptr[19].cells_ptr[13].display_char, game_board_arr->board_ptr[20].cells_ptr[13].display_char, game_board_arr->board_ptr[21].cells_ptr[13].display_char, game_board_arr->board_ptr[22].cells_ptr[13].display_char, game_board_arr->board_ptr[23].cells_ptr[13].display_char, game_board_arr->board_ptr[24].cells_ptr[13].display_char, game_board_arr->board_ptr[25].cells_ptr[13].display_char, game_board_arr->board_ptr[26].cells_ptr[13].display_char, game_board_arr->board_ptr[27].cells_ptr[13].display_char, game_board_arr->board_ptr[28].cells_ptr[13].display_char, game_board_arr->board_ptr[29].cells_ptr[13].display_char);
            printf("\n   |---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|");
            printf("\n14 | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c |", game_board_arr->board_ptr[0].cells_ptr[14].display_char, game_board_arr->board_ptr[1].cells_ptr[14].display_char, game_board_arr->board_ptr[2].cells_ptr[14].display_char, game_board_arr->board_ptr[3].cells_ptr[14].display_char, game_board_arr->board_ptr[4].cells_ptr[14].display_char, game_board_arr->board_ptr[5].cells_ptr[14].display_char, game_board_arr->board_ptr[6].cells_ptr[14].display_char, game_board_arr->board_ptr[7].cells_ptr[14].display_char, game_board_arr->board_ptr[8].cells_ptr[14].display_char, game_board_arr->board_ptr[9].cells_ptr[14].display_char, game_board_arr->board_ptr[10].cells_ptr[14].display_char, game_board_arr->board_ptr[11].cells_ptr[14].display_char, game_board_arr->board_ptr[12].cells_ptr[14].display_char, game_board_arr->board_ptr[13].cells_ptr[14].display_char, game_board_arr->board_ptr[14].cells_ptr[14].display_char, game_board_arr->board_ptr[15].cells_ptr[14].display_char, game_board_arr->board_ptr[16].cells_ptr[14].display_char, game_board_arr->board_ptr[17].cells_ptr[14].display_char, game_board_arr->board_ptr[18].cells_ptr[14].display_char, game_board_arr->board_ptr[19].cells_ptr[14].display_char, game_board_arr->board_ptr[20].cells_ptr[14].display_char, game_board_arr->board_ptr[21].cells_ptr[14].display_char, game_board_arr->board_ptr[22].cells_ptr[14].display_char, game_board_arr->board_ptr[23].cells_ptr[14].display_char, game_board_arr->board_ptr[24].cells_ptr[14].display_char, game_board_arr->board_ptr[25].cells_ptr[14].display_char, game_board_arr->board_ptr[26].cells_ptr[14].display_char, game_board_arr->board_ptr[27].cells_ptr[14].display_char, game_board_arr->board_ptr[28].cells_ptr[14].display_char, game_board_arr->board_ptr[29].cells_ptr[14].display_char);
            printf("\n   |---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|");
            printf("\n15 | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c |", game_board_arr->board_ptr[0].cells_ptr[15].display_char, game_board_arr->board_ptr[1].cells_ptr[15].display_char, game_board_arr->board_ptr[2].cells_ptr[15].display_char, game_board_arr->board_ptr[3].cells_ptr[15].display_char, game_board_arr->board_ptr[4].cells_ptr[15].display_char, game_board_arr->board_ptr[5].cells_ptr[15].display_char, game_board_arr->board_ptr[6].cells_ptr[15].display_char, game_board_arr->board_ptr[7].cells_ptr[15].display_char, game_board_arr->board_ptr[8].cells_ptr[15].display_char, game_board_arr->board_ptr[9].cells_ptr[15].display_char, game_board_arr->board_ptr[10].cells_ptr[15].display_char, game_board_arr->board_ptr[11].cells_ptr[15].display_char, game_board_arr->board_ptr[12].cells_ptr[15].display_char, game_board_arr->board_ptr[13].cells_ptr[15].display_char, game_board_arr->board_ptr[14].cells_ptr[15].display_char, game_board_arr->board_ptr[15].cells_ptr[15].display_char, game_board_arr->board_ptr[16].cells_ptr[15].display_char, game_board_arr->board_ptr[17].cells_ptr[15].display_char, game_board_arr->board_ptr[18].cells_ptr[15].display_char, game_board_arr->board_ptr[19].cells_ptr[15].display_char, game_board_arr->board_ptr[20].cells_ptr[15].display_char, game_board_arr->board_ptr[21].cells_ptr[15].display_char, game_board_arr->board_ptr[22].cells_ptr[15].display_char, game_board_arr->board_ptr[23].cells_ptr[15].display_char, game_board_arr->board_ptr[24].cells_ptr[15].display_char, game_board_arr->board_ptr[25].cells_ptr[15].display_char, game_board_arr->board_ptr[26].cells_ptr[15].display_char, game_board_arr->board_ptr[27].cells_ptr[15].display_char, game_board_arr->board_ptr[28].cells_ptr[15].display_char, game_board_arr->board_ptr[29].cells_ptr[15].display_char);
            printf("\n   \\-----------------------------------------------------------------------------------------------------------------------/");
            break;
    }
    
    

}

/**
 * 
 * @brief will recursively search out from user selected cell coordinates, revealing any cells that are not bombs, and stopping at any cells adjacent to bombs.
 * 
 * @param game_board_arr pointer to the game board matrix.
 * @param col_in column of selected cell coordinates.
 * @param row_in row of selected cell coordinates.
 * 
 * @return returns nothing.
 * 
 */
void reveal_cell_recur(struct game_board* game_board_arr, int col_in, int row_in) {

    if (game_board_arr->board_ptr[col_in].cells_ptr[row_in].visited == TRUE) {
        return;
    }
    else {

        int adj_bombs = 0;
        game_board_arr->board_ptr[col_in].cells_ptr[row_in].visited = TRUE;

        enum cell_position c_pos;

        //count how many bombs are adjacent
        //condition checks if the selected cell is not on the edge of the board.
        if((col_in > 0 && col_in < game_board_arr->cols - 1) && (row_in > 0 && row_in < game_board_arr->rows - 1)) {

            c_pos = CENTER;

            //iterate through cells surrounding selected cell, counting how many bombs are present.
            for(int i = col_in - 1; i < col_in + 2; i++) {

                for(int j = row_in - 1; j < row_in + 2; j++) {

                    if(game_board_arr->board_ptr[i].cells_ptr[j].has_bomb == TRUE) {

                        adj_bombs++;

                    }

                }

            }

        }
        
        //for cells of the edges of the board.
        else {

            //determining where the cell is located along the edge
            
            //cells along the left edge of the board
            if(col_in == 0) {

                //this block is for cells located in the upper-left corner of the board
                if(row_in == 0) {

                    c_pos = UL_CORNER;

                    //now that cell is located, we now know which cells are adjacent and in-bounds to check for bombs
                    if(game_board_arr->board_ptr[col_in + 1].cells_ptr[row_in].has_bomb == TRUE) {
                        adj_bombs++;
                    }
                    if(game_board_arr->board_ptr[col_in + 1].cells_ptr[row_in + 1].has_bomb == TRUE) {
                        adj_bombs++;
                    }
                    if(game_board_arr->board_ptr[col_in].cells_ptr[row_in + 1].has_bomb == TRUE) {
                        adj_bombs++;
                    }

                }
                //this block is for cells that are in the bottom-left corner of the board
                else if(row_in == game_board_arr->rows - 1) {

                    c_pos = BL_CORNER;

                    //now that cell is located, we now know which cells are adjacent and in-bounds to check for bombs
                    if(game_board_arr->board_ptr[col_in + 1].cells_ptr[row_in].has_bomb == TRUE) {
                        adj_bombs++;
                    }
                    if(game_board_arr->board_ptr[col_in + 1].cells_ptr[row_in - 1].has_bomb == TRUE) {
                        adj_bombs++;
                    }
                    if(game_board_arr->board_ptr[col_in].cells_ptr[row_in - 1].has_bomb == TRUE) {
                        adj_bombs++;
                    }

                }
                //this block is for cells that are along the left edge of the board, but are not in a corner.
                else {

                    c_pos = LEFT_EDGE;

                    if(game_board_arr->board_ptr[col_in].cells_ptr[row_in - 1].has_bomb == TRUE) {
                        adj_bombs++;
                    }
                    if(game_board_arr->board_ptr[col_in + 1].cells_ptr[row_in - 1].has_bomb == TRUE) {
                        adj_bombs++;
                    }
                    if(game_board_arr->board_ptr[col_in + 1].cells_ptr[row_in].has_bomb == TRUE) {
                        adj_bombs++;
                    }
                    if(game_board_arr->board_ptr[col_in + 1].cells_ptr[row_in + 1].has_bomb == TRUE) {
                        adj_bombs++;
                    }
                    if(game_board_arr->board_ptr[col_in].cells_ptr[row_in + 1].has_bomb == TRUE) {
                        adj_bombs++;
                    }

                }

            }

            //cells located along the right edge of the board.
            else if(col_in == game_board_arr->cols - 1) {

                //cell is located in upper-right corner of the board
                if(row_in == 0) {

                    c_pos = UR_CORNER;

                    if(game_board_arr->board_ptr[col_in - 1].cells_ptr[row_in].has_bomb == TRUE) {
                        adj_bombs++;
                    }
                    if(game_board_arr->board_ptr[col_in - 1].cells_ptr[row_in + 1].has_bomb == TRUE) {
                        adj_bombs++;
                    }
                    if(game_board_arr->board_ptr[col_in].cells_ptr[row_in + 1].has_bomb == TRUE) {
                        adj_bombs++;
                    }

                }
                //cell is located in the lower-right corner of the board.
                else if(row_in == game_board_arr->rows - 1) {
                    
                    c_pos = BR_CORNER;

                    if(game_board_arr->board_ptr[col_in].cells_ptr[row_in - 1].has_bomb == TRUE) {
                        adj_bombs++;
                    }
                    if(game_board_arr->board_ptr[col_in - 1].cells_ptr[row_in - 1].has_bomb == TRUE) {
                        adj_bombs++;
                    }
                    if(game_board_arr->board_ptr[col_in - 1].cells_ptr[row_in].has_bomb == TRUE) {
                        adj_bombs++;
                    }

                }
                //cell is located on the right edge but is not a corner cell.
                else {

                    c_pos = RIGHT_EDGE;

                    if(game_board_arr->board_ptr[col_in].cells_ptr[row_in + 1].has_bomb == TRUE) {
                        adj_bombs++;
                    }
                    if(game_board_arr->board_ptr[col_in - 1].cells_ptr[row_in + 1].has_bomb == TRUE) {
                        adj_bombs++;
                    }
                    if(game_board_arr->board_ptr[col_in - 1].cells_ptr[row_in].has_bomb == TRUE) {
                        adj_bombs++;
                    }
                    if(game_board_arr->board_ptr[col_in - 1].cells_ptr[row_in - 1].has_bomb == TRUE) {
                        adj_bombs++;
                    }
                    if(game_board_arr->board_ptr[col_in].cells_ptr[row_in - 1].has_bomb == TRUE) {
                        adj_bombs++;
                    }

                }

            }

            //cells located along the top edge of the board, excluding the corners since they are covered in the above blocks.
            else if(row_in == 0 && (col_in != 0 && col_in != game_board_arr->cols - 1)) {

                c_pos = TOP_EDGE;

                if(game_board_arr->board_ptr[col_in + 1].cells_ptr[row_in].has_bomb == TRUE) {
                    adj_bombs++;
                }
                if(game_board_arr->board_ptr[col_in + 1].cells_ptr[row_in + 1].has_bomb == TRUE) {
                    adj_bombs++;
                }
                if(game_board_arr->board_ptr[col_in].cells_ptr[row_in + 1].has_bomb == TRUE) {
                    adj_bombs++;
                }
                if(game_board_arr->board_ptr[col_in - 1].cells_ptr[row_in + 1].has_bomb == TRUE) {
                    adj_bombs++;
                }
                if(game_board_arr->board_ptr[col_in - 1].cells_ptr[row_in].has_bomb == TRUE) {
                    adj_bombs++;
                }

            }

            //cells located along the bottom edge of the board, excluding the corners since they are covered in the above blocks.
            else if(row_in == game_board_arr->rows - 1 && (col_in != 0 && col_in != game_board_arr->cols - 1)) {

                c_pos = BOTTOM_EDGE;

                if(game_board_arr->board_ptr[col_in - 1].cells_ptr[row_in].has_bomb == TRUE) {
                    adj_bombs++;
                }
                if(game_board_arr->board_ptr[col_in - 1].cells_ptr[row_in - 1].has_bomb == TRUE) {
                    adj_bombs++;
                }
                if(game_board_arr->board_ptr[col_in].cells_ptr[row_in - 1].has_bomb == TRUE) {
                    adj_bombs++;
                }
                if(game_board_arr->board_ptr[col_in + 1].cells_ptr[row_in - 1].has_bomb == TRUE) {
                    adj_bombs++;
                }
                if(game_board_arr->board_ptr[col_in + 1].cells_ptr[row_in].has_bomb == TRUE) {
                    adj_bombs++;
                }

            }

        }

        //if no bombs are adjacent, recursively call this function on adjacent cells
        if(adj_bombs == 0) {

            /*changing display char to reflect that thare are no adjacent bombs to this tile, 
            then recursively calling this function on its adjacent tiles*/
            switch(c_pos) {

                case(CENTER):

                    game_board_arr->board_ptr[col_in].cells_ptr[row_in].c_stat = OPEN;
                    game_board_arr->board_ptr[col_in].cells_ptr[row_in].display_char = '_';

                    reveal_cell_recur(game_board_arr, col_in, row_in - 1);
                    reveal_cell_recur(game_board_arr, col_in + 1, row_in - 1);
                    reveal_cell_recur(game_board_arr, col_in + 1, row_in);
                    reveal_cell_recur(game_board_arr, col_in + 1, row_in + 1);
                    reveal_cell_recur(game_board_arr, col_in, row_in + 1);
                    reveal_cell_recur(game_board_arr, col_in - 1, row_in + 1);
                    reveal_cell_recur(game_board_arr, col_in - 1, row_in);
                    reveal_cell_recur(game_board_arr, col_in - 1, row_in - 1);

                    break;

                case(LEFT_EDGE):

                    game_board_arr->board_ptr[col_in].cells_ptr[row_in].c_stat = OPEN;
                    game_board_arr->board_ptr[col_in].cells_ptr[row_in].display_char = '_';

                    reveal_cell_recur(game_board_arr, col_in, row_in - 1);
                    reveal_cell_recur(game_board_arr, col_in + 1, row_in - 1);
                    reveal_cell_recur(game_board_arr, col_in + 1, row_in);
                    reveal_cell_recur(game_board_arr, col_in + 1, row_in + 1);
                    reveal_cell_recur(game_board_arr, col_in, row_in + 1);

                    break;

                case(RIGHT_EDGE):

                    game_board_arr->board_ptr[col_in].cells_ptr[row_in].c_stat = OPEN;
                    game_board_arr->board_ptr[col_in].cells_ptr[row_in].display_char = '_';

                    reveal_cell_recur(game_board_arr, col_in, row_in + 1);
                    reveal_cell_recur(game_board_arr, col_in - 1, row_in + 1);
                    reveal_cell_recur(game_board_arr, col_in - 1, row_in);
                    reveal_cell_recur(game_board_arr, col_in - 1, row_in - 1);
                    reveal_cell_recur(game_board_arr, col_in, row_in - 1);

                    break;

                case(TOP_EDGE):

                    game_board_arr->board_ptr[col_in].cells_ptr[row_in].c_stat = OPEN;
                    game_board_arr->board_ptr[col_in].cells_ptr[row_in].display_char = '_';

                    reveal_cell_recur(game_board_arr, col_in + 1, row_in);
                    reveal_cell_recur(game_board_arr, col_in + 1, row_in + 1);
                    reveal_cell_recur(game_board_arr, col_in, row_in + 1);
                    reveal_cell_recur(game_board_arr, col_in - 1, row_in + 1);
                    reveal_cell_recur(game_board_arr, col_in - 1, row_in);

                    break;

                case(BOTTOM_EDGE):

                    game_board_arr->board_ptr[col_in].cells_ptr[row_in].c_stat = OPEN;
                    game_board_arr->board_ptr[col_in].cells_ptr[row_in].display_char = '_';

                    reveal_cell_recur(game_board_arr, col_in - 1, row_in);
                    reveal_cell_recur(game_board_arr, col_in - 1, row_in - 1);
                    reveal_cell_recur(game_board_arr, col_in, row_in - 1);
                    reveal_cell_recur(game_board_arr, col_in + 1, row_in - 1);
                    reveal_cell_recur(game_board_arr, col_in + 1, row_in);

                    break;

                case(UL_CORNER):

                    game_board_arr->board_ptr[col_in].cells_ptr[row_in].c_stat = OPEN;
                    game_board_arr->board_ptr[col_in].cells_ptr[row_in].display_char = '_';

                    reveal_cell_recur(game_board_arr, col_in + 1, row_in);
                    reveal_cell_recur(game_board_arr, col_in + 1, row_in + 1);
                    reveal_cell_recur(game_board_arr, col_in, row_in + 1);

                    break;

                case(UR_CORNER):

                    game_board_arr->board_ptr[col_in].cells_ptr[row_in].c_stat = OPEN;
                    game_board_arr->board_ptr[col_in].cells_ptr[row_in].display_char = '_';

                    reveal_cell_recur(game_board_arr, col_in - 1, row_in);
                    reveal_cell_recur(game_board_arr, col_in - 1, row_in + 1);
                    reveal_cell_recur(game_board_arr, col_in, row_in + 1);

                    break;

                case(BL_CORNER):

                    game_board_arr->board_ptr[col_in].cells_ptr[row_in].c_stat = OPEN;
                    game_board_arr->board_ptr[col_in].cells_ptr[row_in].display_char = '_';

                    reveal_cell_recur(game_board_arr, col_in, row_in - 1);
                    reveal_cell_recur(game_board_arr, col_in + 1, row_in - 1);
                    reveal_cell_recur(game_board_arr, col_in + 1, row_in);

                    break;

                case(BR_CORNER):

                    game_board_arr->board_ptr[col_in].cells_ptr[row_in].c_stat = OPEN;
                    game_board_arr->board_ptr[col_in].cells_ptr[row_in].display_char = '_';

                    reveal_cell_recur(game_board_arr, col_in - 1, row_in);
                    reveal_cell_recur(game_board_arr, col_in - 1, row_in - 1);
                    reveal_cell_recur(game_board_arr, col_in, row_in - 1);

                    break;
                
            }

        }
        else {

            //changing display char to reflect how many adjacent bombs there are to this tile
            switch(adj_bombs) {

                case(1):

                    game_board_arr->board_ptr[col_in].cells_ptr[row_in].c_stat = OPEN;
                    game_board_arr->board_ptr[col_in].cells_ptr[row_in].display_char = '1';

                    break;

                case(2):

                    game_board_arr->board_ptr[col_in].cells_ptr[row_in].c_stat = OPEN;
                    game_board_arr->board_ptr[col_in].cells_ptr[row_in].display_char = '2';

                    break;

                case(3):

                    game_board_arr->board_ptr[col_in].cells_ptr[row_in].c_stat = OPEN;
                    game_board_arr->board_ptr[col_in].cells_ptr[row_in].display_char = '3';

                    break;

                case(4):

                    game_board_arr->board_ptr[col_in].cells_ptr[row_in].c_stat = OPEN;
                    game_board_arr->board_ptr[col_in].cells_ptr[row_in].display_char = '4';

                    break;

                case(5):

                    game_board_arr->board_ptr[col_in].cells_ptr[row_in].c_stat = OPEN;
                    game_board_arr->board_ptr[col_in].cells_ptr[row_in].display_char = '5';

                    break;

                case(6):

                    game_board_arr->board_ptr[col_in].cells_ptr[row_in].c_stat = OPEN;
                    game_board_arr->board_ptr[col_in].cells_ptr[row_in].display_char = '6';

                    break;

                case(7):

                    game_board_arr->board_ptr[col_in].cells_ptr[row_in].c_stat = OPEN;
                    game_board_arr->board_ptr[col_in].cells_ptr[row_in].display_char = '7';

                    break;

                case(8):

                    game_board_arr->board_ptr[col_in].cells_ptr[row_in].c_stat = OPEN;
                    game_board_arr->board_ptr[col_in].cells_ptr[row_in].display_char = '8';

                    break;

            }

            

        }
    }

}

/**
 * 
 * @brief will iterate through whole board and reset each cell's 'visited' data member to FALSE (0)
 * 
 * @return returns nothing
 * 
 */
void reset_visit_flags(struct game_board* game_board_arr) {

    for (int i = 0; i < game_board_arr->cols; i++) {

        for (int j = 0; j < game_board_arr->cols; j++) {

            game_board_arr->board_ptr[i].cells_ptr[j].visited = FALSE;

        }

    }

}


/**
 * 
 * @brief will house the functions that reveal the cell at the input coordinates, as well as call the 
 * recursive function to reveal any adjacent cells to the input. will also call function to reset all visited flags. 
 * 
 * @param game_board_arr pointer to the game board matrix.
 * @param col_in column of selected cell coordinates.
 * @param row_in row of selected cell coordinates.
 * 
 */
void reveal_cell_init(struct game_board* game_board_arr, int col_in, int row_in, int reveal_cell_actions) {
    
    //ensures that the first cell that is revealed will always be safe by only setting the bombs after the first cell is revealed
    if(reveal_cell_actions == 1) {

        set_bombs(game_board_arr, col_in, row_in);
        reveal_cell_recur(game_board_arr, col_in, row_in);
        reset_visit_flags(game_board_arr);

    }
    else {

        reveal_cell_recur(game_board_arr, col_in, row_in);
        reset_visit_flags(game_board_arr);

    }
}


/**
 * 
 * @brief will change the display character of all cells that have a bomb to '#'.
 * 
 * @return returns nothing.
 * 
 */
void reveal_bombs(struct game_board* game_board_arr) {

    for (int i = 0; i < game_board_arr->cols; i++) {

        for (int j = 0; j < game_board_arr->cols; j++) {

            if(game_board_arr->board_ptr[i].cells_ptr[j].has_bomb == TRUE) {
                game_board_arr->board_ptr[i].cells_ptr[j].c_stat = OPEN;
                game_board_arr->board_ptr[i].cells_ptr[j].display_char = '#';
            }

        }
    }

}


/**
 * 
 * @brief will determine if game has been won by checking if every cell that does not have a bomb is revealed
 * 
 * @param game_board_arr pointer to the game board matrix.
 * 
 * @return returns an integer. 1 indicates that the player has won the game, and 0 indicates that the player has not yet won.
 * 
 */
int win_check(struct game_board* game_board_arr) {

    int open_cell_count = 0;

    switch(game_board_arr->board_difficulty) {

        default:

            //handling unexpected difficulty levels
            return -1;


        case(SIMPLE):

            for (int i = 0; i < game_board_arr->cols; i++) {

                for (int j = 0; j < game_board_arr->cols; j++) {

                    if((game_board_arr->board_ptr[i].cells_ptr[j].has_bomb == FALSE && game_board_arr->board_ptr[i].cells_ptr[j].c_stat == OPEN) ||
                       (game_board_arr->board_ptr[i].cells_ptr[j].has_bomb == FALSE && game_board_arr->board_ptr[i].cells_ptr[j].c_stat == FLAGGED)
                    ) {

                        open_cell_count++;
                        
                    }

                    //checking if number of open cells matches the number of cells on the board minus the number of bombs
                    if(open_cell_count == 25 - game_board_arr->number_of_bombs) {
                        game_board_arr->g_stat = WON;
                        break;
                    }

                    if(game_board_arr->g_stat == WON) {
                        break;
                    }

                }

                if(game_board_arr->g_stat == WON) {
                    return 1;
                    break;
                }

            }  

            return 0; 
            break;


        case(EASY):
            
            for (int i = 0; i < game_board_arr->cols; i++) {

                for (int j = 0; j < game_board_arr->cols; j++) {

                    if(game_board_arr->board_ptr[i].cells_ptr[j].has_bomb == FALSE && game_board_arr->board_ptr[i].cells_ptr[j].c_stat == OPEN) {

                        open_cell_count++;
                        
                    }

                    //checking if number of open cells matches the number of cells on the board minus the number of bombs
                    if(open_cell_count == 81 - game_board_arr->number_of_bombs) {
                        game_board_arr->g_stat = WON;
                        break;
                    }

                    if(game_board_arr->g_stat == WON) {
                        break;
                    }

                }

                if(game_board_arr->g_stat == WON) {
                    return 1;
                    break;
                }

            }  

            return 0; 
            break;


        case(MEDIUM):

            for (int i = 0; i < game_board_arr->cols; i++) {

                for (int j = 0; j < game_board_arr->cols; j++) {

                    if(game_board_arr->board_ptr[i].cells_ptr[j].has_bomb == FALSE && game_board_arr->board_ptr[i].cells_ptr[j].c_stat == OPEN) {

                        open_cell_count++;
                        
                    }

                    //checking if number of open cells matches the number of cells on the board minus the number of bombs
                    if(open_cell_count == 256 - game_board_arr->number_of_bombs) {
                        game_board_arr->g_stat = WON;
                        break;
                    }

                    if(game_board_arr->g_stat == WON) {
                        break;
                    }

                }

                if(game_board_arr->g_stat == WON) {
                    return 1;
                    break;
                }

            }  

            return 0; 
            break;


        case(HARD):

            for (int i = 0; i < game_board_arr->cols; i++) {

                for (int j = 0; j < game_board_arr->cols; j++) {

                    if(game_board_arr->board_ptr[i].cells_ptr[j].has_bomb == FALSE && game_board_arr->board_ptr[i].cells_ptr[j].c_stat == OPEN) {

                        open_cell_count++;
                        
                    }

                    //checking if number of open cells matches the number of cells on the board minus the number of bombs
                    if(open_cell_count == 480 - game_board_arr->number_of_bombs) {
                        game_board_arr->g_stat = WON;
                        break;
                    }

                    if(game_board_arr->g_stat == WON) {
                        break;
                    }

                }

                if(game_board_arr->g_stat == WON) {
                    return 1;
                    break;
                }

            }  

            return 0; 
            break;

    }
}


/**
 * 
 * @brief this funtion will house the game loop, calling other functions for the game until the game state is 'won' or 'lost'.
 * 
 * @param game_board_arr the array that stores the data for the game that will be played.
 * 
 * @return returns nothing.
 * 
 */
void play_game(struct game_board* game_board_arr) {

    //is currently for testing purposes. but could be used as a kind of "score" along with the time taken to complete a game.
    int round_count = 1;
    int reveal_cell_actions = 0;

    int col_in;
    int row_in;
    char command_in;

    game_board_arr->g_stat = PLAYING;

    //game cycle will continue until game status is changed from 'playing'
    while (game_board_arr->g_stat == PLAYING) {

        //take user input (coordinates, and a command char)
        printf("\n\nInput cell coordinates (column, then row), and a command for the cell. Example: '3,2,R' \n");
        printf("commands: | 'R' = reveal cell | 'F' = flag cell |\n");

        scanf("%d,%d,%c", &col_in, &row_in, &command_in);

        //error handling for user input
        if(col_in < 0 || col_in > game_board_arr->cols || row_in < 0 || row_in > game_board_arr->rows) {
            printf("Input coordinates out of bounds. please try again.\n");
            break;
        }
        else if(command_in == 'f' || command_in == 'F' || command_in == 'r' || command_in == 'R') {
            
            //handling flagging cells
            if(command_in == 'F' || command_in == 'f') {

                if(game_board_arr->board_ptr[col_in].cells_ptr[row_in].c_stat == FLAGGED) {
                    game_board_arr->board_ptr[col_in].cells_ptr[row_in].c_stat = HIDDEN;
                    game_board_arr->board_ptr[col_in].cells_ptr[row_in].display_char = ' ';
                    print_board(game_board_arr);
                }
                else if(game_board_arr->board_ptr[col_in].cells_ptr[row_in].c_stat == OPEN) {

                    //do nothing, since you cant flag an opened cell

                }
                else {
                    game_board_arr->board_ptr[col_in].cells_ptr[row_in].c_stat = FLAGGED;
                    game_board_arr->board_ptr[col_in].cells_ptr[row_in].display_char = '!';
                    print_board(game_board_arr);
                }
            
            }
            //handling revealing a cell with a bomb
            else if(game_board_arr->board_ptr[col_in].cells_ptr[row_in].has_bomb == TRUE) {

                game_board_arr->g_stat = LOST;
                //call funtion to reveal all bombs
                reveal_bombs(game_board_arr);
                print_board(game_board_arr);

                //print something to the terminal to indicate that the player has lost
                printf("\n\n================================================================================================================\n");
                printf("                                                      GAME OVER                                                 \n");
                printf("================================================================================================================\n\n");
                return;

            }
            //handling revealing a cell with no bomb
            else {
                
                reveal_cell_actions = 1 + reveal_cell_actions;

                reveal_cell_init(game_board_arr, col_in, row_in, reveal_cell_actions);
                print_board(game_board_arr);

            }

            //call win_check somewhere around here
            int has_won = 0;

            has_won = win_check(game_board_arr);
            if(has_won == 1) {
                //player has won the game
                //print something to the terminal here to indicate this to the player
                printf("\n\n================================================================================================================\n");
                printf("                                                      YOU WIN!                                                  \n");
                printf("================================================================================================================\n\n");

                printf("you completed the game in %d rounds!\n", round_count);
                return;
            }
            else {
                //player has not won, and will continue playing
                round_count++;
            }
        }
        else {

            printf("Input command invalid. please try again.\n");

        }

    }

}


int main() {

    int keep_playing = 1;

    while(keep_playing == 1) {

        enum difficulty game_difficulty = select_difficulty();
        struct game_board* game_board_ptr = create_game_board_array(game_difficulty);
        print_board(game_board_ptr);
        play_game(game_board_ptr);

        int valid_response = 0;
        while(valid_response != 1) {
            
            char response = ' ';
            printf("\n\nplay another game? ('y' = yes, 'n' = no)\n");
            scanf("%c", &response);
            if(response == 'y' || response == 'Y') {
                keep_playing = 1;
                valid_response = 1;
                break;
            }
            else if(response == 'n' || response == 'N') {
                printf("Thank you for playing!\n");
                valid_response = 1;
                keep_playing = 0;
                break;
            }
            else {
                printf("response invalid. please try again.\n");
            }

        }
        

    }

    

};
