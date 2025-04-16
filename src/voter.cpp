#include "voter.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include "utils.h"
    std::string id, title, type, criteria;
    time_t start, end;
};


    std::string id, name, party;
    int votes;
};


    std::stringstream ss(line);
    std::string startStr, endStr;
    if (!std::getline(ss, info.id, ',')) return false;
    if (!std::getline(ss, info.title, ',')) return false;
    if (!std::getline(ss, startStr, ',')) return false;
    if (!std::getline(ss, endStr, ',')) return false;
    if (!std::getline(ss, info.type, ',')) return false;
    if (!std::getline(ss, info.criteria, ',')) info.criteria = "";
    info.start = std::stol(startStr);
    info.end = std::stol(endStr);
    return true;
}


    return now >= info.start && now <= info.end;
}


    std::string status = isElectionActive(info, now) ? "[ACTIVE]" : "[INACTIVE]";
    std::cout << info.id << ": " << info.title << " (" << info.type << ") " << status << std::endl;
}


    std::stringstream ss(line);
    std::string votesStr;
    if (!std::getline(ss, info.id, ',')) return false;
    if (!std::getline(ss, info.name, ',')) return false;
    if (!std::getline(ss, info.party, ',')) return false;
    if (!std::getline(ss, votesStr, ',')) votesStr = "0";
    info.votes = std::stoi(votesStr);
    return true;
}


    std::cout << info.id << ": " << info.name << " (" << info.party << ") Votes: " << info.votes << std::endl;
}

bool Voter::hasVoted(const std::string& electionID) const {
    std::ifstream file("data/votes.txt");
    if (!file.is_open()) return false;
    char line[256];
    while (file.getline(line, 256)) {
        char* voterID = strtok(line, ",");
        char* candidateID = strtok(NULL, ",");
        char* eID = strtok(NULL, ",");
        if (voterID && eID && this->getID() == voterID && electionID == eID) {
            return true;
        }
    }
    return false;
}

void Voter::castVote(Election* election, Candidate* candidate) {
    if (hasVoted(election->getID())) {
        std::cout << "You have already voted in this election!" << std::endl;
        return;
    }
    Vote vote(this, candidate, election->getID());
    vote.saveVote();
    std::cout << "Vote cast successfully!" << std::endl;
}

void Voter::checkVoteStatus(const std::string& electionID) const {
    if (hasVoted(electionID)) {
        std::cout << "You have already voted in election " << electionID << std::endl;
    } else {
        std::cout << "You have not voted in election " << electionID << std::endl;
    }
}
#include <iostream>
#include "filehandler.h"
#include <fstream>
#include <sstream>

Voter::Voter(std::string id, std::string username, std::string password)
    : User(id, username, password, "voter") {}

void Voter::displayProfile()
{
    std::cout << "=== Voter Profile ===\n";
    std::cout << "ID: " << id << "\nUsername: " << username << "\nRole: " << role << std::endl;
}

// filepath: g:\Github\Castify\src\voter.cpp
void Voter::displayMenu()
{
    while (true)
    {
        std::cout << "\n=== Voter Menu ===\n";
        std::cout << "1. View Elections\n";
        std::cout << "2. View Candidates for Election\n";
        std::cout << "3. Vote for a Candidate\n";
        std::cout << "4. Check Vote Status\n";
        std::cout << "5. View Voting History\n";
        std::cout << "6. Logout\n";
        std::cout << "Enter your choice: ";
        int choice;
        std::cin >> choice;

        if (choice == 1)
        {
            // View all elections, modular
            std::ifstream file("data/elections.txt");
            std::string line;
            time_t now = time(nullptr);
            std::cout << "\n--- Elections ---\n";
            while (std::getline(file, line)) {
                ElectionInfo info;
                if (parseElectionLine(line, info)) {
                    displayElection(info, now);
                }
            }
            file.close();
        }
        else if (choice == 2)
        {
            // View candidates for a selected election (modular)
            std::string electionID;
            std::cout << "Enter Election ID: ";
            std::cin >> electionID;
            std::ifstream file("data/candidates_" + electionID + ".txt");
            std::string line;
            std::cout << "\n--- Candidates for Election " << electionID << " ---\n";
            while (std::getline(file, line)) {
                CandidateInfo info;
                if (parseCandidateLine(line, info)) {
                    displayCandidate(info);
                }
            }
            file.close();
        }
        else if (choice == 3)
        {
            // Vote for a candidate
            std::string electionID, candidateID;
            std::cout << "Enter Election ID: ";
            std::cin >> electionID;
            // Check if election is active
            std::ifstream efile("data/elections.txt");
            std::string eline;
            bool found = false, active = false;
            time_t now = time(nullptr);
            while (std::getline(efile, eline)) {
                std::stringstream ss(eline);
                std::string id, title, start, end, type, criteria;
                std::getline(ss, id, ',');
                std::getline(ss, title, ',');
                std::getline(ss, start, ',');
                std::getline(ss, end, ',');
                std::getline(ss, type, ',');
                std::getline(ss, criteria, ',');
                if (id == electionID) {
                    found = true;
                    time_t st = std::stol(start), et = std::stol(end);
                    if (now >= st && now <= et) active = true;
                    break;
                }
            }
            efile.close();
            if (!found) {
                std::cout << "Election not found!\n";
                continue;
            }
            if (!active) {
                std::cout << "Election is not active!\n";
                continue;
            }
            std::cout << "Enter Candidate ID: ";
            std::cin >> candidateID;
            // Check if already voted
            if (hasVoted(electionID)) {
                std::cout << "You have already voted in this election!\n";
                continue;
            }
            // Save vote
            Candidate candidate(candidateID, "", "", "");
            Vote vote(this, &candidate, electionID);
            vote.saveVote();
            std::cout << "Vote cast successfully!\n";
        }
        else if (choice == 4)
        {
            std::string electionID;
            std::cout << "Enter Election ID: ";
            std::cin >> electionID;
            checkVoteStatus(electionID);
        }
        else if (choice == 5)
        {
            // View voting history
            std::ifstream file("data/votes.txt");
            std::string line;
            std::cout << "\n--- Voting History ---\n";
            while (std::getline(file, line)) {
                std::stringstream ss(line);
                std::string voterID, candidateID, electionID;
                std::getline(ss, voterID, ',');
                std::getline(ss, candidateID, ',');
                std::getline(ss, electionID, ',');
                if (voterID == this->getID()) {
                    std::cout << "Election: " << electionID << ", Candidate: " << candidateID << std::endl;
                }
            }
            file.close();
        }
        else if (choice == 6)
        {
            std::cout << "Logging out...\n";
            break;
        }
        else
        {
            std::cout << "Invalid choice. Please try again.\n";
        }
    }
}
{
    while (true)
    {
        std::cout << "\n=== Voter Menu ===\n";
        std::cout << "1. View Candidates\n";
        std::cout << "2. Vote for a Candidate\n";
        std::cout << "3. Logout\n";
        std::cout << "Enter your choice: ";
        int choice;
        std::cin >> choice;

        if (choice == 1)
        {
            FileHandler::displayCandidates();
        }
        else if (choice == 2)
        {
            std::string electionID, candidateID;
            std::cout << "Enter Election ID: ";
            std::cin >> electionID;

            // Check if the election is active
            std::ifstream file("data/elections.txt");
            std::string line;
            bool isActive = false;

            while (std::getline(file, line))
            {
                std::stringstream ss(line);
                std::string id;
                time_t startTime, endTime;
                std::getline(ss, id, ',');
                if (id == electionID)
                {
                    ss >> startTime >> endTime;
                    time_t currentTime = time(nullptr);
                    if (currentTime >= startTime && currentTime <= endTime)
                    {
                        isActive = true;
                    }
                    break;
                }
            }
            file.close();

            if (!isActive)
            {
                std::cout << "Error: Election is not active or has ended.\n";
                continue;
            }

            std::cout << "Enter Candidate ID: ";
            std::cin >> candidateID;

            if (FileHandler::hasVoted(getID(), electionID))
            {
                std::cout << "You have already voted in this election.\n";
            }
            else
            {
                Candidate candidate(candidateID, "", "", ""); // Placeholder
                FileHandler::saveVote(this, &candidate, electionID);
                std::cout << "Your vote has been recorded.\n";
            }
        }
        else if (choice == 3)
        {
            std::cout << "Logging out...\n";
            break;
        }
        else
        {
            std::cout << "Invalid choice. Please try again.\n";
        }
    }
}
