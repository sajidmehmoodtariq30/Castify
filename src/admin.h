#ifndef ADMIN_H
#define ADMIN_H

#include "user.h"

class Admin : public User {
public:
    Admin(std::string id, std::string username, std::string password);
    void displayProfile() override;
};

#endif
