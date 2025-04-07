#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include "user.h"
#include <string>

class FileHandler {
public:
    static void saveUser(const User* user);
    static User* loadUserWithPassword(const std::string& username, const std::string& password);
};

#endif
