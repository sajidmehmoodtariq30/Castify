#include "utils.h"
#include <sstream>
#include <iostream>

bool parseElectionLine(const std::string& line, ElectionInfo& info) {
    std::stringstream ss(line);
    std::string startStr, endStr;
    if (!std::getline(ss, info.id, ',')) return false;
    if (!std::getline(ss, info.title, ',')) return false;
    if (!std::getline(ss, startStr, ',')) return false;
    if (!std::getline(ss, endStr, ',')) return false;
    if (!std::getline(ss, info.type, ',')) return false;
    if (!std::getline(ss, info.criteria, ',')) info.criteria = "";
    info.start = std::stol(startStr);
    info.end = std::stol(endStr);
    return true;
}

bool isElectionActive(const ElectionInfo& info, time_t now) {
    return now >= info.start && now <= info.end;
}

void displayElection(const ElectionInfo& info, time_t now) {
    std::string status = isElectionActive(info, now) ? "[ACTIVE]" : "[INACTIVE]";
    std::cout << info.id << ": " << info.title << " (" << info.type << ") " << status << std::endl;
}

bool parseCandidateLine(const std::string& line, CandidateInfo& info) {
    std::stringstream ss(line);
    std::string votesStr;
    if (!std::getline(ss, info.id, ',')) return false;
    if (!std::getline(ss, info.name, ',')) return false;
    if (!std::getline(ss, info.party, ',')) return false;
    if (!std::getline(ss, votesStr, ',')) votesStr = "0";
    info.votes = std::stoi(votesStr);
    return true;
}

void displayCandidate(const CandidateInfo& info) {
    std::cout << info.id << ": " << info.name << " (" << info.party << ") Votes: " << info.votes << std::endl;
}
