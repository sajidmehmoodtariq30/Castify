#include "localelection.h"
#include <iostream>

void LocalElection::displayElectionDetails() const {
    std::cout << "[Local Election] ";
    Election::displayElectionDetails();
    // Local election-specific: show top 3 getCandidates() as possible multiple winners
    std::cout << "Top 3 Candidates (by votes):\n";
    // Find top 3 getCandidates()
    struct CandidateRank {
        int idx;
        int votes;
    };
    CandidateRank* ranks = new CandidateRank[getNumCandidates()];
    for (int i = 0; i < getNumCandidates(); ++i) {
        ranks[i].idx = i;
        ranks[i].votes = getCandidates()[i]->getVoteCount();
    }
    // Simple selection sort for top 3
    for (int i = 0; i < getNumCandidates() - 1; ++i) {
        for (int j = i + 1; j < getNumCandidates(); ++j) {
            if (ranks[j].votes > ranks[i].votes) {
                CandidateRank tmp = ranks[i];
                ranks[i] = ranks[j];
                ranks[j] = tmp;
            }
        }
    }
    int topN = getNumCandidates() < 3 ? getNumCandidates() : 3;
    for (int i = 0; i < topN; ++i) {
        int idx = ranks[i].idx;
        std::cout << (i+1) << ". " << getCandidates()[idx]->getUsername() << " (" << getCandidates()[idx]->getID() << ") - Votes: " << getCandidates()[idx]->getVoteCount() << std::endl;
    }
    delete[] ranks;
}
