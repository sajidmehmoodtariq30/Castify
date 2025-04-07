#include <iostream>
#include "admin.h"
#include "voter.h"
#include "candidate.h"
#include "election.h"
#include "filehandler.h"

int main() {
    // Create a new election
    Election election("E1", "Presidential Election 2025", "2025-06-01", "2025-06-30");
    election.displayElectionDetails();

    // Create candidates
    Candidate* candidate1 = new Candidate("C1", "JohnDoe", "password123");
    Candidate* candidate2 = new Candidate("C2", "JaneSmith", "password456");

    // Add candidates to the election
    election.addCandidate(candidate1);
    election.addCandidate(candidate2);

    // Display candidates in the election
    election.displayCandidates();

    // Simulate voter login
    std::string username;
    std::cout << "Enter username to login: ";
    std::cin >> username;

    // Load voter from file (assuming only Voters can vote)
    User* user = FileHandler::loadUserWithPassword(username, "0000"); // Placeholder password
    if (!user || user->getRole() != "voter") {
        std::cout << "Invalid voter or not a valid voter.\n";
        return 0;
    }

    // Check if the voter has already voted
    if (FileHandler::hasVoted(user->getID(), election.getID())) {
        std::cout << "You have already voted in this election.\n";
        delete user;
        return 0;
    }

    // Prompt the voter to choose a candidate
    int choice;
    std::cout << "Enter candidate ID to vote (1 for JohnDoe, 2 for JaneSmith): ";
    std::cin >> choice;

    Candidate* selectedCandidate = (choice == 1) ? candidate1 : candidate2;

    // Save the vote
    FileHandler::saveVote(user, selectedCandidate, election.getID());
    std::cout << "Your vote for " << selectedCandidate->getUsername() << " has been saved!\n";

    // Display election results
    FileHandler::countVotes(election.getID(), new Candidate*[2]{candidate1, candidate2}, 2);

    return 0;
}
