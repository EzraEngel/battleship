#pragma once

#include <string>
#include <vector>
#include "ascii_art.h"
#include "board.h"
#include "player.h"

class Game {
private:
    ASCII text_gen;
    bool game_is_over = false;

public:
    Player player;
    Player computer;
    Board player_board;
    Board computer_board;
    ComputerAI comp_ai;

    Game(ASCII text_var, Board board_p, Board board_c, Player player_p, Player player_c);

    bool is_over();
    std::string to_upper(std::string lower_string);
    void play_intro();
    void place_ships();
    void randomize_ships();
    void strike_feedback(char strike_code);
    void player_strike();
    void computer_strike();
    void check_win_state();
    void conclude();
    void computer_thinks();
};
