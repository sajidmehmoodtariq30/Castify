#ifndef ADMIN_H
#define ADMIN_H

#include "user.h"
#include "candidate.h"

class Admin : public User {
public:
    Admin(const std::string& id, const std::string& username, const std::string& password);

    void displayProfile() override;
    void displayMenu() override;
    void addCandidate();
    void viewCandidates();
    void updateCandidate();
    void deleteCandidate();
    void addVoter();
};

#endif
