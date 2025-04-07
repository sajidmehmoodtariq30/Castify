#ifndef VOTER_H
#define VOTER_H

#include "user.h"

class Voter : public User {
public:
    Voter(std::string id, std::string username, std::string password);
    void displayProfile() override;
};

#endif
