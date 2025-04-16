#ifndef ELECTION_H
#define ELECTION_H

#include <string>
#include <ctime> // For time_t
#include "candidate.h"

class Election {
private:
    std::string id;
    std::string title;
    time_t startTime; // Start time of the election
    time_t endTime;   // End time of the election
    Candidate** candidates; // Dynamic array of pointers to Candidate
    int numCandidates;
    int maxCandidates;
    std::string electionType; // e.g., "General", "Local"
    int eligibilityCriteria;  // Minimum age for eligibility

public:
    Election(std::string id, std::string title, time_t startTime, time_t endTime, std::string type, int criteria);
    ~Election();
    void addCandidate(Candidate* candidate);
    virtual void displayElectionDetails() const;
    virtual void displayResults() const;
    void displayCandidates() const;
    bool isElectionActive() const; // Check if the election is active
    std::string getID() const;
    void setElectionType(const std::string& type);
    void setEligibilityCriteria(int criteria);
    std::string getElectionType() const;
    int getEligibilityCriteria() const;
};

#endif
