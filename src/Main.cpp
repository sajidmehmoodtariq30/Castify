#include <iostream>
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

    return 0;
}
