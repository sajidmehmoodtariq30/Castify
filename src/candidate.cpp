#include "candidate.h"
#include <iostream>

Candidate::Candidate(std::string id, std::string username, std::string password)
    : User(id, username, password, "candidate") {}

void Candidate::displayProfile() {
    std::cout << "=== Candidate Profile ===\n";
    std::cout << "ID: " << id << "\nUsername: " << username << "\nRole: " << role << std::endl;
}
