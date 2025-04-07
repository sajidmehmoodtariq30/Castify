#include <iostream>
#include "admin.h"
#include "voter.h"
#include "candidate.h"
#include "filehandler.h"

int main() {
    std::string username;
    std::cout << "Enter username to load: ";
    std::cin >> username;

    User* user = FileHandler::loadUserByUsername(username);

    if (user) {
        std::cout << "User loaded!\n";
        user->displayProfile();
    } else {
        std::cout << "User not found. Registering...\n";
        std::string id = "U" + std::to_string(rand() % 1000); // Simple ID
        std::string role;
        std::cout << "Enter role (admin/voter/candidate): ";
        std::cin >> role;

        if (role == "admin") user = new Admin(id, username, "123");
        else if (role == "voter") user = new Voter(id, username, "123");
        else if (role == "candidate") user = new Candidate(id, username, "123");

        FileHandler::saveUser(user);
        std::cout << "User registered!\n";
        user->displayProfile();
    }

    delete user;
    return 0;
}
