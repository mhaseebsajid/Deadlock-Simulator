#include "Banker.h"
#include <sstream>

Banker::Banker(int p, int r)
    : numProcesses(p), numResources(r)
{
    available.assign(r, 0);
    maximum.assign(p, std::vector<int>(r, 0));
    allocation.assign(p, std::vector<int>(r, 0));
    need.assign(p, std::vector<int>(r, 0));
}

void Banker::setAvailable(const std::vector<int>& avail) {
    available = avail;
}

void Banker::setMaximum(const std::vector<std::vector<int>>& max) {
    maximum = max;
}

void Banker::setAllocation(const std::vector<std::vector<int>>& alloc) {
    allocation = alloc;
}

void Banker::computeNeed() {
    for (int i = 0; i < numProcesses; i++)
        for (int j = 0; j < numResources; j++)
            need[i][j] = maximum[i][j] - allocation[i][j];
}

BankerResult Banker::isSafeState() {
    std::ostringstream oss;
    std::vector<int> work = available;
    std::vector<bool> finish(numProcesses, false);
    std::vector<int> safeSeq;

    oss << "[Banker's Algorithm - Safety Check]\n";
    oss << "Initial Work (Available): ";
    for (int v : work) oss << v << " ";
    oss << "\n\n";

    int count = 0;
    while (count < numProcesses) {
        bool found = false;
        for (int i = 0; i < numProcesses; i++) {
            if (!finish[i]) {
                bool canAllocate = true;
                for (int j = 0; j < numResources; j++) {
                    if (need[i][j] > work[j]) {
                        canAllocate = false;
                        break;
                    }
                }
                if (canAllocate) {
                    oss << "P" << i << " can proceed. Releasing resources -> Work: ";
                    for (int j = 0; j < numResources; j++) {
                        work[j] += allocation[i][j];
                        oss << work[j] << " ";
                    }
                    oss << "\n";
                    finish[i] = true;
                    safeSeq.push_back(i);
                    found = true;
                    count++;
                }
            }
        }
        if (!found) break;
    }

    BankerResult result;
    result.safeSequence = safeSeq;

    bool allFinished = true;
    for (bool f : finish) if (!f) { allFinished = false; break; }

    result.isSafe = allFinished;

    if (result.isSafe) {
        oss << "\n✅ SYSTEM IS IN SAFE STATE\n";
        oss << "Safe Sequence: ";
        for (int i = 0; i < (int)safeSeq.size(); i++) {
            oss << "P" << safeSeq[i];
            if (i < (int)safeSeq.size() - 1) oss << " → ";
        }
        oss << "\n";
    } else {
        oss << "\n❌ SYSTEM IS IN UNSAFE STATE — DEADLOCK MAY OCCUR\n";
        oss << "Processes that could NOT complete: ";
        for (int i = 0; i < numProcesses; i++)
            if (!finish[i]) oss << "P" << i << " ";
        oss << "\n";
    }

    result.log = oss.str();
    return result;
}

BankerResult Banker::requestResources(int pid, const std::vector<int>& request) {
    std::ostringstream oss;
    oss << "[Resource Request by P" << pid << "]\n";
    oss << "Request: ";
    for (int v : request) oss << v << " ";
    oss << "\n";

    BankerResult result;

    // Step 1: Check request <= need
    for (int j = 0; j < numResources; j++) {
        if (request[j] > need[pid][j]) {
            oss << "❌ Error: Request exceeds maximum need for resource R" << j << "\n";
            result.isSafe = false;
            result.log = oss.str();
            return result;
        }
    }

    // Step 2: Check request <= available
    for (int j = 0; j < numResources; j++) {
        if (request[j] > available[j]) {
            oss << "⏳ Resources not available right now. P" << pid << " must WAIT.\n";
            result.isSafe = false;
            result.log = oss.str();
            return result;
        }
    }

    // Step 3: Pretend to allocate
    for (int j = 0; j < numResources; j++) {
        available[j]        -= request[j];
        allocation[pid][j]  += request[j];
        need[pid][j]        -= request[j];
    }

    oss << "Tentatively allocating resources...\n";

    // Step 4: Safety check
    result = isSafeState();

    if (!result.isSafe) {
        // Rollback
        for (int j = 0; j < numResources; j++) {
            available[j]        += request[j];
            allocation[pid][j]  -= request[j];
            need[pid][j]        += request[j];
        }
        oss << "⚠️  Rolled back: granting this request leads to unsafe state.\n";
    } else {
        oss << "✅ Request GRANTED. System remains in safe state.\n";
    }

    result.log = oss.str() + "\n" + result.log;
    return result;
}
