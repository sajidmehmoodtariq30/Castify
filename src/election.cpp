#include "election.h"
#include <iostream>

std::string Election::getID() const { return id; }

Election::Election(std::string id, std::string title, std::string startDate, std::string endDate)
    : id(id), title(title), startDate(startDate), endDate(endDate), numCandidates(0), maxCandidates(5) {
    candidates = new Candidate*[maxCandidates];  // Allocate space for 5 candidates
}

Election::~Election() {
    // Free the dynamically allocated memory for candidates
    for (int i = 0; i < numCandidates; ++i) {
        delete candidates[i];
    }
    delete[] candidates;
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

void Election::displayElectionDetails() const {
    std::cout << "Election ID: " << id << "\nTitle: " << title << "\nStart Date: " << startDate << "\nEnd Date: " << endDate << std::endl;
}

void Election::displayCandidates() const {
    std::cout << "Candidates in the Election:\n";
    for (int i = 0; i < numCandidates; ++i) {
        candidates[i]->displayProfile();
    }
}
