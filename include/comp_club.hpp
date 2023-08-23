#pragma once

#include <map>
#include <vector>
#include <set>

#include "./input_check.hpp"

namespace comp_club {

struct pos {
    char q_or_r; // determines if a client in queue or in room
    size_t num;  // determines client's number of table or position in queue
};

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

struct table {
    bool active = false;
    std::string cl_name;
    std::size_t start_time_m; 
    size_t total_time = 0;
    size_t total_sum  = 0;

    void dump ();
    size_t end_session(const std::string& end_time);

};

class comp_club_data {
    size_t num_of_tables;

    std::string  opening;
    size_t opening_m = 0;

    std::string  closing;
    size_t closing_m = 0;

    size_t cost_per_hour;

    std::map    <size_t, table> room;
    std::vector <std::string>   queue;


    public:
        comp_club_data (const size_t& i_num_of_tables, 
                        const std::string&  i_opening, 
                        const std::string&  i_closing,  
                        const size_t& i_cost_per_hour) : 

                        num_of_tables (i_num_of_tables),
                        opening       (i_opening),
                        opening_m     (time_to_minutes(i_opening)),
                        closing       (i_closing), 
                        closing_m     (time_to_minutes(i_closing)),     
                        cost_per_hour (i_cost_per_hour) {}
        void dump ();
        void event_handler (std::ifstream& i_file); 

    private:
        // All for monitoring and changing comp_club_data
        void end_session  (size_t table, const std::string end_time);
        bool working      (const std::string& time);
        pos  in_da_club   (const std::string& cl_name);
        void place_client (const std::string& start_time, const std::string& name, 
                           size_t table, const pos& prev_pos);
        size_t free_table ();

        // All for handling i_events:
        void handle_cl_enter      (std::ifstream& i_file, const std::string& e_time);
        void handle_cl_take_table (std::ifstream& i_file, const std::string& e_time);
        void handle_cl_is_waiting (std::ifstream& i_file, const std::string& e_time);
        void handle_cl_quit       (std::ifstream& i_file, const std::string& e_time);
        void handle_event         (std::ifstream& i_file, i_event event_id, const std::string& e_time);

        // All for generating o_events:
        void generate_error         (const std::string& time, errors error_id);
        void generate_cl_quit       (const std::string& time, const std::string& cl_name);
        void generate_cl_take_table (const std::string& time, const std::string& cl_name, size_t table);
        
};

}