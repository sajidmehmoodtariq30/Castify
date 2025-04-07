#ifndef ELECTION_H
#define ELECTION_H

#include <string>
#include "candidate.h"

class Election {
private:
    std::string id;
    std::string title;
    std::string startDate;
    std::string endDate;
    Candidate** candidates;  // Dynamic array of pointers to Candidate
    int numCandidates;
    int maxCandidates;

public:
    Election(std::string id, std::string title, std::string startDate, std::string endDate);
    ~Election();
    void addCandidate(Candidate* candidate);
    void displayElectionDetails() const;
    void displayCandidates() const;
    std::string getID() const ;
};

#endif
