#include "localelection.h"
#include <iostream>

void LocalElection::displayElectionDetails() const {
    std::cout << "[Local Election] ";
    Election::displayElectionDetails();
    // Local election-specific: show top 3 candidates as possible multiple winners
    std::cout << "Top 3 Candidates (by votes):\n";
    // Find top 3 candidates
    struct CandidateRank {
        int idx;
        int votes;
    };
    CandidateRank* ranks = new CandidateRank[numCandidates];
    for (int i = 0; i < numCandidates; ++i) {
        ranks[i].idx = i;
        ranks[i].votes = candidates[i]->getVoteCount();
    }
    // Simple selection sort for top 3
    for (int i = 0; i < numCandidates - 1; ++i) {
        for (int j = i + 1; j < numCandidates; ++j) {
            if (ranks[j].votes > ranks[i].votes) {
                CandidateRank tmp = ranks[i];
                ranks[i] = ranks[j];
                ranks[j] = tmp;
            }
        }
    }
    int topN = numCandidates < 3 ? numCandidates : 3;
    for (int i = 0; i < topN; ++i) {
        int idx = ranks[i].idx;
        std::cout << (i+1) << ". " << candidates[idx]->getUsername() << " (" << candidates[idx]->getID() << ") - Votes: " << candidates[idx]->getVoteCount() << std::endl;
    }
    delete[] ranks;
}
