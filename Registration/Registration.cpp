//
// Created by ero on 5/14/23.
//


#include "Registration.h"

#include <utility>


bool Registration::registerUser(std::string login, std::string name, std::string password, std::string phoneNumber,
                                std::string mail) {
    if (checkIfLoginExists(login)) {
        std::cout << "This login is already taken. Please choose a different one." << std::endl;
        return false;
    }

    size_t userId = _dbHelper.getUserId();
    std::unique_ptr<User> userItem = std::make_unique<User>(userId, login, name, password, phoneNumber, mail);

    _dbHelper.saveUser(std::move(userItem));

    std::cout << "User registered successfully." << std::endl;
    return true;
}

bool Registration::checkIfLoginExists(std::string login) {
    bool wasFound {true};
    _dbHelper.getUser(std::move(login), &wasFound);
    return wasFound;
}