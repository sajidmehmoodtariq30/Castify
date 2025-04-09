#ifndef USER_H
#define USER_H

#include <string>

class User
{
protected:
    std::string id;
    std::string username;
    std::string password;
    std::string role;

public:
    User(std::string id, std::string username, std::string password, std::string role);
    virtual void displayProfile() = 0;
    virtual void displayMenu() = 0;
    std::string getID() const;
    std::string getUsername() const;
    std::string getRole() const;
    std::string getPassword() const;
    virtual ~User() {}
};

#endif
