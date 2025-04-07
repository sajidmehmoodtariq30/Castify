#ifndef VOTE_H
#define VOTE_H

#include <string>
#include "user.h"
#include "candidate.h"

class Vote {
private:
    User* voter;
    Candidate* candidate;

public:
    Vote(User* voter, Candidate* candidate);
    void saveVote() const;
    void displayVote() const;
};

#endif
