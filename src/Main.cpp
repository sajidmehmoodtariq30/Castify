#include <iostream>
#include "filehandler.h"
#include "admin.h"
#include "voter.h"
#include "candidate.h"

void displayAdminMenu(Admin* admin);
void displayVoterMenu(Voter* voter);
void displayCandidateMenu(Candidate* candidate);

int main() {
    while (true) {
        std::cout << "=== Welcome to Castify ===\n";
        std::cout << "1. Login\n";
        std::cout << "2. Exit\n";
        std::cout << "Enter your choice: ";
        int choice;
        std::cin >> choice;

        if (choice == 2) {
            std::cout << "Exiting the system. Goodbye!\n";
            break;
        }

        if (choice == 1) {
            std::string username, password;
            std::cout << "Enter username: ";
            std::cin >> username;
            std::cout << "Enter password: ";
            std::cin >> password;

            // Authenticate user
            User* user = FileHandler::loadUserWithPassword(username, password);
            if (!user) {
                std::cout << "Invalid username or password. Please try again.\n";
                continue;
            }

            // Use polymorphism to display the appropriate menu
            user->displayMenu();

            delete user; // Clean up dynamically allocated memory
        } else {
            std::cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
