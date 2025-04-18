#ifndef ELECTION_SYSTEM_H
#define ELECTION_SYSTEM_H

#include "User.h"
#include "Voter.h"
#include "Admin.h"
#include "Election.h"
#include "Candidate.h"
#include "Vote.h"
#include "Array.h"

// Forward declaration of FileHandler
class FileHandler;

// ElectionSystem class declaration
class ElectionSystem {
private:
    Array<Voter> voters;
    Array<Administrator> admins;
    Array<Election*> elections;
    User* currentUser;
    FileHandler* fileHandler;

public:
    ElectionSystem();
    ~ElectionSystem();
    
    void seedData();
    bool login(std::string username, std::string password);
    void logout();
    bool isLoggedIn() const;
    bool isAdmin() const;
    
    // Methods for system operation
    void registerVoter(std::string username, std::string password, std::string name, 
                      std::string id, std::string address, std::string voterIdNumber);
    void createElection(int electionType);
    void addCandidate();
    void displayElections() const;
    void manageElection();
    void castVote();
    void viewResults() const;
    
    // User interface methods
    void displayMainMenu() const;
    void displayAdminMenu() const;
    void displayVoterMenu() const;
    void run();
    
    // File handling methods
    bool saveData();
    bool loadData();
    
    // Getter methods for FileHandler
    Array<Voter>& getVoters() { return voters; }
    Array<Administrator>& getAdmins() { return admins; }
    Array<Election*>& getElections() { return elections; }
    
    // Const versions of getters
    const Array<Voter>& getVoters() const { return voters; }
    const Array<Administrator>& getAdmins() const { return admins; }
    const Array<Election*>& getElections() const { return elections; }
};

#endif // ELECTION_SYSTEM_H
