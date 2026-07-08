#include "Detection.h"
#include <sstream>

Detection::Detection(int p, int r)
    : numProcesses(p), numResources(r)
{
    available.assign(r, 0);
    allocation.assign(p, std::vector<int>(r, 0));
    request.assign(p, std::vector<int>(r, 0));
}

void Detection::setAvailable(const std::vector<int>& avail) {
    available = avail;
}

void Detection::setAllocation(const std::vector<std::vector<int>>& alloc) {
    allocation = alloc;
}

void Detection::setRequest(const std::vector<std::vector<int>>& req) {
    request = req;
}

DetectionResult Detection::detect() {
    std::ostringstream oss;
    oss << "[Deadlock Detection Algorithm]\n\n";

    std::vector<int> work = available;
    std::vector<bool> finish(numProcesses, false);

    // Mark processes with zero allocation as finished
    for (int i = 0; i < numProcesses; i++) {
        bool zeroAlloc = true;
        for (int j = 0; j < numResources; j++) {
            if (allocation[i][j] != 0) { zeroAlloc = false; break; }
        }
        if (zeroAlloc) {
            finish[i] = true;
            oss << "P" << i << " has zero allocation → marked as finished.\n";
        }
    }

    oss << "\nWork (Available): ";
    for (int v : work) oss << v << " ";
    oss << "\n\n";

    bool found = true;
    while (found) {
        found = false;
        for (int i = 0; i < numProcesses; i++) {
            if (!finish[i]) {
                bool canFinish = true;
                for (int j = 0; j < numResources; j++) {
                    if (request[i][j] > work[j]) {
                        canFinish = false;
                        break;
                    }
                }
                if (canFinish) {
                    oss << "P" << i << " can finish. Releasing resources -> Work: ";
                    for (int j = 0; j < numResources; j++) {
                        work[j] += allocation[i][j];
                        oss << work[j] << " ";
                    }
                    oss << "\n";
                    finish[i] = true;
                    found = true;
                }
            }
        }
    }

    DetectionResult result;
    result.deadlockFound = false;

    for (int i = 0; i < numProcesses; i++) {
        if (!finish[i]) {
            result.deadlockFound = true;
            result.deadlockedProcesses.push_back(i);
        }
    }

    if (result.deadlockFound) {
        oss << "\n🔴 DEADLOCK DETECTED!\n";
        oss << "Deadlocked Processes: ";
        for (int p : result.deadlockedProcesses) oss << "P" << p << " ";
        oss << "\nThese processes are waiting for resources held by each other.\n";
    } else {
        oss << "\n✅ NO DEADLOCK — All processes can complete.\n";
    }

    result.log = oss.str();
    return result;
}
