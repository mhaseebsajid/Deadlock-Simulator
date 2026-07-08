#ifndef BANKER_H
#define BANKER_H

#include <vector>
#include <string>

struct BankerResult {
    bool isSafe;
    std::vector<int> safeSequence;
    std::string log;
};

class Banker {
public:
    int numProcesses;
    int numResources;
    std::vector<int> available;
    std::vector<std::vector<int>> maximum;
    std::vector<std::vector<int>> allocation;
    std::vector<std::vector<int>> need;

    Banker(int p, int r);
    void setAvailable(const std::vector<int>& avail);
    void setMaximum(const std::vector<std::vector<int>>& max);
    void setAllocation(const std::vector<std::vector<int>>& alloc);
    void computeNeed();
    BankerResult isSafeState();
    BankerResult requestResources(int pid, const std::vector<int>& request);
};

#endif // BANKER_H
