#include <iostream>
#include "admin.h"
#include "voter.h"
#include "candidate.h"
#include "filehandler.h"

int main() {
    std::cout << "=== Welcome to Castify ===\n";
    std::cout << "1. Login\n2. Register\nChoose option: ";
    int choice;
    std::cin >> choice;

    std::string username, password, role, id;
    User* user = nullptr;

    if (choice == 1) {
        std::cout << "Enter username: ";
        std::cin >> username;
        std::cout << "Enter password: ";
        std::cin >> password;

        user = FileHandler::loadUserWithPassword(username, password);
        if (user) {
            std::cout << "Login successful!\n";
            user->displayProfile();
        } else {
            std::cout << "Invalid username or password.\n";
        }

    } else if (choice == 2) {
        std::cout << "Enter new username: ";
        std::cin >> username;
        std::cout << "Enter password: ";
        std::cin >> password;
        std::cout << "Enter role (admin/voter/candidate): ";
        std::cin >> role;

        id = "U" + std::to_string(rand() % 1000); // Simple ID gen

        if (role == "admin") user = new Admin(id, username, password);
        else if (role == "voter") user = new Voter(id, username, password);
        else if (role == "candidate") user = new Candidate(id, username, password);

        FileHandler::saveUser(user);
        std::cout << "Registration successful!\n";
        user->displayProfile();
    }

    delete user;
    return 0;
}
