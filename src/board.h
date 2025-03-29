#pragma once

#include <string>
#include <map>
#include <vector>

// Forward declaration instead of including "ascii.h"
class ASCII;

// Represents a single tile on the game board
class Tile {
public:
    bool hit = false;
    char ship = ' ';
};

// Manages the state and rendering of a player's or computer's game board
class Board {
private:
    [[maybe_unused]] int board_size = 10;
    Tile state[10][10];
    std::string column_names = "123456789X";
    std::string row_names = "ABCDEFGHIJ";

    void print_header();
    void print_hline();
    void print_row(int row_index, bool vis);
    void lay_ship(std::string coordinate, char direction, char type);
    bool ship_fits_on_board(std::string coordinate, char direction, char type);
    bool ship_overlaps(std::string coordinate, char direction, char type);
    int get_index(char name, std::string name_list);
    bool valid_coordinate(std::string coordinate);

public:
    std::map<char, int> ship_map;

    Board();

    void display(bool vis);
    void leading_whitespace();

    char strike(std::string coordinate);
    int health();
    void damage_ship(char type, ASCII text_gen);

    std::string get_cols();
    std::string get_rows();
    std::string guess_to_string(std::vector<int> guess_vec);

    bool emplace_ship(std::string coordinate, char direction, char type, bool silence);
};
