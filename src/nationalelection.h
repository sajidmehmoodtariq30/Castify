#ifndef NATIONALELECTION_H
#define NATIONALELECTION_H

#include "election.h"

class NationalElection : public Election {
public:
    NationalElection(std::string id, std::string title, time_t startTime, time_t endTime, int criteria)
        : Election(id, title, startTime, endTime, "National", criteria) {}

    void displayElectionDetails() const override;
    // Add national election-specific logic here
};

#endif
