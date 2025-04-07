#include "vote.h"
#include <fstream>
#include <iostream>

Vote::Vote(User* voter, Candidate* candidate)
    : voter(voter), candidate(candidate) {}

void Vote::saveVote() const {
    std::ofstream file("data/votes.txt", std::ios::app);
    if (file.is_open()) {
        file << voter->getID() << "," 
             << candidate->getID() << "\n";
        file.close();
    }
}

void Vote::displayVote() const {
    std::cout << "Voter ID: " << voter->getID() 
              << " voted for Candidate ID: " << candidate->getID() << std::endl;
}
