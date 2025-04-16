#ifndef VOTER_H
#define VOTER_H

#include "user.h"
#include "election.h"

class Voter : public User {
public:
    Voter(std::string id, std::string username, std::string password);
    void displayProfile() override;
    void displayMenu() override; // Menu: view elections, view candidates, vote, check vote status, view voting history, logout
    bool hasVoted(const std::string& electionID) const;
    void castVote(Election* election, Candidate* candidate);
    void checkVoteStatus(const std::string& electionID) const;
};

#endif
