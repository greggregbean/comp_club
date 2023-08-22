#pragma once

#include <map>
#include <vector>

#include "./input_check.hpp"

namespace comp_club {

enum class i_event {
    cl_enter      = 1,
    cl_take_table = 2,
    cl_is_waiting = 3,
    cl_quit       = 4
};

enum class o_event {
    cl_quit       = 11,
    cl_take_table = 12,
    error         = 13
};

enum class errors {
    ClientUnknown, 
    ICanWaitNoLonger, 
    PlaceIsBusy, 
    NotOpenYet, 
    YouShallNotPass
};

class table {
    private:
        bool active = false;
        std::string cl_name;
        std::size_t start_time; 
        std::size_t end_time;
        size_t total_time = 0;

    public:
        void dump ();
        const std::string& get_cl_name() { return cl_name; }

};

class comp_club_data {
    private:
        size_t num_of_tables;

        std::string  opening;
        size_t opening_m = 0;

        std::string  closing;
        size_t closing_m = 0;

        size_t cost_per_hour;

        std::map    <int, table>  room;
        std::vector <std::string> queue;

    public:
        comp_club_data (const size_t& i_num_of_tables, 
                        const std::string&  i_opening, 
                        const std::string&  i_closing,  
                        const size_t& i_cost_per_hour);
        void dump ();

        // All for handle events:
        bool working     (const std::string& time);
        bool in_the_club (const std::string& cl_name);
        void handle_cl_enter      (std::ifstream& i_file, const std::string& e_time);
        void handle_cl_take_table (std::ifstream& i_file, const std::string& e_time);
        void handle_cl_is_waiting (std::ifstream& i_file, const std::string& e_time);
        void handle_cl_quit       (std::ifstream& i_file, const std::string& e_time);
        void handle_event  (std::ifstream& i_file, i_event event_id, const std::string& e_time);
        void event_handler (std::ifstream& i_file); 

};

void print_error(const std::string& time, errors erorr_id);


}