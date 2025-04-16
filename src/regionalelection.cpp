#include "regionalelection.h"
#include <iostream>

void RegionalElection::displayElectionDetails() const {
    std::cout << "[Regional Election] ";
    Election::displayElectionDetails();
}
