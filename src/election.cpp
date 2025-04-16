#include "election.h"
#include <iostream>
#include <ctime> // For time functions
#include <fstream>
#include <cstring>

std::string Election::getID() const { return id; }

Election::Election(std::string id, std::string title, time_t startTime, time_t endTime, std::string type, int criteria)
    : id(id), title(title), startTime(startTime), endTime(endTime), electionType(type), eligibilityCriteria(criteria), numCandidates(0), maxCandidates(5) {
    candidates = new Candidate*[maxCandidates];
}

Election::~Election() {
    for (int i = 0; i < numCandidates; ++i) {
        delete candidates[i]; // Free each Candidate object
    }
    delete[] candidates; // Free the array
}

bool Election::isElectionActive() const {
    time_t currentTime = time(nullptr); // Get the current time
    return currentTime >= startTime && currentTime <= endTime;
}

void Election::addCandidate(Candidate* candidate) {
    if (numCandidates >= maxCandidates) {
        // If array is full, expand it (doubling size)
        maxCandidates *= 2;
        Candidate** newCandidates = new Candidate*[maxCandidates];
        for (int i = 0; i < numCandidates; ++i) {
            newCandidates[i] = candidates[i];
        }
        delete[] candidates;
        candidates = newCandidates;
    }
    candidates[numCandidates++] = candidate;
}

void Election::setElectionType(const std::string& type) {
    electionType = type;
}

void Election::setEligibilityCriteria(int criteria) {
    eligibilityCriteria = criteria;
}

void Election::displayResults() const {
    std::cout << "\nElection Results for: " << title << " (ID: " << id << ")\n";
    int* voteCounts = new int[numCandidates];
    for (int i = 0; i < numCandidates; ++i) voteCounts[i] = 0;
    std::ifstream file("data/votes.txt");
    char line[256];
    while (file.getline(line, 256)) {
        char* voterID = strtok(line, ",");
        char* candidateID = strtok(NULL, ",");
        char* electionID = strtok(NULL, ",");
        if (electionID && id == electionID) {
            for (int i = 0; i < numCandidates; ++i) {
                if (candidateID && candidates[i]->getID() == candidateID) {
                    voteCounts[i]++;
                }
            }
        }
    }
    std::cout << "-------------------------------------\n";
    for (int i = 0; i < numCandidates; ++i) {
        std::cout << candidates[i]->getUsername() << " (" << candidates[i]->getID() << ") - Votes: " << voteCounts[i] << std::endl;
    }
    std::cout << "-------------------------------------\n";
    delete[] voteCounts;
}

void Election::displayElectionDetails() const {
    std::cout << "Election ID: " << id << "\nTitle: " << title
              << "\nStart Time: " << ctime(&startTime)
              << "End Time: " << ctime(&endTime)
              << "Type: " << electionType
              << "\nEligibility: " << eligibilityCriteria << std::endl;
}

void Election::displayCandidates() const {
    std::cout << "Candidates in the Election:\n";
    for (int i = 0; i < numCandidates; ++i) {
        candidates[i]->displayProfile();
    }
}
