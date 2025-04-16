#include "nationalelection.h"
#include <iostream>

void NationalElection::displayElectionDetails() const {
    std::cout << "[National Election] ";
    Election::displayElectionDetails();
    // Add national election-specific display logic here
}
