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

    if (game_difficulty < 0 || game_difficulty > 3) {
        printf("Error: game difficulty out of bounds.");
        int* nullptr = NULL;
        return nullptr;

        exit(1);
    }


    switch(game_difficulty) {
        case(SIMPLE):

            //initialize the game_board and populate its data members.
            struct game_board* simple_game = (struct game_board*)malloc(sizeof(struct game_board)*1);
            
            if (simple_game == NULL) {
                printf("Error: memory allocation failed.");
                free(simple_game);
                exit(1);
            }

            simple_game->rows = 5;
            simple_game->cols = 5;
            simple_game->number_of_bombs = 3;
            simple_game->g_stat = MENU;
            simple_game->board_difficulty = game_difficulty;

            //allocate memory to store the game_cell array pointers
            simple_game->board_ptr = (struct dynamic_array*)malloc(sizeof(struct dynamic_array)*simple_game->cols);
            
            if (simple_game->board_ptr == NULL) {
                printf("Error: memory allocation failed.");
                free(simple_game);
                exit(1);
            }

            //allocate the memory for the game_cell structs, and populate its data members.
            for(int x = 0; x < simple_game->cols; x++) {

                simple_game->board_ptr[x].cells_ptr = (struct game_cell*)malloc(sizeof(struct game_cell)*simple_game->rows);
                
                for(int y = 0; y < simple_game->rows; y++) {

                    simple_game->board_ptr[x].cells_ptr[y].c_stat = HIDDEN;
                    simple_game->board_ptr[x].cells_ptr[y].display_char = ' ';

                }

            }

            //call set_bombs, passing in the created game_board array
            if(simple_game == NULL) {
                printf("Error: game board array not created properly.");
                return simple_game;
                exit(1);
            }
            else{

                set_bombs(simple_game);
                return simple_game;
            }
            

        case(EASY):

            //initialize the game_board and populate its data members.
            struct game_board* easy_game = (struct game_board*)malloc(sizeof(struct game_board)*1);
            easy_game->rows = 9;
            easy_game->cols = 9;
            easy_game->number_of_bombs = 10;
            easy_game->g_stat = MENU;
            easy_game->board_difficulty = game_difficulty;

            //allocate memory to store the game_cell array pointers
            easy_game->board_ptr = (struct dynamic_array*)malloc(sizeof(struct dynamic_array)*easy_game->cols);
            
            //allocate the memory for the game_cell structs, and populate its data members.
            for(int x = 0; x < easy_game->cols; x++) {

                easy_game->board_ptr[x].cells_ptr = (struct game_cell*)malloc(sizeof(struct game_cell)*easy_game->rows);
                
                for(int y = 0; y < easy_game->rows; y++) {

                    easy_game->board_ptr[x].cells_ptr[y].c_stat = HIDDEN;
                    easy_game->board_ptr[x].cells_ptr[y].display_char = ' ';

                }

            }

            //call set_bombs, passing in the created game_board array
            if(easy_game == NULL) {
                printf("Error: game board array not created properly.");
                return easy_game;
                exit(1);
            }
            else{

                set_bombs(easy_game);
                return easy_game;
            }

        case(MEDIUM):

            //initialize the game_board and populate its data members.
            struct game_board* medium_game = (struct game_board*)malloc(sizeof(struct game_board)*1);
            medium_game->rows = 16;
            medium_game->cols = 16;
            medium_game->number_of_bombs = 40;
            medium_game->g_stat = MENU;
            medium_game->board_difficulty = game_difficulty;

            //allocate memory to store the game_cell array pointers
            medium_game->board_ptr = (struct dynamic_array*)malloc(sizeof(struct dynamic_array)*medium_game->cols);
            
            //allocate the memory for the game_cell structs, and populate its data members.
            for(int x = 0; x < medium_game->cols; x++) {

                medium_game->board_ptr[x].cells_ptr = (struct game_cell*)malloc(sizeof(struct game_cell)*medium_game->rows);
                
                for(int y = 0; y < medium_game->rows; y++) {

                    medium_game->board_ptr[x].cells_ptr[y].c_stat = HIDDEN;
                    medium_game->board_ptr[x].cells_ptr[y].display_char = ' ';

                }

            }

            //call set_bombs, passing in the created game_board array
            if(medium_game == NULL) {
                printf("Error: game board array not created properly.");
                return medium_game;
                exit(1);
            }
            else{

                set_bombs(medium_game);
                return medium_game;
            }

        case(HARD):

            //initialize the game_board and populate its data members.
            struct game_board* hard_game = (struct game_board*)malloc(sizeof(struct game_board)*1);
            hard_game->rows = 16;
            hard_game->cols = 30;
            hard_game->number_of_bombs = 99;
            hard_game->g_stat = MENU;
            hard_game->board_difficulty = game_difficulty;

            //allocate memory to store the game_cell array pointers
            hard_game->board_ptr = (struct dynamic_array*)malloc(sizeof(struct dynamic_array)*hard_game->cols);
            
            //allocate the memory for the game_cell structs, and populate its data members.
            for(int x = 0; x < hard_game->cols; x++) {

                hard_game->board_ptr[x].cells_ptr = (struct game_cell*)malloc(sizeof(struct game_cell)*hard_game->rows);
                
                for(int y = 0; y < hard_game->rows; y++) {

                    hard_game->board_ptr[x].cells_ptr[y].c_stat = HIDDEN;
                    hard_game->board_ptr[x].cells_ptr[y].display_char = ' ';

                }

            }

            //call set_bombs, passing in the created game_board array
            if(hard_game == NULL) {
                printf("Error: game board array not created properly.");
                return hard_game;
                exit(1);
            }
            else{

                set_bombs(hard_game);
                return hard_game;
            }

    }

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

void print_board(enum difficulty game_difficulty) {

    switch(game_difficulty) {
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

int main() {
enum difficulty game_difficulty = select_difficulty();
print_board(game_difficulty);

};
