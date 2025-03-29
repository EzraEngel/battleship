#include <iostream>
#include <string>
#include <string.h>
#include <map>
#include <random>
#include <vector>
#include "player.h"

using namespace std;

// LEAD DECLARATIONS

Lead::Lead(int first_row_tmp, int first_col_tmp, char type_tmp, int length_tmp, map<char,int>* ship_map_tmp) {
  first_row = first_row_tmp;
  first_col = first_col_tmp;
  type = type_tmp;
  length = length_tmp;
  ship_map_ptr = ship_map_tmp;
}

int Lead::health() {
  map<char,int> ship_map= *ship_map_ptr;
  return ship_map[type];
}

bool Lead::bracketing() {
  return (direction=='U');
}

bool Lead::strafing() {
  return (direction!='U' && !terminus_found);
}

bool Lead::back_tracking() {
  return (direction!='U' && terminus_found);
}


//ComputerAI Declarations

// ####################################################################################################################################################################
// Class Member Initializers ##########################################################################################################################################
// I've avoided using a classical constructor here due to the requirement of a guess before setting
// most of the variables. Default values wouldn't have any logical meaning outside the existence of
// an actual guess.

void ComputerAI::set_map(map<char,int>* ship_map_adr) {
  ship_map_ptr = ship_map_adr;
}

void ComputerAI::new_lead(char strike_code, map<char,int>ship_map, vector<int> comp_guess) {
  if (strike_code != 'X' && strike_code != ' ') {
    Lead new_lead(comp_guess[0],comp_guess[1],strike_code,ship_map[strike_code],ship_map_ptr);
    leads.push_back(new_lead);
  }
}

// ######################################################################################################################################################################
// Primary Computer Logic Flow ##########################################################################################################################################
// computer_guess defines logic flow for different types of guesses while update_leads defines how
// the lead vector is updated based on what information is already known about the ship and what new
// information the computer has learned.

vector<int> ComputerAI::computer_guess() {
  if (leads.empty()) {
    return random_guess();
  }
  else if (leads[0].bracketing()) {
    return bracket();
  }
  else if (leads[0].strafing()) {
    return strafe();
  }
  else if (leads[0].back_tracking()) {
    return back_track();
  }
  else {
    return random_guess();
  }
}

int ComputerAI::update_leads(char strike_code, map<char,int>ship_map, vector<int> comp_guess) {
  if (strike_code != 'X' && strike_code != ' ') {
    if (!lead_exists(strike_code)) {
      new_lead(strike_code, ship_map, comp_guess);
      return 0;
    }
  }
  if (!leads.empty() && strike_code!='X') {
    if (leads[0].health()==0) {
      leads.erase(leads.begin());
      center_target();
      return 0;
    }
    if (leads[0].type==strike_code && leads[0].bracketing()) {
      set_direction();
      center_target();
      return 0;
    }
    if (leads[0].strafing() && strike_code!=leads[0].type) {
      leads[0].terminus_found = true;
      center_target();
      return 0;
    }
    if (leads[0].back_tracking() && strike_code!=leads[0].type) {
      leads.erase(leads.begin());
      center_target();
      return 0;
    }
    else {
      return 0;
    }
  }
  return 0;
}

// ####################################################################################################################################################################
// Guess Type definitions #############################################################################################################################################
// Describes computer guess logic for different guessing strategies dictated by main guess logic loop
// computer_guess and update_lead functions.

vector<int> ComputerAI::random_guess() {
  uniform_int_distribution<int> distribution10(0, 10);
  default_random_engine generator(time(nullptr));
  int row = distribution10(generator);
  int col = distribution10(generator);
  vector<int> comp_guess = {row,col};
  last_row = row;
  last_col = col;
  return comp_guess;
}

vector<int> ComputerAI::bracket() {
  vector<int> comp_guess = {leads[0].first_row, leads[0].first_col};
  switch (bracket_dir) {
    case 'N':
      comp_guess[0]--;
      break;
    case 'E':
      comp_guess[1]--;
      break;
    case 'S':
      comp_guess[0]++;
      break;
    case 'W':
      comp_guess[1]++;
      break;
    default:
      return comp_guess;
  }
  if (comp_guess[0]<0 || comp_guess[0]>9 || comp_guess[1]<0 || comp_guess[1]>9) {
    comp_guess = {last_row, last_col};
  }
  rotate_bracket();
  return comp_guess;
}

vector<int> ComputerAI::strafe() {
  if (leads[0].direction=='H') {
    last_col++;
  }
  else {
    last_row++;
  }
  vector<int> computer_guess = {last_row, last_col};
  return computer_guess;
}

vector<int> ComputerAI::back_track() {
  if (leads[0].direction=='H') {
    last_col--;
  }
  else {
    last_row--;
  }
  vector<int> computer_guess = {last_row, last_col};
  return computer_guess;
}

// ####################################################################################################################################################################
//Lead Logic Helper Functions #########################################################################################################################################

bool ComputerAI::lead_exists(char strike_code) {
  bool lead_exists = false;
  for (Lead lead:leads) {
    if (lead.type==strike_code) {
      lead_exists=true;
    }
  }
  return lead_exists;
}

Lead ComputerAI::get_lead(char strike_code) {
  for (Lead lead:leads) {
    if (lead.type==strike_code) {
      return lead;
    }
  }
  Lead normal(0,0,'U',0,nullptr);
  return normal;
}

// ####################################################################################################################################################################
// Pull strike feedback into the class ################################################################################################################################

void ComputerAI::update_strike_code(char strike_code) {
  last_guess = strike_code;
}


// ####################################################################################################################################################################
// Class Member update functions ######################################################################################################################################

void ComputerAI::set_direction() {
  if (bracket_dir=='N' || bracket_dir=='S') {
    leads[0].direction = 'H';
  }
  else {
    leads[0].direction = 'V';
  }
}

void ComputerAI::rotate_bracket() {
  switch (bracket_dir) {
  case 'N':
    bracket_dir = 'E';
    break;
  case 'E':
    bracket_dir = 'S';
    break;
  case 'S':
    bracket_dir = 'W';
    break;
  case 'W':
    bracket_dir = 'N';
    break;
  }
}

void ComputerAI::center_target() {
  last_row=leads[0].first_row;
  last_col=leads[0].first_col;
}

