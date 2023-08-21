#include "../include/input_check.hpp"

input num_of_tables_correct (char* line_buf) {
    int num_of_tables = std::atoi(line_buf);

    if (num_of_tables == 0) {
        return input::incorrect;
    } 

    else if (num_of_tables < 0) {
        return input::incorrect;
    }

    return input::correct;
}

// input time_correct (char* line_buf) {

//     return input::correct;
// }

input input_check (std::ifstream& i_file) {
    if (!i_file.is_open()) 
        return input::incorrect;

    char line_buf [1000];

    i_file.getline(line_buf, 1000);
    if (num_of_tables_correct(line_buf) == input::incorrect) {
        std::cout << line_buf << std::endl;
        return input::incorrect;
    }

    // i_file.getline(line_buf, 1000);
    // if(time_correct(line_buf) == input::incorrect) {
    //     std::cout << line_buf << std::endl;
    //     return input::incorrect;
    // }

    return input::correct;
}