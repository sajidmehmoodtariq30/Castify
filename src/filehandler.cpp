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
             << user->getPassword() << ","  // Placeholder password
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
        std::string voterID, candidateID;
        std::getline(ss, voterID, ',');
        std::getline(ss, candidateID, ',');

        if (voterID == userID) {
            return true;  // The voter has already voted
        }
    }

    return false;
}

void FileHandler::saveVote( User* voter, Candidate* candidate) {
    Vote vote(voter, candidate);
    vote.saveVote();
}

void FileHandler::displayVotes() {
    std::ifstream file("data/votes.txt");
    std::string line;

    while (std::getline(file, line)) {
        std::cout << line << std::endl;
    }
}
