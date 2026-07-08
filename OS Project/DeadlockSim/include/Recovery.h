#ifndef RECOVERY_H
#define RECOVERY_H

#include <vector>
#include <string>
#include "Detection.h"

struct RecoveryResult {
    std::string strategy;
    std::vector<int> terminatedProcesses;
    std::string log;
};

class Recovery {
public:
    RecoveryResult terminateAll(const DetectionResult& dr,
                                std::vector<std::vector<int>>& allocation,
                                std::vector<int>& available,
                                int numResources);

    RecoveryResult terminateOne(const DetectionResult& dr,
                                std::vector<std::vector<int>>& allocation,
                                std::vector<int>& available,
                                int numResources);
};

#endif // RECOVERY_H
