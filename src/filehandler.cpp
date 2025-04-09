#include "filehandler.h"
#include "admin.h"
#include "voter.h"
#include "candidate.h"
#include "vote.h"
#include <fstream>
#include <sstream>
#include <iostream>

void FileHandler::saveUser(const User *user)
{
    std::ofstream file("data/users.txt", std::ios::app);
    if (file.is_open())
    {
        file << user->getID() << ","
             << user->getUsername() << ","
             << user->getPassword() << ","
             << user->getRole() << "\n";
        file.close();
    }
}

User *FileHandler::loadUserWithPassword(const std::string &username, const std::string &password)
{
    std::ifstream file("data/users.txt");
    std::string line;

    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string id, uname, pass, role, party;
        std::getline(ss, id, ',');
        std::getline(ss, uname, ',');
        std::getline(ss, pass, ',');
        std::getline(ss, role, ',');

        if (role == "candidate")
        {
            std::getline(ss, party, ',');
        }

        if (uname == username && pass == password)
        {
            if (role == "admin")
                return new Admin(id, uname, pass);
            else if (role == "voter")
                return new Voter(id, uname, pass);
            else if (role == "candidate")
                return new Candidate(id, uname, pass, party);
        }
    }

    return nullptr;
}

bool FileHandler::hasVoted(const std::string &userID, const std::string &electionID)
{
    std::ifstream file("data/votes.txt");
    std::string line;

    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string voterID, candidateID, eID;
        std::getline(ss, voterID, ',');
        std::getline(ss, candidateID, ',');
        std::getline(ss, eID, ',');

        if (voterID == userID && eID == electionID)
        {
            return true; // The voter has already voted in this election
        }
    }

    return false;
}

void FileHandler::saveVote(User *voter, Candidate *candidate, const std::string &electionID)
{
    Vote vote(voter, candidate, electionID);
    vote.saveVote();
}

void FileHandler::displayVotes()
{
    std::ifstream file("data/votes.txt");
    std::string line;

    while (std::getline(file, line))
    {
        std::cout << line << std::endl;
    }
}

void FileHandler::countVotes(const std::string &electionID)
{
    std::ifstream file("data/votes.txt");
    std::string line;

    // Reset vote counts in candidates.txt
    std::ifstream candidatesFile("data/candidates.txt");
    std::ofstream tempFile("data/temp_candidates.txt");
    std::string candidateLine;

    while (std::getline(candidatesFile, candidateLine))
    {
        std::stringstream ss(candidateLine);
        std::string id, username, party, totalVotes;
        std::getline(ss, id, ',');
        std::getline(ss, username, ',');
        std::getline(ss, party, ',');
        tempFile << id << "," << username << "," << party << ",0\n"; // Reset votes to 0
    }
    candidatesFile.close();
    tempFile.close();
    std::remove("data/candidates.txt");
    std::rename("data/temp_candidates.txt", "data/candidates.txt");

    // Count votes
    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string voterID, candidateID, eID;
        std::getline(ss, voterID, ',');
        std::getline(ss, candidateID, ',');
        std::getline(ss, eID, ',');

        if (eID == electionID)
        {
            // Update vote count in candidates.txt
            std::ifstream candidatesFile("data/candidates.txt");
            std::ofstream tempFile("data/temp_candidates.txt");
            while (std::getline(candidatesFile, candidateLine))
            {
                std::stringstream ss(candidateLine);
                std::string id, username, party, totalVotes;
                std::getline(ss, id, ',');
                std::getline(ss, username, ',');
                std::getline(ss, party, ',');
                std::getline(ss, totalVotes, ',');

                if (id == candidateID)
                {
                    int updatedVotes = std::stoi(totalVotes) + 1;
                    tempFile << id << "," << username << "," << party << "," << updatedVotes << "\n";
                }
                else
                {
                    tempFile << candidateLine << "\n";
                }
            }
            candidatesFile.close();
            tempFile.close();
            std::remove("data/candidates.txt");
            std::rename("data/temp_candidates.txt", "data/candidates.txt");
        }
    }
}

// Create
void FileHandler::saveCandidate(const Candidate &candidate)
{
    std::ofstream file("data/candidates.txt", std::ios::app);
    if (file.is_open())
    {
        file << candidate.getID() << ","
             << candidate.getUsername() << ","
             << candidate.getParty() << ","
             << "0" << "\n"; // Initialize TotalVotes to 0
        file.close();
    }
}

// Read
void FileHandler::displayCandidates() {
    std::ifstream file("data/candidates.txt");
    std::string line;

    std::cout << "Candidates List:\n";
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string id, name, party, totalVotes;
        std::getline(ss, id, ',');
        std::getline(ss, name, ',');
        std::getline(ss, party, ',');
        std::getline(ss, totalVotes, ',');
        std::cout << "ID: " << id << ", Name: " << name << ", Party: " << party 
                  << ", Total Votes: " << totalVotes << "\n";
    }
}

// Update
bool FileHandler::updateCandidate(const std::string &id, const std::string &newName, const std::string &newParty)
{
    std::ifstream file("data/candidates.txt");
    std::ofstream temp("data/temp.txt");
    std::string line;
    bool updated = false;

    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string cid, name, party;
        std::getline(ss, cid, ',');
        std::getline(ss, name, ',');
        std::getline(ss, party, ',');

        if (cid == id)
        {
            temp << cid << "," << newName << "," << newParty << "\n";
            updated = true;
        }
        else
        {
            temp << line << "\n";
        }
    }

    file.close();
    temp.close();
    std::remove("data/candidates.txt");
    std::rename("data/temp.txt", "data/candidates.txt");

    return updated;
}

// Delete
bool FileHandler::deleteCandidate(const std::string &id)
{
    std::ifstream file("data/candidates.txt");
    std::ofstream temp("data/temp.txt");
    std::string line;
    bool deleted = false;

    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string cid;
        std::getline(ss, cid, ',');

        if (cid == id)
        {
            deleted = true;
            continue;
        }
        temp << line << "\n";
    }

    file.close();
    temp.close();
    std::remove("data/candidates.txt");
    std::rename("data/temp.txt", "data/candidates.txt");

    return deleted;
}
