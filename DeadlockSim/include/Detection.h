#ifndef DETECTION_H
#define DETECTION_H

#include <vector>
#include <string>

struct DetectionResult {
    bool deadlockFound;
    std::vector<int> deadlockedProcesses;
    std::string log;
};

class Detection {
public:
    int numProcesses;
    int numResources;
    std::vector<int> available;
    std::vector<std::vector<int>> allocation;
    std::vector<std::vector<int>> request;

    Detection(int p, int r);
    void setAvailable(const std::vector<int>& avail);
    void setAllocation(const std::vector<std::vector<int>>& alloc);
    void setRequest(const std::vector<std::vector<int>>& req);
    DetectionResult detect();
};

#endif // DETECTION_H
