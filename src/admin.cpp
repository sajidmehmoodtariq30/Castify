#include "admin.h"
#include "filehandler.h"
#include <iostream>
#include <fstream>
#include <sstream>

Admin::Admin(const std::string &id, const std::string &username, const std::string &password)
    : User(id, username, password, "admin") {}

void Admin::displayProfile()
{
    std::cout << "=== Admin Profile ===\n";
    std::cout << "ID: " << id << "\nUsername: " << username << "\nRole: " << role << std::endl;
}

void Admin::displayMenu()
{
    while (true)
    {
        std::cout << "\n=== Admin Menu ===\n";
        std::cout << "1. View Candidates\n";
        std::cout << "2. Add Candidate\n";
        std::cout << "3. Update Candidate\n";
        std::cout << "4. Delete Candidate\n";
        std::cout << "5. Add Voter\n";
        std::cout << "6. Logout\n";
        std::cout << "Enter your choice: ";
        int choice;
        std::cin >> choice;

        if (choice == 1)
        {
            viewCandidates();
        }
        else if (choice == 2)
        {
            addCandidate();
        }
        else if (choice == 3)
        {
            updateCandidate();
        }
        else if (choice == 4)
        {
            deleteCandidate();
        }
        else if (choice == 5)
        {
            addVoter();
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
