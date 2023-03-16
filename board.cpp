#include <iostream>
#include <string>
#include <string.h>
#include <map>
#include <random>
#include "ascii_art.cpp"

using namespace std;

class Player {
  private:
  	bool is_computer = false;
  	bool winner = false;
};

class Tile {
  public:
  	bool hit = false;
  	char ship = ' ';
};

class Board {
  private:
    int board_size = 10;
    Tile state[10][10];
    string column_names = "123456789X";
    string row_names = "ABCDEFGHIJ";
    map<char,int>ship_map;

  public:
  	Board() {
  	  ship_map['A'] = 5;
  	  ship_map['B'] = 4;
  	  ship_map['C'] = 3;
  	  ship_map['S'] = 3;
  	  ship_map['D'] = 2;
  	}

  	void damage_ship(char type, ASCII text_gen) {
  	  ship_map[type]--;
  	  if (ship_map[type]==0) {
  	  	text_gen.sunk();
  	  	text_gen.ship(type);
  	  }
  	  else {
  	  	text_gen.hit();
  	  	text_gen.ship(type);
  	  }
  	}

  	string get_cols() {
  	  return column_names;
  	}

  	string get_rows() {
  	  return row_names;
  	}

    void display(bool vis) {
      cout << endl;
      print_header();
      print_hline();
      for (int i=0; i<10; i++) {
      	print_row(i, vis);
      	print_hline();
      }
    }

    void print_header() {
      cout << "  |";
      for (int i=0; i<10; i++) {
      	cout << " " << column_names[i] << " |";
      }
      cout << endl;
    }

    void print_hline() {
      cout << "--+";
      for (int i=0; i<10; i++) {
      	cout << "---+";
      }
      cout << endl;
    }

    void print_row(int row_index, bool vis) {
      cout << row_names[row_index] << " |";
      for (int i=0; i<10; i++) {
      	if (!state[i][row_index].hit) {
      	  vis ? cout << " " << state[i][row_index].ship << " |" : cout << "   |";
      	}
      	else if (state[i][row_index].hit && state[i][row_index].ship==' ') {
      	  cout << " O |";
      	}
      	else {
      	  cout << " X |";
      	}
      }
      cout << endl;
    }

    char strike(string coordinate) {
      if (valid_coordinate(coordinate)) {
        int i = get_index(coordinate[1], column_names);
        int j = get_index(coordinate[0], row_names);
        if (state[i][j].hit == false) {
          state[i][j].hit = true;
          return state[i][j].ship;
        }
        else {
          return 'X';
        }
      }
      else {
      	return 'X';
      }
    }

    int get_index(char name, string name_list) {
      int i = 0;
      for (char letter:name_list) {
        if (name==letter) {
        	break;
        }
        i++;
      }
      return i;
    }

    bool valid_coordinate(string coordinate) {
      bool row_valid = false;
      bool column_valid = false;
      for (char letter:row_names) {
      	if (coordinate[0]==letter) {
      	  row_valid = true;
      	}
      }
      for (char number:column_names) {
      	if (coordinate[1]==number) {
      	  column_valid = true;
      	}
      }
      return (row_valid && column_valid);
    }

    bool emplace_ship(string coordinate, char direction, char type, bool silence) {
      string output;
      if (!valid_coordinate(coordinate)) {
      	output = (!silence) ? "Bad coordinate.\n" : "";
      	cout << output;
        return false;	
      }
      else if (direction!='R'&&direction!='D') {
      	output = (!silence) ? "Bad direction.\n" : "";
      	cout << output;
      	return false;
      }
      else if (!ship_fits_on_board(coordinate,direction,type)) {
      	output = (!silence) ? "Ship does not fit on board.\n" : "";
      	cout << output;
      	return false;
      }
      else if (ship_overlaps(coordinate,direction,type)) {
      	output = (!silence) ? "Ship overlaps another ship.\n" : "";
      	cout << output;
      	return false;
      }
      else {
      	lay_ship(coordinate,direction,type);
      	output = (!silence) ? "Good placement.\n" : "";
      	cout << output;
      	return true;
      }
      return false;
    }

    bool ship_fits_on_board(string coordinate, char direction, char type) {
      int col_index = get_index(coordinate[1], column_names);
      int row_index = get_index(coordinate[0], row_names);
      switch (direction) {
        case 'R':
          return col_index+ship_map[type]<10;
          break;
        case 'D':
          return row_index+ship_map[type]<10;
          break;
        default:
          cout << "Direction is invalid. Enter R or D." << endl;
      	  return false;
      }
      return false;
    }

    bool ship_overlaps(string coordinate, char direction, char type) {
      int col_index = get_index(coordinate[1], column_names);
      int row_index = get_index(coordinate[0], row_names);
      bool ship_overlaps = false;
      switch (direction) {
        case 'R':
          for (int i=0; i<ship_map[type]; i++) {
          	if (state[col_index+i][row_index].ship!=' ') {
          	  ship_overlaps = true;
          	  break;
          	}
          }
          break;
        case 'D':
          for (int j=0; j<ship_map[type]; j++) {
          	if (state[col_index][row_index+j].ship!=' ') {
          	  ship_overlaps = true;
          	  break;
          	}
          }
          break;
        default:
          cout << "Direction is invalid. Enter R or D." << endl;
      	  return true;
      }
      return ship_overlaps;
    }

    void lay_ship(string coordinate, char direction, char type) {
      int col_index = get_index(coordinate[1], column_names);
      int row_index = get_index(coordinate[0], row_names);
      switch (direction) {
        case 'R':
          for (int i=0; i<ship_map[type]; i++) {
          	state[col_index+i][row_index].ship=type;
          }
          break;
        case 'D':
          for (int j=0; j<ship_map[type]; j++) {
          	state[col_index][row_index+j].ship=type;
          }
          break;
        default:
          cout << "Direction is invalid. Enter R or D." << endl;
      }
    }

};

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
  	text_gen.computer();
  	game.computer_strike();
  }

  return 0;
}