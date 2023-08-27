#include <gtest/gtest.h>
#include "../include/comp_club.hpp"
#include "../include/input_check.hpp"

//-------------
// Imput check
//-------------
TEST (input_check, time_correct) {
    // Arange
    std::string time_1 {"09:00"};
    std::string time_2 {"00:00"};
    std::string time_3 {"12'32"};
    std::string time_4 {"24:00"};
    std::string time_5 {"5:00"};
    std::string time_6 {"-1:25"};
    std::string time_7 {"22:83"};
    std::string time_8 {""};
    std::string time_9 {" "};

    // Act
    bool res_1 = ic::time_correct(time_1);
    bool res_2 = ic::time_correct(time_2);
    bool res_3 = ic::time_correct(time_3);
    bool res_4 = ic::time_correct(time_4);
    bool res_5 = ic::time_correct(time_5);
    bool res_6 = ic::time_correct(time_6);
    bool res_7 = ic::time_correct(time_7);
    bool res_8 = ic::time_correct(time_8);
    bool res_9 = ic::time_correct(time_9);
    
    // Assert
    ASSERT_TRUE (res_1);
    ASSERT_TRUE (res_2);
    ASSERT_FALSE(res_3);
    ASSERT_FALSE(res_4);
    ASSERT_FALSE(res_5);
    ASSERT_FALSE(res_6);
    ASSERT_FALSE(res_7);
    ASSERT_FALSE(res_8);
    ASSERT_FALSE(res_9);
}

TEST (input_check, event_correct) {
    // Arrange
    size_t num_of_tables = 5;
    std::string last_e_time {"05:00"};

    char event_line_1  [] = {"19:00 1 client8"};
    char event_line_2  [] = {""};
    char event_line_3  [] = {" 19:00 1 client8"};
    char event_line_4  [] = {"19:00 5 client8"};
    char event_line_5  [] = {"4:00 1 client8"};
    char event_line_6  [] = {"19:01 2 cliEnt6"};
    char event_line_7  [] = {"19:00 1  client5"};
    char event_line_8  [] = {"19:00 2 client "};
    char event_line_9  [] = {"19:00 3 client2\n"};
    char event_line_10 [] = {"19:00 2 client1 7"};

    // Act
    bool res_1  = ic::event_correct(event_line_1, last_e_time, num_of_tables);
    bool res_2  = ic::event_correct(event_line_2, last_e_time, num_of_tables);
    bool res_3  = ic::event_correct(event_line_3, last_e_time, num_of_tables);
    bool res_4  = ic::event_correct(event_line_4, last_e_time, num_of_tables);
    bool res_5  = ic::event_correct(event_line_5, last_e_time, num_of_tables);
    bool res_6  = ic::event_correct(event_line_6, last_e_time, num_of_tables);
    bool res_7  = ic::event_correct(event_line_7, last_e_time, num_of_tables);
    bool res_8  = ic::event_correct(event_line_8, last_e_time, num_of_tables);
    bool res_9  = ic::event_correct(event_line_9, last_e_time, num_of_tables);
    bool res_10 = ic::event_correct(event_line_9, last_e_time, num_of_tables);

    // Assert
    ASSERT_TRUE (res_1);
    ASSERT_FALSE(res_2);
    ASSERT_FALSE(res_3);
    ASSERT_FALSE(res_4);
    ASSERT_FALSE(res_5);
    ASSERT_FALSE(res_6);
    ASSERT_FALSE(res_7);
    ASSERT_FALSE(res_8);
    ASSERT_FALSE(res_9);
    ASSERT_FALSE(res_10);
}

TEST (input_check, time_to_minutes) {
    // Arange
    std::string time_1 {"19:00"};
    std::string time_2 {"23:26"};
    std::string time_3 {"00:00"};
    std::string time_4 {"12:10"};
    std::string time_5 {"01:01"};

    // Act
    size_t res_1 = time_to_minutes(time_1);
    size_t res_2 = time_to_minutes(time_2);
    size_t res_3 = time_to_minutes(time_3);
    size_t res_4 = time_to_minutes(time_4);
    size_t res_5 = time_to_minutes(time_5);

    // Assert
    ASSERT_EQ(res_1, 1140);
    ASSERT_EQ(res_2, 1406);
    ASSERT_EQ(res_3, 0);
    ASSERT_EQ(res_4, 730);
    ASSERT_EQ(res_5, 61);
}

//----------------
// Comp club data
//----------------
struct comp_club_data_fixture : public testing::Test {
    comp_club::comp_club_data test_day_data {1, "09:00", "19:00", 10};

    void SetUp() override { testing::internal::CaptureStdout(); }
};

TEST_F (comp_club_data_fixture, handle_cl_enter) {
    // Arange
    std::ifstream i_file;
    i_file.open("../../testing/test_files_for_handling/handle_cl_enter.txt", std::ios::in);

    std::string right_output;
    right_output += "03:00 1 test_client\n";
    right_output += "03:00 13 NotOpenYet\n";
    right_output += "10:00 1 test_client\n";
    right_output += "12:00 1 test_client\n";
    right_output += "12:00 13 YouShallNotPass\n";

    // Act
    test_day_data.event_handler(i_file);
    std::string output = testing::internal::GetCapturedStdout();

    // Assert
    ASSERT_STREQ(output.c_str(), right_output.c_str());
}

TEST_F (comp_club_data_fixture, handle_cl_take_table) {
    // Arange
    std::ifstream i_file;
    i_file.open("../../testing/test_files_for_handling/handle_cl_take_table.txt", std::ios::in);

    std::string right_output;
    right_output += {"09:00 2 test_client 1\n"};
    right_output += {"09:00 13 ClientUnknown\n"};
    right_output += {"10:00 1 test_client\n"};
    right_output += {"11:00 2 test_client 1\n"};
    right_output += {"12:00 2 test_client 1\n"};
    right_output += {"12:00 13 PlaceIsBusy\n"};
    right_output += {"13:00 1 new_client\n"};
    right_output += {"14:00 2 new_client 1\n"};
    right_output += {"14:00 13 PlaceIsBusy\n"};

    // Act
    test_day_data.event_handler(i_file);
    std::string output = testing::internal::GetCapturedStdout();

    // Assert
    ASSERT_STREQ(output.c_str(), right_output.c_str());
}

TEST_F (comp_club_data_fixture, handle_cl_is_waiting) {
    // Arange
    std::ifstream i_file;
    i_file.open("../../testing/test_files_for_handling/handle_cl_is_waiting.txt", std::ios::in);

    std::string right_output;
    right_output += {"09:00 1 test_client\n"};
    right_output += {"10:00 3 test_client\n"};
    right_output += {"10:00 13 ICanWaitNoLonger!\n"};
    right_output += {"10:30 2 test_client 1\n"};
    right_output += {"11:00 1 new_client_1\n"};
    right_output += {"11:30 3 new_client_1\n"};
    right_output += {"12:00 1 new_client_2\n"};
    right_output += {"12:30 3 new_client_2\n"};
    right_output += {"13:00 1 new_client_3\n"};
    right_output += {"13:30 3 new_client_3\n"};
    right_output += {"13:30 11 new_client_3\n"};
    
    // Act
    test_day_data.event_handler(i_file);
    std::string output = testing::internal::GetCapturedStdout();

    // Assert
    ASSERT_STREQ(output.c_str(), right_output.c_str());
}

TEST_F (comp_club_data_fixture, handle_cl_quit) {
    // Arange
    std::ifstream i_file;
    i_file.open("../../testing/test_files_for_handling/handle_cl_quit.txt", std::ios::in);

    std::string right_output;
    right_output += {"09:00 4 test_client\n"};
    right_output += {"09:00 13 ClientUnknown\n"};
    right_output += {"10:00 1 test_client\n"};
    right_output += {"11:00 2 test_client 1\n"};
    right_output += {"12:00 1 new_client_1\n"};
    right_output += {"12:30 3 new_client_1\n"};
    right_output += {"13:00 1 new_client_2\n"};
    right_output += {"13:30 3 new_client_2\n"};
    right_output += {"14:00 4 test_client\n"};
    right_output += {"14:00 12 new_client_1 1\n"};
    right_output += {"15:00 4 new_client_1\n"};
    right_output += {"15:00 12 new_client_2 1\n"};

    // Act
    test_day_data.event_handler(i_file);
    std::string output = testing::internal::GetCapturedStdout();

    // Assert
    ASSERT_STREQ(output.c_str(), right_output.c_str());
}





