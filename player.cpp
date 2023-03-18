#include <iostream>
#include <string>
#include <string.h>
#include <map>
#include <random>
#include <vector>

using namespace std;

class Lead {
  public:
    int first_row;
    int first_col;
    bool terminus_found=false;
    char direction='U';
    char type;
    int length;

    Lead(int first_row_tmp, int first_col_tmp, char type_tmp, int length_tmp) {
      first_row = first_row_tmp;
      first_col = first_col_tmp;
      type = type_tmp;
      length = length_tmp;
    }

    int health(map<char,int> ship_map) {
      return ship_map[type];
    }

    bool bracketing() {
      return (direction=='U');
    }

    bool strafing() {
      return (direction!='U' && !terminus_found);
    }

    bool back_tracking() {
      return (direction!='U' && terminus_found);
    }
};

class ComputerAI {
  public:
    vector<Lead> leads;
    int last_row;
    int last_col;
    char last_guess;
    char bracket_dir='N';

    void update_strike_code(char strike_code) {
      last_guess = strike_code;
    }

    void new_lead(char strike_code, map<char,int>ship_map, vector<int> comp_guess) {
      if (strike_code != 'X' && strike_code != ' ') {
        Lead new_lead(comp_guess[0],comp_guess[1],strike_code,ship_map[strike_code]);
        leads.push_back(new_lead);
      }
    }

    void set_direction() {
      if (bracket_dir=='N' || bracket_dir=='S') {
        leads[0].direction = 'H';
      }
      else {
        leads[0].direction = 'V';
      }
    }

    bool lead_exists(char strike_code) {
      bool lead_exists = false;
      for (Lead lead:leads) {
        if (lead.type==strike_code) {
          lead_exists=true;
        }
      }
      return lead_exists;
    }

    Lead get_lead(char strike_code) {
      for (Lead lead:leads) {
        if (lead.type==strike_code) {
          return lead;
        }
      }
      Lead normal(0,0,'U',0);
      return normal;
    }

    void center_target() {
      last_row=leads[0].first_row;
      last_col=leads[0].first_col;
    }

    int update_leads(char strike_code, map<char,int>ship_map, vector<int> comp_guess) {
      if (strike_code != 'X' && strike_code != ' ') {
        if (!lead_exists(strike_code)) {
          new_lead(strike_code, ship_map, comp_guess);
          return 0;
        }
      }
      if (!leads.empty() && strike_code!='X') {
        if (leads[0].health(ship_map)==0) {
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

    void rotate_bracket() {
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
    
    vector<int> random_guess() {
      uniform_int_distribution<int> distribution10(0, 10);
      default_random_engine generator(time(nullptr));
      int row = distribution10(generator);
      int col = distribution10(generator);
      vector<int> comp_guess = {row,col};
      last_row = row;
      last_col = col;
      return comp_guess;
    }

    vector<int> bracket() {
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

    vector<int> strafe() {
      if (leads[0].direction=='H') {
        last_col++;
      }
      else {
        last_row++;
      }
      vector<int> computer_guess = {last_row, last_col};
      return computer_guess;
    }

    vector<int> back_track() {
      if (leads[0].direction=='H') {
        last_col--;
      }
      else {
        last_row--;
      }
      vector<int> computer_guess = {last_row, last_col};
      return computer_guess;
    }

    vector<int> computer_guess() {
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
};

class Player {
  private:
  	bool is_computer = false;
  	bool winner = false;
};