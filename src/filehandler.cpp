#include "filehandler.h"
#include "admin.h"
#include "voter.h"
#include "candidate.h"
#include "vote.h"
#include <fstream>
#include <sstream>
#include <iostream>

void FileHandler::saveUser(const User* user) {
    std::ofstream file("data/users.txt", std::ios::app);
    if (file.is_open()) {
        file << user->getID() << "," 
             << user->getUsername() << "," 
             << "123" << ","  // Placeholder password
             << user->getRole() << "\n";
        file.close();
    }
}

User* FileHandler::loadUserWithPassword(const std::string& username, const std::string& password) {
    std::ifstream file("data/users.txt");
    std::string line;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string id, uname, pass, role;
        std::getline(ss, id, ',');
        std::getline(ss, uname, ',');
        std::getline(ss, pass, ',');
        std::getline(ss, role, ',');

        if (uname == username && pass == password) {
            if (role == "admin")
                return new Admin(id, uname, pass);
            else if (role == "voter")
                return new Voter(id, uname, pass);
            else if (role == "candidate")
                return new Candidate(id, uname, pass);
        }
    }

    return nullptr;
}

bool FileHandler::hasVoted(const std::string& userID, const std::string& electionID) {
    std::ifstream file("data/votes.txt");
    std::string line;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string voterID, candidateID, eID;
        std::getline(ss, voterID, ',');
        std::getline(ss, candidateID, ',');
        std::getline(ss, eID, ',');

        if (voterID == userID && eID == electionID) {
            return true;  // The voter has already voted in this election
        }
    }

    return false;
}

void FileHandler::saveVote( User* voter, Candidate* candidate, const std::string& electionID) {
    Vote vote(voter, candidate, electionID);
    vote.saveVote();
}

void FileHandler::displayVotes() {
    std::ifstream file("data/votes.txt");
    std::string line;

    while (std::getline(file, line)) {
        std::cout << line << std::endl;
    }
}

void FileHandler::countVotes(const std::string& electionID, Candidate** candidates, int numCandidates) {
    std::ifstream file("data/votes.txt");
    std::string line;

    int* voteCount = new int[numCandidates]();  // Array to store vote counts

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string voterID, candidateID, eID;
        std::getline(ss, voterID, ',');
        std::getline(ss, candidateID, ',');
        std::getline(ss, eID, ',');

        if (eID == electionID) {
            for (int i = 0; i < numCandidates; ++i) {
                if (candidates[i]->getID() == candidateID) {
                    ++voteCount[i];  // Increment vote count for the candidate
                }
            }
        }
    }

    // Display vote count
    for (int i = 0; i < numCandidates; ++i) {
        std::cout << "Candidate " << candidates[i]->getUsername() << " has " 
                  << voteCount[i] << " votes." << std::endl;
    }

    delete[] voteCount;  // Clean up dynamically allocated memory
}
