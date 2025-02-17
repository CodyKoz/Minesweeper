#ifndef Minesweeper_H_
#define Minesweeper_H_

#define TRUE 1
#define FALSE 0


enum difficulty {
    SIMPLE,
    EASY,
    MEDIUM,
    HARD,
};

enum cell_status {
    HIDDEN,
    OPEN,
    FLAGGED,
};

enum game_status {
    MENU,
    PLAYING,
    WON,
    LOST,
};

enum cell_position {
        CENTER,
        LEFT_EDGE,
        RIGHT_EDGE,
        TOP_EDGE,
        BOTTOM_EDGE,
        UL_CORNER,
        UR_CORNER,
        BL_CORNER,
        BR_CORNER,
    };

struct game_cell {

    enum cell_status c_stat;
    int has_bomb;
    char display_char;
    int visited;

};

struct dynamic_array {

    struct game_cell* cells_ptr;

};

struct game_board {

    int rows;
    int cols;
    int number_of_bombs;
    enum difficulty board_difficulty;
    enum game_status g_stat;
    struct dynamic_array* board_ptr;

};

int select_difficulty();
void* create_game_board_array();
void set_bombs();
void print_board();
void reveal_cell_recur();       
void reset_visit_flags();
void reveal_cell_init();        
void reveal_bombs();
int win_check();
void play_game();




#endif /* End Minesweeper_H_ */