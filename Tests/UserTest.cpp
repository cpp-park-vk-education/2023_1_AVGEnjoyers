#include "gtest/gtest.h"
#include "../User/User.h"
#include <boost/property_tree/json_parser.hpp>

// Тест метода getJson класса User
TEST(UserTest, GetJsonTest) {
    User user(1, "John", "Doe", "123-456-7890", "john.doe@example.com");

    boost::property_tree::ptree json = user.getJson();

    EXPECT_EQ(json.get<size_t>("id"), 1);
    EXPECT_EQ(json.get<std::string>("nameUser"), "John");
    EXPECT_EQ(json.get<std::string>("secondName"), "Doe");
    EXPECT_EQ(json.get<std::string>("phoneNumber"), "123-456-7890");
    EXPECT_EQ(json.get<std::string>("mail"), "john.doe@example.com");
}