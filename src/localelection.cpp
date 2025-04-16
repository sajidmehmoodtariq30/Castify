#include "localelection.h"
#include <iostream>

void LocalElection::displayElectionDetails() const {
    std::cout << "[Local Election] ";
    Election::displayElectionDetails();
    // Add local election-specific display logic here
}
