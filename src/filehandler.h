#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include "user.h"
#include "candidate.h"

class FileHandler {
public:
    static void saveUser(const User* user);
    static User* loadUserWithPassword(const std::string& username, const std::string& password);

    static bool hasVoted(const std::string& userID, const std::string& electionID);
    static void saveVote(User* voter, Candidate* candidate, const std::string& electionID);
    static void displayVotes();
    static void countVotes(const std::string& electionID);

    // Candidate CRUD
    static void saveCandidate(const Candidate& candidate);               // Create
    static void displayCandidates();                                     // Read
    static bool updateCandidate(const std::string& id, const std::string& newName, const std::string& newParty); // Update
    static bool deleteCandidate(const std::string& id);                  // Delete
};

#endif
