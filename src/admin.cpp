#include "admin.h"
#include "utils.h"
#include <iostream>
#include "localelection.h"
#include "regionalelection.h"
#include "nationalelection.h"

void Admin::viewResults(Election* election) {
    if (election) {
        election->displayResults();
    } else {
        std::cout << "Invalid election selected!" << std::endl;
    }
}

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
        std::cout << "8. Edit Election\n";
        std::cout << "9. Logout\n";
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
            editElection();
        } else if (choice == 9) {
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

void saveElectionToFile(Election* election) {
    std::ofstream file("data/elections.txt", std::ios::app);
    if (file.is_open()) {
        file << election->getID() << "," << election->getTitle() << "," << election->getStartTime() << "," << election->getEndTime() << "," << election->getElectionType() << "," << election->getEligibilityCriteria() << "\n";
        file.close();
    }
    // Save candidates for this election
    std::ofstream cfile("data/candidates_" + election->getID() + ".txt");
    for (int i = 0; i < election->getNumCandidates(); ++i) {
        Candidate* c = election->getCandidates()[i];
        cfile << c->getID() << "," << c->getUsername() << "," << c->getParty() << "," << c->getVoteCount() << "\n";
    }
    cfile.close();
}

void loadElectionsFromFile() {
    // Stub: implement if needed for memory-based management
}

void Admin::editElection() {
    std::string electionID;
    std::cout << "Enter Election ID to edit: ";
    std::cin >> electionID;
    // Edit duration
    std::ifstream infile("data/elections.txt");
    std::ofstream tempfile("data/elections_temp.txt");
    std::string line;
    bool found = false;
    while (std::getline(infile, line)) {
        std::stringstream ss(line);
        std::string id, title, start, end, type, criteria;
        std::getline(ss, id, ',');
        if (id == electionID) {
            found = true;
            std::cout << "Editing election: " << line << std::endl;
            std::cout << "Enter new start time (epoch): ";
            std::cin >> start;
            std::cout << "Enter new end time (epoch): ";
            std::cin >> end;
            tempfile << id << "," << title << "," << start << "," << end << "," << type << "," << criteria << "\n";
        } else {
            tempfile << line << "\n";
        }
    }
    infile.close();
    tempfile.close();
    remove("data/elections.txt");
    rename("data/elections_temp.txt", "data/elections.txt");
    // Edit candidates
    std::cout << "Edit candidates for this election? (y/n): ";
    char ch;
    std::cin >> ch;
    if (ch == 'y' || ch == 'Y') {
        std::ofstream cfile("data/candidates_" + electionID + ".txt", std::ios::app);
        std::string cid, uname, party;
        std::cout << "Add candidate (id username party, or 'end' to finish):\n";
        while (true) {
            std::cin >> cid;
            if (cid == "end") break;
            std::cin >> uname >> party;
            cfile << cid << "," << uname << "," << party << ",0\n";
        }
        cfile.close();
    }
    std::cout << "Election edited.\n";
}

void Admin::createElection()
{
    std::cout << "\n=== Create Election ===\n";
    std::string id, title, type;
    time_t startTime, endTime;
    int criteria;
    std::cout << "Enter Election ID: ";
    std::cin >> id;
    std::cout << "Enter Title: ";
    std::cin.ignore();
    std::getline(std::cin, title);
    std::cout << "Enter Type (Local/National): ";
    std::cin >> type;
    std::cout << "Enter Start Time (as epoch): ";
    std::cin >> startTime;
    std::cout << "Enter End Time (as epoch): ";
    std::cin >> endTime;
    std::cout << "Enter Eligibility Criteria (min age): ";
    std::cin >> criteria;
    Election* election = nullptr;
    if (type == "Local") {
        election = new LocalElection(id, title, startTime, endTime, criteria);
    } else if (type == "Regional") {
        election = new RegionalElection(id, title, startTime, endTime, criteria);
    } else {
        election = new NationalElection(id, title, startTime, endTime, criteria);
    }
    char addMore = 'y';
    while (addMore == 'y' || addMore == 'Y') {
        addCandidateToElection(election);
        std::cout << "Add another candidate? (y/n): ";
        std::cin >> addMore;
    }
    // TODO: Save election to file or memory as per your design
    std::cout << "Election created successfully!\n";
}

void Admin::addCandidateToElection(Election* election)
{
    std::string cid, uname, pwd, party;
    std::cout << "Enter Candidate ID: ";
    std::cin >> cid;
    std::cout << "Enter Candidate Username: ";
    std::cin >> uname;
    std::cout << "Enter Candidate Password: ";
    std::cin >> pwd;
    std::cout << "Enter Candidate Party: ";
    std::cin >> party;
    Candidate* candidate = new Candidate(cid, uname, pwd, party);
    election->addCandidate(candidate);
    std::cout << "Candidate added to election!\n";
}

void Admin::updateCandidateInElection(Election* election)
{
    if (!election) {
        std::cout << "Invalid election!\n";
        return;
    }
    std::string cid;
    std::cout << "Enter Candidate ID to update: ";
    std::cin >> cid;
    bool found = false;
    // Access the dynamic array directly (no STL)
    for (int i = 0; i < election->getNumCandidates(); ++i) {
        Candidate* candidate = election->getCandidates()[i];
        if (candidate->getID() == cid) {
            std::string uname, pwd, party;
            std::cout << "Enter new username: ";
            std::cin >> uname;
            std::cout << "Enter new password: ";
            std::cin >> pwd;
            std::cout << "Enter new party: ";
            std::cin >> party;
            candidate->setParty(party);
            // Assume setters for username/password, or update directly if public
            /* TODO: Add setUsername() to Candidate/User if you want to update username */
            /* TODO: Add setPassword() to Candidate/User if you want to update password */
            std::cout << "Candidate updated!\n";
            found = true;
            break;
        }
    }
    if (!found) {
        std::cout << "Candidate not found in this election.\n";
    }
}

void Admin::deleteCandidateFromElection(Election* election)
{
    if (!election) {
        std::cout << "Invalid election!\n";
        return;
    }
    std::string cid;
    std::cout << "Enter Candidate ID to delete: ";
    std::cin >> cid;
    bool found = false;
    for (int i = 0; i < election->getNumCandidates(); ++i) {
        Candidate* candidate = election->getCandidates()[i];
        if (candidate->getID() == cid) {
            election->removeCandidateByIndex(i);
            std::cout << "Candidate deleted from election!\n";
            found = true;
            break;
        }
    }
    if (!found) {
        std::cout << "Candidate not found in this election.\n";
    }
}

void Admin::viewElections() {
    std::ifstream file("data/elections.txt");
    std::string line;
    time_t now = time(nullptr);
    std::cout << "=== Elections ===\n";
    while (std::getline(file, line)) {
        ElectionInfo info;
        if (parseElectionLine(line, info)) {
            displayElection(info, now);
        }
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
