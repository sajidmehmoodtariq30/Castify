#ifndef LOCALELECTION_H
#define LOCALELECTION_H

#include "election.h"

class LocalElection : public Election {
public:
    LocalElection(std::string id, std::string title, time_t startTime, time_t endTime, int criteria)
        : Election(id, title, startTime, endTime, "Local", criteria) {}

    void displayElectionDetails() const override;
    // Add local election-specific logic here
};

#endif
