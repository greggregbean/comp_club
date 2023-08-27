#include <gtest/gtest.h>
#include "../include/comp_club.hpp"
#include "../include/input_check.hpp"

TEST(inpuit_check, time_correct) {
    // Arange
    std::string corr_time_1   {"09:00"};
    std::string corr_time_2   {"00:00"};
    std::string incorr_time_3 {"12'32"};
    std::string incorr_time_4 {"24:00"};
    std::string incorr_time_5 {"5:00"};
    std::string incorr_time_6 {"-1:25"};
    std::string incorr_time_7 {"22:83"};

    // Act
    bool res_1 = ic::time_correct(corr_time_1);
    bool res_2 = ic::time_correct(corr_time_2);
    bool res_3 = ic::time_correct(incorr_time_3);
    bool res_4 = ic::time_correct(incorr_time_4);
    bool res_5 = ic::time_correct(incorr_time_5);
    bool res_6 = ic::time_correct(incorr_time_6);
    bool res_7 = ic::time_correct(incorr_time_7);
    
    // Assert
    ASSERT_EQ(res_1,  true);
    ASSERT_EQ(res_2,  true);
    ASSERT_EQ(res_3,  false);
    ASSERT_EQ(res_4,  false);
    ASSERT_EQ(res_5,  false);
    ASSERT_EQ(res_6,  false);
    ASSERT_EQ(res_7,  false);
}
