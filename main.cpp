#include "src/header/User.h"
#include "src/header/Voter.h"
#include "src/header/Admin.h"
#include "src/header/Election.h"
#include "src/header/Candidate.h"
#include "src/header/Vote.h"
#include "src/header/ElectionSystem.h"
#include <iostream>

// Main function
int main() {
    ElectionSystem system;
    system.run();
    return 0;
}