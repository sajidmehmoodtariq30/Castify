#include "election.h"
#include <iostream>

Election::Election(std::string id, std::string title, std::string startDate, std::string endDate)
    : id(id), title(title), startDate(startDate), endDate(endDate), numCandidates(0), maxCandidates(5) {
    candidates = new Candidate*[maxCandidates];  // Allocate space for 5 candidates
}

Election::~Election() {
    // Free the dynamically allocated memory for candidates
    for (int i = 0; i < numCandidates; ++i) {
        delete candidates[i];  // Only delete candidate objects
    }
    delete[] candidates;  // Delete the array itself
}


void Election::addCandidate(Candidate* candidate) {
    std::cout << "Adding candidate: " << candidate->getUsername() << "\n";

    if (numCandidates >= maxCandidates) {
        std::cout << "Resizing candidates array...\n";
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
