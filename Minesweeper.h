
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



struct game_cell {
    enum cell_status c_stat;
    int has_bomb;
    char display_char;

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
void reveal_cell_init();        //
void reveal_cell_recur();       //
void print_board();
