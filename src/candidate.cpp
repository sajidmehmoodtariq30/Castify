#include "candidate.h"
#include <iostream>

Candidate::Candidate(const std::string& id, const std::string& username, const std::string& password, const std::string& party)
    : User(id, username, password, "candidate"), party(party), voteCount(0) {}

void Candidate::incrementVotes() {
    voteCount++;
}

int Candidate::getVoteCount() const {
    return voteCount;
}

std::string Candidate::getCandidateInfo() const {
    return "ID: " + id + ", Username: " + username + ", Party: " + party + ", Votes: " + std::to_string(voteCount);
}

std::string Candidate::getParty() const {
    return party;
}

void Candidate::setParty(const std::string& newParty) {
    party = newParty;
}

void Candidate::displayProfile() {
    std::cout << "Candidate ID: " << getID() << "\n"
              << "Name: " << getUsername() << "\n"
              << "Party: " << party << "\n";
}

void Candidate::displayMenu() {
    while (true) {
        std::cout << "\n=== Candidate Menu ===\n";
        std::cout << "1. View Profile\n";
        std::cout << "2. Logout\n";
        std::cout << "Enter your choice: ";
        int choice;
        std::cin >> choice;

        if (choice == 1) {
            displayProfile();
        } else if (choice == 2) {
            std::cout << "Logging out...\n";
            break;
        } else {
            std::cout << "Invalid choice. Please try again.\n";
        }
    }
}