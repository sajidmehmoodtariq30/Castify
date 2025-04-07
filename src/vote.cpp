#include "vote.h"
#include <fstream>
#include <iostream>

Vote::Vote(User* voter, Candidate* candidate, const std::string& electionID)
    : voter(voter), candidate(candidate), electionID(electionID) {}

void Vote::saveVote() const {
    std::ofstream file("data/votes.txt", std::ios::app);
    if (file.is_open()) {
        file << voter->getID() << "," 
             << candidate->getID() << ","
             << electionID << "\n";
        file.close();
    }
}

void Vote::displayVote() const {
    std::cout << "Voter ID: " << voter->getID() 
              << " voted for Candidate ID: " << candidate->getID() 
              << " in Election ID: " << electionID << std::endl;
}
