#include "admin.h"
#include <iostream>

Admin::Admin(std::string id, std::string username, std::string password)
    : User(id, username, password, "admin") {}

void Admin::displayProfile() {
    std::cout << "=== Admin Profile ===\n";
    std::cout << "ID: " << id << "\nUsername: " << username << "\nRole: " << role << std::endl;
}
