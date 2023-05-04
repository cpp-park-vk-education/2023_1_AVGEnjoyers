//
// Created by ero on 4/16/23.
//

#ifndef BACKEND_CPP_USER_H
#define BACKEND_CPP_USER_H

#include <string>
#include <vector>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

class User {
public:
    User(size_t id, std::string nameUser, std::string secondName, std::string phoneNumber, std::string mail);
    boost::property_tree::ptree getJson() const;

private:
    size_t _id;
    std::string _nameUser, _secondName, _phoneNumber, _mail;

    std::vector<std::string> flatsHands();
    std::vector<std::string> flatsRent();

};

#endif //BACKEND_CPP_USER_H
