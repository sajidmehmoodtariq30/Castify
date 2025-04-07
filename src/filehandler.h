#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include "user.h"
#include <string>
#include <fstream>

class FileHandler {
public:
    static void saveUser(const User* user);
    static User* loadUserByUsername(const std::string& username);
};

#endif
