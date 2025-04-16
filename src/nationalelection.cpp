#include "nationalelection.h"
#include <iostream>

void NationalElection::displayElectionDetails() const {
    std::cout << "[National Election] ";
    Election::displayElectionDetails();
    // National election-specific: show votes per party
    std::cout << "Party-wise Vote Breakdown:\n";
    // Count votes per party
    struct PartyCount { std::string party; int votes; };
    PartyCount* partyCounts = new PartyCount[numCandidates];
    int partyCount = 0;
    for (int i = 0; i < numCandidates; ++i) {
        std::string party = candidates[i]->getParty();
        int idx = -1;
        for (int j = 0; j < partyCount; ++j) {
            if (partyCounts[j].party == party) { idx = j; break; }
        }
        if (idx == -1) {
            partyCounts[partyCount].party = party;
            partyCounts[partyCount].votes = candidates[i]->getVoteCount();
            ++partyCount;
        } else {
            partyCounts[idx].votes += candidates[i]->getVoteCount();
        }
    }
    for (int i = 0; i < partyCount; ++i) {
        std::cout << "Party: " << partyCounts[i].party << ", Total Votes: " << partyCounts[i].votes << std::endl;
    }
    delete[] partyCounts;
}
