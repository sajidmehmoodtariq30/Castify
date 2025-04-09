#ifndef CANDIDATE_H
#define CANDIDATE_H

#include "user.h"
#include <string>

class Candidate : public User {
private:
    std::string party;

public:
    Candidate(const std::string& id, const std::string& username, const std::string& password, const std::string& party);
    
    std::string getParty() const;
    void setParty(const std::string& newParty);
    
    void displayProfile() override;
    void displayMenu() override;
};

#endif
