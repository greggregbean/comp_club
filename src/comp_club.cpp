#include "../include/comp_club.hpp"


namespace comp_club {

//-------------
//--- TABLE ---
//-------------
    void table::dump() {
        std::cout << "\t Active:         " << active       << std::endl 
                  << "\t Client:         " << cl_name      << std::endl
                  << "\t Start time (m): " << start_time_m << std::endl
                  << "\t Total time:     " << total_time   << std::endl
                  << "\t Total sum:      " << total_sum    << std::endl;
    }

    size_t table::end_session(const std::string& end_time) {
        size_t session_time_m = time_to_minutes(end_time) - start_time_m;
        active = false;
        cl_name.erase();
        start_time_m = 0;
        total_time += session_time_m;

        return session_time_m;
    }

//----------------------
//--- COMP_CLUB_DATA ---
//----------------------
    void comp_club_data::dump () {
        std::cout << "-----------------------------------------------" << std::endl
                  << "Num of tables: " << num_of_tables << std::endl
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

        std::cout << std::endl << "-----------------------------------------------" << std::endl;
    }

    //------------------------------------------------
    // All for monitoring and changing comp_club_data
    //------------------------------------------------

    void comp_club_data::end_session (size_t table, const std::string end_time) {
        size_t session_time_m = room[table].end_session(end_time);
        room[table].total_sum += ((session_time_m / 60) + (session_time_m % 60 > 0)) * cost_per_hour;
    }

    bool comp_club_data::working (const std::string& time) {
        size_t time_m = time_to_minutes(time);
        return time_m >= opening_m && time_m <= closing_m;
    }

    pos comp_club_data::in_da_club (const std::string& cl_name) {
        // Looking in queue
        for (size_t i = 0; i < queue.size(); ++i) {
            if (!queue[i].compare(cl_name)) return {'q', i};
        }

        // Looking in room
        for (size_t i = 1; i <= num_of_tables; ++i) {
            if (!room[i].cl_name.compare(cl_name)) return {'r', i};
        }

        return {'-', 0};
    }

    void comp_club_data::place_client (const std::string& start_time, const std::string& name, 
                                       size_t table, const pos& prev_pos) {
        room[table].active       = true;
        room[table].cl_name      = name;
        room[table].start_time_m = time_to_minutes(start_time);

        if (prev_pos.q_or_r == 'q') {
            auto rm_pos = queue.begin();
            rm_pos += prev_pos.num;
            queue.erase(rm_pos);
        }

        else {
            end_session(prev_pos.num, start_time);
        }
    }

    //-------------------------
    // All for handling events
    //-------------------------

    void comp_club_data::handle_cl_enter (std::ifstream& i_file, const std::string& e_time) {
        std::string cl_name;
        i_file >> cl_name;

        std::cout << e_time << " " << static_cast<short>(i_event::cl_enter) 
                  << " " << cl_name << std::endl;

        if (!working(e_time)) {
            print_error(e_time, errors::NotOpenYet);
        }
        
        else if (in_da_club(cl_name).q_or_r != '-') {
            print_error(e_time, errors::YouShallNotPass);
        }

        else {
            queue.push_back(cl_name);
        }
    }

    void comp_club_data::handle_cl_take_table (std::ifstream& i_file, const std::string& e_time) {
        std::string cl_name;
        i_file >> cl_name;

        size_t table_num;
        i_file >> table_num;

        std::cout << e_time << " " << static_cast<short>(i_event::cl_take_table)
                  << " " << cl_name << " " << table_num << std::endl;

        pos prev_pos = in_da_club(cl_name);

        if (prev_pos.q_or_r == '-') {
            print_error(e_time, errors::ClientUnknown);
        }

        else if (room[table_num].active) {
            print_error(e_time, errors::PlaceIsBusy);
        }

        else {
            place_client(e_time, cl_name, table_num, prev_pos);
        }

        dump();
    }

    void comp_club_data::handle_event (std::ifstream& i_file, i_event event_id, const std::string& e_time) {

        switch (event_id) {
            case i_event::cl_enter:
                handle_cl_enter(i_file, e_time);
                break;
            case i_event::cl_take_table:
                handle_cl_take_table(i_file, e_time);
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