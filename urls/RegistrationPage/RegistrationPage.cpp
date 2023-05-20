//
// Created by nikita on 18.05.23.
//

#include "RegistrationPage.h"
#include "../../Registration/Registration.h"

#define EMAIL_IS_MISSING "'email' is missing. Please include the required parameter in your POST request"
#define NAME_IS_MISSING "'name' is missing. Please include the required parameter in your POST request"
#define PASSWORD_IS_MISSING "'password' is missing. Please include the required parameter in your POST request"
#define PHONE_NUMBER_IS_MISSING "'phoneNumber' is missing. Please include the required parameter in your POST request"
#define LOGIN_IS_MISSING "'login' is missing. Please include the required parameter in your POST request"


//getErrorResponse(LOGIN_IS_MISSING, http::status::bad_request);
http::response<http::string_body> RegistrationPage::getResponse() {
    std::string login, name, password, phoneNumber, mail;
    try {
        login = _params.at("login");
        name = _params.at("name");
        password = _params.at("password");
        phoneNumber = _params.at("phoneNumber");
        mail = _params.at("email");
    } catch (const std::out_of_range& e) {
        std::string errorText = "Missing parameters: ";
        // Iterate through _params to find the missing parameters
        std::vector<std::string> requiredParams = {"login", "name", "password", "phoneNumber", "email"};

        for (const auto& param : requiredParams) {
            if (_params.find(param) == _params.end()) {
                errorText += param + ", ";
            }
        }
        // Remove the trailing comma and space
        if (!errorText.empty()) {
            errorText = errorText.substr(0, errorText.length() - 2);
        }
        return getErrorResponse(errorText, http::status::bad_request);
    }

    DBHelper dbHelper;
    Registration registration(dbHelper);

    boost::beast::http::response<http::string_body> res;

    if (registration.registerUser(login, name, password, phoneNumber, mail)) {
        // Registration successful
        res.result(http::status::ok);
        res.set(http::field::content_type, "text/plain");
        res.body() = "Registration successful";
    } else {
        // Registration failed
        res.result(http::status::bad_request);
        res.set(http::field::content_type, "text/plain");
        res.body() = "Registration failed";
    }

    return res;
}

RegistrationPage::RegistrationPage(const std::shared_ptr<http::request<http::string_body>> &request) {
    _params = parsePostRequest(request);
}


