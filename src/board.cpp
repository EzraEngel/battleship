#include <iostream>
#include <string>
#include <string.h>
#include <map>
#include <random>
#include <tuple>
#include "ascii_art.h"
#include "board.h"

using namespace std;


Board::Board() {
  ship_map['A'] = 5;
  ship_map['B'] = 4;
  ship_map['C'] = 3;
  ship_map['S'] = 3;
  ship_map['D'] = 2;
}

void Board::damage_ship(char type, ASCII text_gen) {
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

int Board::health() {
  int total_health=0;
  for (auto const& ship_health:ship_map) {
  	total_health = total_health + ship_health.second;
  }
  return total_health;
}

string Board::get_cols() {
  return column_names;
}

string Board::get_rows() {
  return row_names;
}

void Board::display(bool vis) {
  cout << endl;
  print_header();
  print_hline();
  for (int i=0; i<10; i++) {
  	print_row(i, vis);
  	print_hline();
  }
}

void Board::print_header() {
  leading_whitespace();
  cout << "  |";
  for (int i=0; i<10; i++) {
  	cout << " " << column_names[i] << " |";
  }
  cout << endl;
}

void Board::print_hline() {
  leading_whitespace();
  cout << "--+";
  for (int i=0; i<10; i++) {
  	cout << "---+";
  }
  cout << endl;
}

void Board::leading_whitespace() {
  cout << "                         ";
}

void Board::print_row(int row_index, bool vis) {
  leading_whitespace();
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

char Board::strike(string coordinate) {
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

int Board::get_index(char name, string name_list) {
  int i = 0;
  for (char letter:name_list) {
    if (name==letter) {
    	break;
    }
    i++;
  }
  return i;
}

bool Board::valid_coordinate(string coordinate) {
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

bool Board::emplace_ship(string coordinate, char direction, char type, bool silence) {
  string output;
  if (!valid_coordinate(coordinate)) {
  	output = (!silence) ? "                         Bad coordinate.\n" : "";
  	cout << output;
    return false;	
  }
  else if (direction!='R'&&direction!='D') {
  	output = (!silence) ? "                         Bad direction.\n" : "";
  	cout << output;
  	return false;
  }
  else if (!ship_fits_on_board(coordinate,direction,type)) {
  	output = (!silence) ? "                         Ship does not fit on board.\n" : "";
  	cout << output;
  	return false;
  }
  else if (ship_overlaps(coordinate,direction,type)) {
  	output = (!silence) ? "                         Ship overlaps another ship.\n" : "";
  	cout << output;
  	return false;
  }
  else {
  	lay_ship(coordinate,direction,type);
  	output = (!silence) ? "                         Good placement.\n" : "";
  	cout << output;
  	return true;
  }
  return false;
}

bool Board::ship_fits_on_board(string coordinate, char direction, char type) {
  int col_index = get_index(coordinate[1], column_names);
  int row_index = get_index(coordinate[0], row_names);
  switch (direction) {
    case 'R':
      return col_index+ship_map[type]<11;
      break;
    case 'D':
      return row_index+ship_map[type]<11;
      break;
    default:
      cout << "Direction is invalid. Enter R or D." << endl;
  	  return false;
  }
  return false;
}

bool Board::ship_overlaps(string coordinate, char direction, char type) {
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

void Board::lay_ship(string coordinate, char direction, char type) {
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

string Board::guess_to_string(vector<int> guess_vec) {
  string guess_str = "--";
  guess_str[0] = row_names[guess_vec[0]];
  guess_str[1] = column_names[guess_vec[1]];
  return guess_str;
}