#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

size_t time_to_minutes (const std::string& time);

namespace ic {

const size_t line_len = 1000;

bool num_correct        (const std::string& num_s);
bool time_correct       (const std::string& time);
bool cl_name_correct    (const std::string& cl_name);
bool cl_tt_body_correct (const std::string& cl_tt_body, const size_t& num_of_tables);
bool event_correct      (const char* event_line, std::string & last_e_time, const size_t& num_of_tables);
bool input_check        (std::ifstream& i_file);

}






