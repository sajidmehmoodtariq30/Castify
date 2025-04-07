#include "filehandler.h"
#include "admin.h"
#include "voter.h"
#include "candidate.h"
#include <fstream>
#include <sstream>

void FileHandler::saveUser(const User* user) {
    std::ofstream file("data/users.txt", std::ios::app);
    if (file.is_open()) {
        file << user->getID() << "," 
             << user->getUsername() << "," 
             << user->getPassword() << ","
             << user->getRole() << "\n";
        file.close();
    }
}

User* FileHandler::loadUserWithPassword(const std::string& username, const std::string& password) {
    std::ifstream file("data/users.txt");
    std::string line;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string id, uname, pass, role;
        std::getline(ss, id, ',');
        std::getline(ss, uname, ',');
        std::getline(ss, pass, ',');
        std::getline(ss, role, ',');

        if (uname == username && pass == password) {
            if (role == "admin")
                return new Admin(id, uname, pass);
            else if (role == "voter")
                return new Voter(id, uname, pass);
            else if (role == "candidate")
                return new Candidate(id, uname, pass);
        }
    }

    return nullptr;
}
