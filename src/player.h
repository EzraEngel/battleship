#pragma once

#include <vector>
#include <map>

// Represents an enemy ship once it's hit by the computer and being tracked
class Lead {
public:
    int first_row;
    int first_col;
    bool terminus_found = false;
    char direction = 'U';
    char type;
    int length;
    std::map<char, int>* ship_map_ptr;

    Lead(int first_row_tmp, int first_col_tmp, char type_tmp, int length_tmp, std::map<char, int>* ship_map_tmp);

    int health();
    bool bracketing();
    bool strafing();
    bool back_tracking();
};

// Represents the AI logic for the computer player
class ComputerAI {
public:
    std::vector<Lead> leads;
    int last_row;
    int last_col;
    char last_guess;
    char bracket_dir = 'N';
    std::map<char, int>* ship_map_ptr;

    void set_map(std::map<char, int>* ship_map_adr);
    void new_lead(char strike_code, std::map<char, int> ship_map, std::vector<int> comp_guess);
    std::vector<int> computer_guess();
    int update_leads(char strike_code, std::map<char, int> ship_map, std::vector<int> comp_guess);
    void update_strike_code(char strike_code);

private:
    std::vector<int> random_guess();
    std::vector<int> bracket();
    std::vector<int> strafe();
    std::vector<int> back_track();

    bool lead_exists(char strike_code);
    Lead get_lead(char strike_code);

    void set_direction();
    void rotate_bracket();
    void center_target();
};

// Represents a human or computer-controlled player (stubbed for now)
class Player {
private:
    [[maybe_unused]] bool is_computer = false;
    [[maybe_unused]] bool winner = false;
};
