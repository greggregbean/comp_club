#include "../include/input_check.hpp"

size_t time_to_minutes (const std::string& time) {
    size_t minutes = 0;

    minutes += (time[0] - '0') * 600;
    minutes += (time[1] - '0') * 60;
    minutes += (time[3] - '0') * 10;
    minutes += (time[4] - '0');

    return minutes;
}

namespace ic {

bool num_correct (const std::string& num_s) {
    return (num_s[0] != '0') && std::all_of(num_s.begin(), num_s.end(), ::isdigit) && !num_s.empty();
}

bool time_correct (const std::string& time) {
    if (time[0] >  '2' || time[0] < '0') return false;
    if (time[1] >  '9' || time[1] < '0') return false;
    if (time[2] != ':')                  return false;
    if (time[3] >  '5' || time[3] < '0') return false;
    if (time[4] >  '9' || time[4] < '0') return false;
    if (time_to_minutes(time) > 24 * 60) return false;

    return true;
}

bool cl_name_correct (const std::string& cl_name) {
    return cl_name.find_first_not_of("abcdefghijklmnopqrstuvwxyz0123456789_-") == std::string::npos
           && !cl_name.empty();
}

// --- Check if cl_take_table event body is correct ---
bool cl_tt_body_correct (const std::string& cl_tt_body, const size_t& num_of_tables) {
    if (cl_tt_body.empty()) return false;

    // --- Separate body on 2 parts ---
    std::string cl_name, dest_table;
    auto pos = cl_tt_body.find(" ");
    if (pos != std::string::npos)
    {
        cl_name    = cl_tt_body.substr(0,  pos);
        dest_table = cl_tt_body.substr(pos + 1);
    }
    else return false;

    // --- Check if cl_mane is correct ---
    if (!cl_name_correct(cl_name)) return false;

    // --- Check if destination table is correct ---
    if (!num_correct(dest_table))                return false;
    if (std::stoull(dest_table) > num_of_tables) return false;

    return true;
}

bool event_correct (const char* event_line, std::string & last_e_time, const size_t& num_of_tables) {
    // --- Check if time of event is correct
    std::string e_time {event_line, 5};
    
    if (!time_correct(e_time) || time_to_minutes(e_time) < time_to_minutes(last_e_time)) 
        return false;
    
    // --- Check if space between time and event id is set ---
    if (event_line[5] != ' ') return false;

    // --- Check if i_event id is correct
    if (event_line[6] != '1' && 
        event_line[6] != '2' &&
        event_line[6] != '3' &&
        event_line[6] != '4') return false;
    
    // --- Check if space between event id and event body is set ---
    if (event_line[7] != ' ') return false;

    // --- Check if name of client is correct in no-arg events ---
    if (event_line[6] != '2') {
        std::string cl_name {event_line + 8};
        if (!cl_name_correct(cl_name)) return false;
    }

    // --- Check if name of client and num of table is correct in cl_take_table event ---
    else {
        std::string cl_tt_body {event_line + 8};
        if (!cl_tt_body_correct(cl_tt_body, num_of_tables)) return false;
    }

    last_e_time = e_time;

    return true;
}

bool input_check (std::ifstream& i_file) {
    // --- Check if file was found ---
    if (!i_file.is_open()) 
        return false;

    // --- Check if num_of_tables is correct ---
    char line_buf[line_len];

    i_file.getline(line_buf, line_len);
    std::string num {line_buf};

    if (!num_correct(num)) {
        std::cout << line_buf << std::endl;
        return false;
    }

    size_t num_of_tables = std::stoull(num); // will be neccesary in checking cl_take_table events 

    // --- Check if opening and closing times are correct ---
    i_file.getline(line_buf, line_len);
    std::string opening {line_buf, 5};
    std::string closing {line_buf + 6}; // 5 symbols of time XX:XX and one space symbol

    if (!time_correct(opening)   || !time_correct(closing) || 
        time_to_minutes(opening) >= time_to_minutes(closing)) {
            std::cout << line_buf << std::endl;
            return false;
    }

    // --- Check if cost_per_hour is correct ---
    i_file.getline(line_buf, line_len);

    if (!num_correct(line_buf)) {
        std::cout << line_buf << std::endl;
        return false;
    }

    // --- Check if events are correct ---
    i_file.getline(line_buf, line_len);
    std::string last_e_time {line_buf, 5};

    while (!i_file.eof()) {
        if (!event_correct(line_buf, last_e_time, num_of_tables)) {
            std::cout << line_buf << std::endl;
            return false;
        }
        i_file.getline(line_buf, line_len);
    }

    return true;
}

}