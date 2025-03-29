#pragma once

#include <iostream>
#include <string>

class ASCII {
public:
    // General layout and control
    void new_screen();
    void new_page();
    void h_bar();

    // Intro and instructions
    void welcome_to();
    void instructions();
    void your_fleet();

    // Player headers
    void player();
    void computer();

    // Ship names
    void ship(char type);
    void carrier();
    void battleship();
    void cruiser();
    void destroyer();
    void submarine();

    // Combat feedback
    void hit();
    void miss();
    void sunk();
    void invalid();

    // Game outcome
    void you_win();
    void you_lose();
};
