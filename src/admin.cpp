#include "admin.h"
#include "filehandler.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime> // For time functions

Admin::Admin(const std::string &id, const std::string &username, const std::string &password)
    : User(id, username, password, "admin") {}

void Admin::displayProfile()
{
    std::cout << "=== Admin Profile ===\n";
    std::cout << "ID: " << id << "\nUsername: " << username << "\nRole: " << role << std::endl;
}

void Admin::displayMenu() {
    while (true) {
        std::cout << "\n=== Admin Menu ===\n";
        std::cout << "1. View Candidates\n";
        std::cout << "2. Add Candidate\n";
        std::cout << "3. Update Candidate\n";
        std::cout << "4. Delete Candidate\n";
        std::cout << "5. Add Voter\n";
        std::cout << "6. Create Election\n";
        std::cout << "7. View Elections\n";
        std::cout << "8. Logout\n";
        std::cout << "Enter your choice: ";
        int choice;
        std::cin >> choice;

        if (choice == 1) {
            viewCandidates();
        } else if (choice == 2) {
            addCandidate();
        } else if (choice == 3) {
            updateCandidate();
        } else if (choice == 4) {
            deleteCandidate();
        } else if (choice == 5) {
            addVoter();
        } else if (choice == 6) {
            createElection();
        } else if (choice == 7) {
            viewElections();
        } else if (choice == 8) {
            std::cout << "Logging out...\n";
            break;
        } else {
            std::cout << "Invalid choice. Please try again.\n";
        }
    }
}

void Admin::addCandidate()
{
    std::string id, name, password, party;
    std::cout << "Enter Candidate ID: ";
    std::cin >> id;

    // Check if the ID already exists in users.txt
    std::ifstream file("data/users.txt");
    std::string line;
    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string existingID;
        std::getline(ss, existingID, ',');
        if (existingID == id)
        {
            std::cout << "Error: Candidate ID already exists.\n";
            return;
        }
    }
    file.close();

    std::cout << "Enter Candidate Name: ";
    std::cin >> name;
    std::cout << "Enter Password: ";
    std::cin >> password;
    std::cout << "Enter Party: ";
    std::cin >> party;

    // Save candidate to users.txt
    std::ofstream usersFile("data/users.txt", std::ios::app);
    if (usersFile.is_open())
    {
        usersFile << id << "," << name << "," << password << ",candidate\n";
        usersFile.close();
    }
    else
    {
        std::cout << "Error: Unable to open users.txt for writing.\n";
        return;
    }

    // Save candidate to candidates.txt
    Candidate candidate(id, name, password, party);
    FileHandler::saveCandidate(candidate);

    std::cout << "Candidate added successfully.\n";
}

void Admin::addVoter()
{
    std::string id, username, password;

    std::cout << "Enter Voter ID: ";
    std::cin >> id;

    // Check if the ID already exists in users.txt
    std::ifstream file("data/users.txt");
    std::string line;
    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string existingID;
        std::getline(ss, existingID, ',');
        if (existingID == id)
        {
            std::cout << "Error: Voter ID already exists.\n";
            return;
        }
    }
    file.close();

    std::cout << "Enter Username: ";
    std::cin >> username;
    std::cout << "Enter Password: ";
    std::cin >> password;

    // Save voter to users.txt
    std::ofstream usersFile("data/users.txt", std::ios::app);
    if (usersFile.is_open())
    {
        usersFile << id << "," << username << "," << password << ",voter\n";
        usersFile.close();
    }
    else
    {
        std::cout << "Error: Unable to open users.txt for writing.\n";
        return;
    }

    // Save voter to voters.txt
    std::ofstream votersFile("data/voters.txt", std::ios::app);
    if (votersFile.is_open())
    {
        votersFile << id << "," << username << "\n";
        votersFile.close();
    }
    else
    {
        std::cout << "Error: Unable to open voters.txt for writing.\n";
        return;
    }

    std::cout << "Voter added successfully.\n";
}

void Admin::createElection() {
    std::string id, title, startDate, endDate, type;
    int criteria;
    std::cout << "Enter Election ID: ";
    std::cin >> id;
    std::cout << "Enter Election Title: ";
    std::cin.ignore();
    std::getline(std::cin, title);
    std::cout << "Enter Start Date (YYYY-MM-DD): ";
    std::cin >> startDate;
    std::cout << "Enter End Date (YYYY-MM-DD): ";
    std::cin >> endDate;
    std::cout << "Enter Election Type (e.g., General, Local): ";
    std::cin.ignore();
    std::getline(std::cin, type);
    std::cout << "Enter Minimum Age for Eligibility: ";
    std::cin >> criteria;

    // Save election to file
    std::ofstream file("data/elections.txt", std::ios::app);
    if (file.is_open()) {
        file << id << "," << title << "," << startDate << "," << endDate << "," << type << "," << criteria << "\n";
        file.close();
        std::cout << "Election created successfully.\n";
    } else {
        std::cout << "Error: Unable to save election.\n";
    }
}

void Admin::viewElections() {
    std::ifstream file("data/elections.txt");
    std::string line;

    std::cout << "=== Elections ===\n";
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string id, title, startDate, endDate, type;
        int criteria;
        std::getline(ss, id, ',');
        std::getline(ss, title, ',');
        std::getline(ss, startDate, ',');
        std::getline(ss, endDate, ',');
        std::getline(ss, type, ',');
        ss >> criteria;

        std::cout << "ID: " << id << "\nTitle: " << title << "\nStart Date: " << startDate
                  << "\nEnd Date: " << endDate << "\nType: " << type
                  << "\nMinimum Age for Eligibility: " << criteria << "\n\n";
    }
}

void Admin::viewCandidates()
{
    FileHandler::displayCandidates();
}

void Admin::updateCandidate()
{
    std::string id, newName, newParty;
    std::cout << "Enter Candidate ID to update: ";
    std::cin >> id;
    std::cout << "Enter new name: ";
    std::cin >> newName;
    std::cout << "Enter new party: ";
    std::cin >> newParty;

    if (FileHandler::updateCandidate(id, newName, newParty))
        std::cout << "Candidate updated.\n";
    else
        std::cout << "Candidate not found.\n";
}

void Admin::deleteCandidate()
{
    std::string id;
    std::cout << "Enter Candidate ID to delete: ";
    std::cin >> id;

    if (FileHandler::deleteCandidate(id))
        std::cout << "Candidate deleted.\n";
    else
        std::cout << "Candidate not found.\n";
}

void Admin::startElection() {
    std::string electionID;
    int durationMinutes;

    std::cout << "Enter Election ID to start: ";
    std::cin >> electionID;

    // Check if the election exists in elections.txt
    std::ifstream file("data/elections.txt");
    std::string line, id, title, type;
    int criteria;
    time_t startTime, endTime;
    bool found = false;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::getline(ss, id, ',');
        if (id == electionID) {
            found = true;
            break;
        }
    }
    file.close();

    if (!found) {
        std::cout << "Error: Election ID not found.\n";
        return;
    }

    std::cout << "Enter duration of the election in minutes: ";
    std::cin >> durationMinutes;

    // Set start and end times
    startTime = time(nullptr); // Current time
    endTime = startTime + (durationMinutes * 60); // Add duration in seconds

    // Update the election in elections.txt
    std::ifstream inFile("data/elections.txt");
    std::ofstream outFile("data/temp_elections.txt");

    while (std::getline(inFile, line)) {
        std::stringstream ss(line);
        std::getline(ss, id, ',');
        if (id == electionID) {
            outFile << id << "," << title << "," << startTime << "," << endTime << "," << type << "," << criteria << "\n";
        } else {
            outFile << line << "\n";
        }
    }

    inFile.close();
    outFile.close();
    std::remove("data/elections.txt");
    std::rename("data/temp_elections.txt", "data/elections.txt");

    std::cout << "Election started successfully. It will end at: " << ctime(&endTime);
}
