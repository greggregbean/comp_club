#include "../include/comp_club.hpp"

namespace comp_club {

    //------------------
    // Table
    //------------------

    void table::dump() {
        std::cout << "\t Activity: "      << active        << std::endl 
                  << "\t Client: "        << client        << std::endl
                  << "\t Start time: "    << start_time    << std::endl
                  << "\t End time: "      << end_time      << std::endl
                  << "\t Total time: "    << total_time    << std::endl;
    }

    //------------------
    // Comp_club_data
    //------------------

    comp_club_data::comp_club_data (const size_t& i_num_of_tables, 
                                    const std::string&  i_opening, 
                                    const std::string&  i_closing,  
                                    const size_t& i_cost_per_hour) : 

                                    num_of_tables (i_num_of_tables),
                                    opening       (i_opening),
                                    opening_m     (time_to_minutes(i_opening)),
                                    closing       (i_closing), 
                                    closing_m     (time_to_minutes(i_closing)),     
                                    cost_per_hour (i_cost_per_hour) {}

    void comp_club_data::dump () {
        std::cout << "Num of tables: " << num_of_tables << std::endl
                  << "Opening: " << opening << "(" << opening_m << ")" << std::endl
                  << "Closing: " << closing << "(" << closing_m << ")" << std::endl
                  << "Cost per hour: " << cost_per_hour << std::endl << std::endl;
        for (size_t i = 0; i < num_of_tables; ++i) {
            std::cout << "Table №" << i << ":" << std::endl;
            room[i].dump();
        }
    }

    // bool comp_club_data::time_correct(const std::string& time) {
    //     bool correct = true;

    //     return correct;
    // }

    // void comp_club_data::event_handler (const std::ifstream& i_file) {
    //     std::string event_time;
    //     if (time_correct(event_time)) {

    //     }
    // }

}