#include "voter.h"
#include <iostream>

Voter::Voter(std::string id, std::string username, std::string password)
    : User(id, username, password, "voter") {}

void Voter::displayProfile() {
    std::cout << "=== Voter Profile ===\n";
    std::cout << "ID: " << id << "\nUsername: " << username << "\nRole: " << role << std::endl;
}
