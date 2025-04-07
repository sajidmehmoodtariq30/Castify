#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include "user.h"
#include "candidate.h"
#include <string>

class FileHandler {
public:
    static void saveUser(const User* user);
    static User* loadUserWithPassword(const std::string& username, const std::string& password);
    static bool hasVoted(const std::string& userID, const std::string& electionID);
    static void saveVote( User* voter, Candidate* candidate);
    static void displayVotes();
};

#endif
