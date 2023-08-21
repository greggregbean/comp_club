#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <map>

namespace comp_club {

enum class i_event {
    cl_enter      = 1,
    cl_take_table = 2,
    cl_is_waiting = 3
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

size_t time_to_minutes (const std::string& time);

class table {
    private:
        bool active = false;
        std::string client;
        std::size_t start_time; 
        std::size_t end_time;
        size_t total_time = 0;

    public:
        table () {}
        void dump ();
};

class comp_club_data {
    private:
        size_t num_of_tables;

        std::string  opening;
        size_t opening_m = 0;

        std::string  closing;
        size_t closing_m = 0;

        size_t cost_per_hour;
        std::map <int, table> room;

    public:
        comp_club_data (const size_t& i_num_of_tables, 
                        const std::string&  i_opening, 
                        const std::string&  i_closing,  
                        const size_t& i_cost_per_hour);

        void dump ();
        bool time_correct (const std::string& time);
        void event_handler (const std::ifstream& i_file); 

};




}