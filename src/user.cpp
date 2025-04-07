#include "user.h"
#include <iostream>

User::User(std::string id, std::string username, std::string password, std::string role)
    : id(id), username(username), password(password), role(role) {}

std::string User::getID() const {
    return id;
}

std::string User::getUsername() const {
    return username;
}

std::string User::getRole() const {
    return role;
}

std::string User::getPassword() const {
    return password;
}