#include "../include/comp_club.hpp"


namespace comp_club {

//------------------
// Table
//------------------
    void table::dump() {
        std::cout << "\t Activity:   " << active     << std::endl 
                  << "\t Client:     " << cl_name    << std::endl
                  << "\t Start time: " << start_time << std::endl
                  << "\t End time:   " << end_time   << std::endl
                  << "\t Total time: " << total_time << std::endl;
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
        for (size_t i = 1; i <= num_of_tables; ++i) {
            std::cout << "Table №" << i << ":" << std::endl;
            room[i].dump();
        }
        std::cout << std::endl << "Queue: ";
        for (size_t i = 0; i < queue.size(); ++i) {
            std::cout << "\t\"" << queue[i] << "\"" << std::endl;
        }
        std::cout << std::endl;
    }

//-------------------------
// All for handling events
//-------------------------
    bool comp_club_data::working (const std::string& time) {
        size_t time_m = time_to_minutes(time);
        return time_m >= opening_m && time_m <= closing_m;
    }

    bool comp_club_data::in_the_club (const std::string& cl_name) {
        // Looking in queue
        for (size_t i = 0; i < queue.size(); ++i) {
            if (!queue[i].compare(cl_name)) return true;
        }

        // Looking in room
        for (size_t i = 1; i <= num_of_tables; ++i) {
            if (!room[i].get_cl_name().compare(cl_name)) return true;
        }

        return false;
    }

    void comp_club_data::handle_cl_enter (std::ifstream& i_file, const std::string& e_time) {
        std::string cl_name;
        i_file >> cl_name;

        if (!working(e_time)) {
            std::cout << e_time << " " << static_cast<short>(i_event::cl_enter) 
                      << " " << cl_name << std::endl;
            print_error(e_time, errors::NotOpenYet);
        }
        
        else if (in_the_club(cl_name)) {
            std::cout << e_time << " " << static_cast<short>(i_event::cl_enter) 
                      << " " << cl_name << std::endl;
            print_error(e_time, errors::YouShallNotPass);
        }

        else {
            queue.push_back(cl_name);
        }

        dump();
    }

    void comp_club_data::handle_event (std::ifstream& i_file, i_event event_id, const std::string& e_time) {

        switch (event_id) {
            case i_event::cl_enter:
                handle_cl_enter(i_file, e_time);
                break;
            case i_event::cl_take_table:
                i_file.ignore(line_len, '\n');
                //handle_cl_take_table(i_file, e_time);
                break;
            case i_event::cl_is_waiting:
                i_file.ignore(line_len, '\n');
                //handle_cl_is_waiting(i_file, e_time);
                break;
            case i_event::cl_quit:
                i_file.ignore(line_len, '\n');
                //handle_cl_quit(i_file, e_time);
                break;
        }
    }

    void comp_club_data::event_handler (std::ifstream& i_file) {
        std::string event_time;
        short       event_id;
        
        i_file >> event_time;
        i_file >> event_id;

        while (!i_file.eof()) {          
            handle_event(i_file, static_cast<i_event> (event_id), event_time);
            i_file >> event_time;
            i_file >> event_id;
        }
    }

    void print_error(const std::string& time, errors error_id) {
        std::cout << time << " 13 ";
        switch (error_id) {
            case errors::ClientUnknown:
                std::cout << "ClientUnknown" << std::endl;
                break;
            case errors::ICanWaitNoLonger:
                std::cout << "ICanWaitNoLonger!" << std::endl;
                break;
            case errors::PlaceIsBusy:
                std::cout << "PlaceIsBusy" << std::endl;
                break;
            case errors::NotOpenYet:
                std::cout << "NotOpenYet" << std::endl;
                break;
            case errors::YouShallNotPass:
                std::cout << "YouShallNotPass" << std::endl;
                break;
        }
    }

}