#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Minesweeper.h"

//gcc -Wall Minesweeper.c -o Minesweeper
enum difficulty;

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
 * @param game_board_data the game_board struct that will have bombs set to it by this function.
 * 
 * @return returns nothing.  
 * 
*/
void set_bombs(struct game_board* game_board_data) {

    int bombs_set = 0;

    switch(game_board_data->board_difficulty) {

        case(SIMPLE):

            srand(time(0));
            
            while(bombs_set != game_board_data->number_of_bombs) {

                for (int i = 0; i < game_board_data->cols; i++)
                {
                    
                    for (int j = 0; j < game_board_data->rows; j++)
                    {
                        
                        int mod_val = rand() % 2;

                        if(mod_val == 1) {
                            game_board_data->board_ptr[i].cells_ptr[j].has_bomb = TRUE;
                            bombs_set++;
                        }

                        if(bombs_set == game_board_data->number_of_bombs) {
                            break;
                        }

                    }

                    if(bombs_set == game_board_data->number_of_bombs) {
                            break;
                    }

                }
            
            }


        case(EASY):

            srand(time(0));

            while(bombs_set != game_board_data->number_of_bombs) {

                for (int i = 0; i < game_board_data->cols; i++)
                {
                    
                    for (int j = 0; j < game_board_data->rows; j++)
                    {
                        
                        int mod_val = rand() % 2;

                        if(mod_val == 1) {
                            game_board_data->board_ptr[i].cells_ptr[j].has_bomb = TRUE;
                            bombs_set++;
                        }

                        if(bombs_set == game_board_data->number_of_bombs) {
                            break;
                        }

                    }

                    if(bombs_set == game_board_data->number_of_bombs) {
                            break;
                    }

                }
            
            }

        case(MEDIUM):

            srand(time(0));;

            while(bombs_set != game_board_data->number_of_bombs) {

                for (int i = 0; i < game_board_data->cols; i++)
                {
                    
                    for (int j = 0; j < game_board_data->rows; j++)
                    {
                        
                        int mod_val = rand() % 2;

                        if(mod_val == 1) {
                            game_board_data->board_ptr[i].cells_ptr[j].has_bomb = TRUE;
                            bombs_set++;
                        }

                        if(bombs_set == game_board_data->number_of_bombs) {
                            break;
                        }

                    }

                    if(bombs_set == game_board_data->number_of_bombs) {
                            break;
                    }

                }
            
            }

        case(HARD):

            srand(time(0));

            while(bombs_set != game_board_data->number_of_bombs) {

                for (int i = 0; i < game_board_data->cols; i++)
                {
                    
                    for (int j = 0; j < game_board_data->rows; j++)
                    {
                        
                        int mod_val = rand() % 2;

                        if(mod_val == 1) {
                            game_board_data->board_ptr[i].cells_ptr[j].has_bomb = TRUE;
                            bombs_set++;
                        }

                        if(bombs_set == game_board_data->number_of_bombs) {
                            break;
                        }

                    }

                    if(bombs_set == game_board_data->number_of_bombs) {
                            break;
                    }

                }
            
            }

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
        printf("Error: game difficulty out of bounds.");
        return game_array;
        exit(1);
    }

    switch(game_difficulty) {
        case(SIMPLE):
            
            //initialize game_array struct
            game_array = (struct game_board*)malloc(sizeof(struct game_board)*1);

            //check for malloc success
            if (game_array == NULL) {
                printf("Error: memory allocation failed.");
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
                printf("Error: memory allocation failed.");
                free(game_array->board_ptr);
                free(game_array);
                exit(1);
            }

            //allocate the memory for the game_cell structs, and populate its data members.
            for(int x = 0; x < game_array->cols; x++) {

                game_array->board_ptr[x].cells_ptr = (struct game_cell*)malloc(sizeof(struct game_cell)*game_array->rows);
                
                //check for malloc success
                if (game_array->board_ptr[x].cells_ptr == NULL) {

                    printf("Error: memory allocation failed.");

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

            //call set_bombs function to complete board setup.
            set_bombs(game_array);


        case(EASY):

            //initialize game_array struct
            game_array = (struct game_board*)malloc(sizeof(struct game_board)*1);

            //check for malloc success
            if (game_array == NULL) {
                printf("Error: memory allocation failed.");
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
                printf("Error: memory allocation failed.");
                free(game_array->board_ptr);
                free(game_array);
                exit(1);
            }

            //allocate the memory for the game_cell structs, and populate its data members.
            for(int x = 0; x < game_array->cols; x++) {

                game_array->board_ptr[x].cells_ptr = (struct game_cell*)malloc(sizeof(struct game_cell)*game_array->rows);
                
                //check for malloc success
                if (game_array->board_ptr[x].cells_ptr == NULL) {

                    printf("Error: memory allocation failed.");

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

            //call set_bombs function to complete board setup.
            set_bombs(game_array);


        case(MEDIUM):

            //initialize game_array struct
            game_array = (struct game_board*)malloc(sizeof(struct game_board)*1);

            //check for malloc success
            if (game_array == NULL) {
                printf("Error: memory allocation failed.");
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
                printf("Error: memory allocation failed.");
                free(game_array->board_ptr);
                free(game_array);
                exit(1);
            }

            //allocate the memory for the game_cell structs, and populate its data members.
            for(int x = 0; x < game_array->cols; x++) {

                game_array->board_ptr[x].cells_ptr = (struct game_cell*)malloc(sizeof(struct game_cell)*game_array->rows);
                
                //check for malloc success
                if (game_array->board_ptr[x].cells_ptr == NULL) {

                    printf("Error: memory allocation failed.");

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

            //call set_bombs function to complete board setup.
            set_bombs(game_array);


        case(HARD):

            //initialize game_array struct
            game_array = (struct game_board*)malloc(sizeof(struct game_board)*1);

            //check for malloc success
            if (game_array == NULL) {
                printf("Error: memory allocation failed.");
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
                printf("Error: memory allocation failed.");
                free(game_array->board_ptr);
                free(game_array);
                exit(1);
            }

            //allocate the memory for the game_cell structs, and populate its data members.
            for(int x = 0; x < game_array->cols; x++) {

                game_array->board_ptr[x].cells_ptr = (struct game_cell*)malloc(sizeof(struct game_cell)*game_array->rows);
                
                //check for malloc success
                if (game_array->board_ptr[x].cells_ptr == NULL) {

                    printf("Error: memory allocation failed.");

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

            //call set_bombs function to complete board setup.
            set_bombs(game_array);

    }

    return game_array;

}

/**
 * 
 * @brief prints the board to the screen, populated with the game data.
 * 
 * @param game_difficulty the difficulty will determine the size of the board that is printed
 * @param game_board_data the array that stores the data for the game that will be played.
 * 
 * @return returns nothing
 * 
 */
// TOADD - param: struct game_board game_board_data
void print_board(struct game_board* game_board_arr) {

    switch(game_board_arr->board_difficulty) {
        case(SIMPLE):
            printf("game difficulty: SIMPLE\n\n");
            printf("     0   1   2   3   4\n");
            printf("   /-------------------\\");
            printf("\n 0 |   |   |   |   |   |");
            printf("\n   |---|---|---|---|---|");
            printf("\n 1 |   |   |   |   |   |");
            printf("\n   |---|---|---|---|---|");
            printf("\n 2 |   |   |   |   |   |");
            printf("\n   |---|---|---|---|---|");
            printf("\n 3 |   |   |   |   |   |");
            printf("\n   |---|---|---|---|---|");
            printf("\n 4 |   |   |   |   |   |");
            printf("\n   \\-------------------/");

            break;

        case(EASY):
            printf("game difficulty: EASY\n");
            printf("     0   1   2   3   4   5   6   7   8\n");
            printf("   /-----------------------------------\\");
            printf("\n 0 |   |   |   |   |   |   |   |   |   |");
            printf("\n   |---|---|---|---|---|---|---|---|---|");
            printf("\n 1 |   |   |   |   |   |   |   |   |   |");
            printf("\n   |---|---|---|---|---|---|---|---|---|");
            printf("\n 2 |   |   |   |   |   |   |   |   |   |");
            printf("\n   |---|---|---|---|---|---|---|---|---|");
            printf("\n 3 |   |   |   |   |   |   |   |   |   |");
            printf("\n   |---|---|---|---|---|---|---|---|---|");
            printf("\n 4 |   |   |   |   |   |   |   |   |   |");
            printf("\n   |---|---|---|---|---|---|---|---|---|");
            printf("\n 5 |   |   |   |   |   |   |   |   |   |");
            printf("\n   |---|---|---|---|---|---|---|---|---|");
            printf("\n 6 |   |   |   |   |   |   |   |   |   |");
            printf("\n   |---|---|---|---|---|---|---|---|---|");
            printf("\n 7 |   |   |   |   |   |   |   |   |   |");
            printf("\n   |---|---|---|---|---|---|---|---|---|");
            printf("\n 8 |   |   |   |   |   |   |   |   |   |");
            printf("\n   \\-----------------------------------/");
            break;

        case(MEDIUM):
            printf("game difficulty: MEDIUM\n");
            printf("     0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15\n");
            printf("   /---------------------------------------------------------------\\");
            printf("\n 0 |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |");
            printf("\n   |---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|");
            printf("\n 1 |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |");
            printf("\n   |---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|");
            printf("\n 2 |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |");
            printf("\n   |---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|");
            printf("\n 3 |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |");
            printf("\n   |---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|");
            printf("\n 4 |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |");
            printf("\n   |---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|");
            printf("\n 5 |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |");
            printf("\n   |---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|");
            printf("\n 6 |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |");
            printf("\n   |---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|");
            printf("\n 7 |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |");
            printf("\n   |---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|");
            printf("\n 8 |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |");
            printf("\n   |---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|");
            printf("\n 9 |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |");
            printf("\n   |---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|");
            printf("\n10 |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |");
            printf("\n   |---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|");
            printf("\n11 |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |");
            printf("\n   |---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|");
            printf("\n12 |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |");
            printf("\n   |---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|");
            printf("\n13 |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |");
            printf("\n   |---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|");
            printf("\n14 |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |");
            printf("\n   |---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|");
            printf("\n15 |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |");
            printf("\n   \\---------------------------------------------------------------/");
            break;

        case(HARD):
            printf("game difficulty: HARD\n");
            printf("     0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25  26  27  28  29\n");
            printf("   /-----------------------------------------------------------------------------------------------------------------------\\");
            printf("\n 0 |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |");
            printf("\n   |---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|");
            printf("\n 1 |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |");
            printf("\n   |---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|");
            printf("\n 2 |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |");
            printf("\n   |---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|");
            printf("\n 3 |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |");
            printf("\n   |---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|");
            printf("\n 4 |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |");
            printf("\n   |---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|");
            printf("\n 5 |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |");
            printf("\n   |---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|");
            printf("\n 6 |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |");
            printf("\n   |---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|");
            printf("\n 7 |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |");
            printf("\n   |---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|");
            printf("\n 8 |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |");
            printf("\n   |---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|");
            printf("\n 9 |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |");
            printf("\n   |---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|");
            printf("\n10 |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |");
            printf("\n   |---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|");
            printf("\n11 |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |");
            printf("\n   |---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|");
            printf("\n12 |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |");
            printf("\n   |---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|");
            printf("\n13 |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |");
            printf("\n   |---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|");
            printf("\n14 |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |");
            printf("\n   |---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|");
            printf("\n15 |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |");
            printf("\n   \\-----------------------------------------------------------------------------------------------------------------------/");
            break;
    }
    
    

}


/**
 * 
 * @brief this funtion will execute the game loop, calling other functions for the game until the game state is 'won' or 'lost'.
 * 
 * @param game_board_arr the array that stores the data for the game that will be played.
 * 
 * @return returns nothing.
 * 
 */
void play_game(struct game_board* game_board_arr) {

    //game cycle will continue until game status is 'won'
    while (game_board_arr->g_stat != WON) {



    }

}


int main() {
enum difficulty game_difficulty = select_difficulty();
struct game_board* game_board_ptr = create_game_board_array(game_difficulty);
print_board(game_board_ptr);

};
