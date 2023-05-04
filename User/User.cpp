//
// Created by ero on 4/16/23.
//
#include "User.h"

User::User(size_t id, std::string nameUser, std::string secondName, std::string phoneNumber, std::string mail)
        :_id(id), _nameUser(nameUser), _secondName(secondName), _phoneNumber(phoneNumber), _mail(mail){};

boost::property_tree::ptree User::getJson() const {
    boost::property_tree::ptree user;

    user.put("id", _id);
    user.put("nameUser", _nameUser);
    user.put("secondName", _secondName);
    user.put("phoneNumber", _phoneNumber);
    user.put("mail", _mail);

    return user;
}