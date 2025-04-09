#include "voter.h"
#include <iostream>
#include "filehandler.h"

Voter::Voter(std::string id, std::string username, std::string password)
    : User(id, username, password, "voter") {}

void Voter::displayProfile() {
    std::cout << "=== Voter Profile ===\n";
    std::cout << "ID: " << id << "\nUsername: " << username << "\nRole: " << role << std::endl;
}

// filepath: g:\Github\Castify\src\voter.cpp
void Voter::displayMenu() {
    while (true) {
        std::cout << "\n=== Voter Menu ===\n";
        std::cout << "1. View Candidates\n";
        std::cout << "2. Vote for a Candidate\n";
        std::cout << "3. Logout\n";
        std::cout << "Enter your choice: ";
        int choice;
        std::cin >> choice;

        if (choice == 1) {
            FileHandler::displayCandidates();
        } else if (choice == 2) {
            std::string electionID, candidateID;
            std::cout << "Enter Election ID: ";
            std::cin >> electionID;
            std::cout << "Enter Candidate ID: ";
            std::cin >> candidateID;

            if (FileHandler::hasVoted(getID(), electionID)) {
                std::cout << "You have already voted in this election.\n";
            } else {
                Candidate candidate(candidateID, "", "", ""); // Placeholder
                FileHandler::saveVote(this, &candidate, electionID);
                std::cout << "Your vote has been recorded.\n";
            }
        } else if (choice == 3) {
            std::cout << "Logging out...\n";
            break;
        } else {
            std::cout << "Invalid choice. Please try again.\n";
        }
    }
}

