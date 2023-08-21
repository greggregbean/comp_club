#include "../include/comp_club.hpp"

int main (int argc, char* argv []) {
    if (argc == 1) {
        std::cout << "No input file." << std::endl;
    }

    else {
        std::ifstream i_file;
        i_file.open(argv[1], std::ios::in);
        char line_buf [1000];
        size_t cur_line = 0;

        size_t num_of_tables;
        std::string opening;
        std::string closing;
        size_t cost_per_hour;

        if (i_file.is_open()) {
            i_file.getline(line_buf, 1000);

            i_file >> num_of_tables;


            i_file >> opening;
            // if ((comp_club::time_to_minutes(opening) < 0) || 
            //     (comp_club::time_to_minutes(opening) > 24 * 60)) {
            //         std::cout << "Incorrect opening time!!!" << std::endl
            //     }
            i_file >> closing;
            i_file >> cost_per_hour;
        }
        comp_club::comp_club_data day_data (num_of_tables, opening, closing, cost_per_hour);
        day_data.dump();

        //day_data.event_handler(i_file);

    }
}