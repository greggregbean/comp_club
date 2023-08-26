#include "../include/comp_club.hpp"
#include "../include/input_check.hpp"

int main (int argc, char* argv []) {
    if (argc == 1) {
        std::cout << "No input file." << std::endl;
    }

    else {
        std::ifstream i_file;

        i_file.open(argv[1], std::ios::in);
        
        // Firstly check correctness of data
        if (!ic::input_check(i_file)) {
            return -1;
        }
        i_file.seekg(0);

        size_t num_of_tables;
        std::string opening;
        std::string closing;
        size_t cost_per_hour;

        i_file >> num_of_tables;
        i_file >> opening;
        i_file >> closing;
        i_file >> cost_per_hour;

        comp_club::comp_club_data day_data (num_of_tables, opening, closing, cost_per_hour);
        
        std::cout << opening << std::endl;
        day_data.event_handler(i_file);
        day_data.end_day();
        std::cout << closing << std::endl;
        day_data.show_day_data();
    }
}