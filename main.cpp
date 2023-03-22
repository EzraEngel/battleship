#include <iostream>
#include <string>
#include <string.h>
#include <map>
#include <random>
#include "game.cpp"


using namespace std;

int main() {
  Board player_board;
  Board computer_board;
  Player player;
  Player computer;
  ASCII text_gen;

  Game game(text_gen, player_board, computer_board, player, computer);
  game.play_intro();
  game.place_ships();
  game.randomize_ships();
  while (!game.is_over()) {
  	text_gen.player();
  	game.player_strike();
    if (game.is_over()) {break;}
    game.computer_thinks();
  	text_gen.computer();
  	game.computer_strike();
  }
  game.conclude();

  return 0;
}