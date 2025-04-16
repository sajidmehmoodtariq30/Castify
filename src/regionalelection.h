#ifndef REGIONALELECTION_H
#define REGIONALELECTION_H

#include "election.h"

class RegionalElection : public Election {
public:
    RegionalElection(std::string id, std::string title, time_t startTime, time_t endTime, int criteria)
        : Election(id, title, startTime, endTime, "Regional", criteria) {}
    void displayElectionDetails() const override;
};

#endif
