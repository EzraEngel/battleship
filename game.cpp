#include <iostream>
#include <string>
#include <string.h>
#include <map>
#include <random>
#include "ascii_art.cpp"
#include "board.cpp"
#include "player.cpp"

using namespace std;

class Game {
  private:
  	ASCII text_gen;
  	bool game_is_over = false;
  
  public:
  	Board player_board;
  	Board computer_board;
  	Player player;
  	Player computer;

  	Game(ASCII text_var, Board board_p, Board board_c, Player player_p, Player player_c) {
  	  player_board=board_p;
  	  computer_board=board_c;
  	  player = player_p;
  	  computer = player_c;
  	  text_gen = text_var;
  	}

  	bool is_over() {
  	  return game_is_over;
  	}

  	void play_intro() {
  	  text_gen.welcome_to();
  	  text_gen.battleship();
  	  player_board.display(false);
  	}

  	void place_ships() {
  	  string ships[5] = {"Carrier","Battleship","Cruiser","Submarine","Destroyer"};
  	  map<string,char> ship_codes{{"Carrier",'A'},
  	  							  {"Battleship",'B'},
  	  							  {"Cruiser",'C'},
  	  							  {"Submarine",'S'},
  	  							  {"Destroyer",'D'}};
  	  for (string ship:ships) {
  	  	bool ship_placed = false;
  	  	while (!ship_placed) {
  	  	  string coordinate;
          char direction;
  	  	  cout << "Place your " << ship << "!" << endl;
          cout << "Choose a coordinate: ";
          cin >> coordinate;
          cout << "Choose a direction (R/D): ";
          cin >> direction;
          ship_placed = player_board.emplace_ship(coordinate,direction,ship_codes[ship],true);
          player_board.display(true);
  	  	}
  	  }
  	}

  	void randomize_ships() {
  	  char ships[5] = {'A','B','C','S','D'};
      uniform_int_distribution<int> distribution10(0, 10);
  	  uniform_int_distribution<int> distribution2(0, 2);
  	  default_random_engine generator(time(nullptr));
  	  int row_index, col_index, RD_index;
      char row, col, direction;
      string RD="RD", coordinate = "--";

  	  for (char ship:ships) {
  	  	bool ship_placed = false;
  	  	while (!ship_placed) {
          row_index = distribution10(generator);
          col_index = distribution10(generator);
          RD_index = distribution2(generator);
          row = computer_board.get_rows()[row_index];
          col = computer_board.get_cols()[col_index];
          direction = RD[RD_index];
          coordinate[0] = row;
          coordinate[1] = col;
          ship_placed = computer_board.emplace_ship(coordinate,direction,ship,true);
  	  	}
  	  }
  	}

  	void strike_feedback(char strike_code) {
  	  if (strike_code == ' ') {
  	  	text_gen.miss();
  	  }
  	  else if (strike_code == 'X') {
        text_gen.invalid();
  	  }
  	  else {
  	  	computer_board.damage_ship(strike_code, text_gen);
  	  }
  	  computer_board.display(false);
  	}

  	void player_strike() {
  	  string player_guess;
      cout << "Strike your opponent!" << endl;
      cout << "Coordinate: ";
  	  cin >> player_guess;
   	  char strike_code = computer_board.strike(player_guess);
   	  strike_feedback(strike_code);
  	}

  	void computer_strike() {
  	  uniform_int_distribution<int> distribution10(0, 10);
  	  default_random_engine generator(time(nullptr));
  	  int row_index, col_index;
      char row, col;
      bool good_strike = false;
      while (!good_strike) {
      	string computer_guess = "--";
      	row_index = distribution10(generator);
        col_index = distribution10(generator);
        row = computer_board.get_rows()[row_index];
        col = computer_board.get_cols()[col_index];
        computer_guess[0] = row;
        computer_guess[1] = col;
      	char strike_code = player_board.strike(computer_guess);
        if (strike_code=='X') {
          good_strike = false;
        }
        else if (strike_code==' ') {
          cout << "Computer guessed: " << computer_guess << "." << endl;
          text_gen.miss();
          good_strike = true;
        }
        else {
          cout << "Computer guessed: " << computer_guess << "." << endl;
          player_board.damage_ship(strike_code, text_gen);
          good_strike=true;
        }
      }
  	}
};