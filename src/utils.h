#ifndef UTILS_H
#define UTILS_H
#include <string>
#include <ctime>

struct ElectionInfo {
    std::string id, title, type, criteria;
    time_t start, end;
};

struct CandidateInfo {
    std::string id, name, party;
    int votes;
};

bool parseElectionLine(const std::string& line, ElectionInfo& info);
bool isElectionActive(const ElectionInfo& info, time_t now);
void displayElection(const ElectionInfo& info, time_t now);
bool parseCandidateLine(const std::string& line, CandidateInfo& info);
void displayCandidate(const CandidateInfo& info);

#endif
