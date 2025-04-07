#ifndef CANDIDATE_H
#define CANDIDATE_H

#include "user.h"

class Candidate : public User {
public:
    Candidate(std::string id, std::string username, std::string password);
    void displayProfile() override;
};

#endif
