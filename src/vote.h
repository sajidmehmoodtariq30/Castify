#ifndef VOTE_H
#define VOTE_H

#include <string>
#include "user.h"
#include "candidate.h"

class Vote {
private:
    User* voter;
    Candidate* candidate;
    std::string electionID;

public:
    Vote(User* voter, Candidate* candidate, const std::string& electionID);
    void saveVote() const;
    void displayVote() const;
    std::string getElectionID() const { return electionID; }
};

#endif
