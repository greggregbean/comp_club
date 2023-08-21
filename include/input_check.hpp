#pragma once

#include <iostream>
#include <fstream>
#include <string>

enum class input {
    correct   = 1,
    incorrect = 0
};

input num_of_tables_correct (char* line_buf);
input time_correct (char* line_buf);
input input_check (std::ifstream& i_file);








