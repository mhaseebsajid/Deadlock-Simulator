#include "Recovery.h"
#include <sstream>

RecoveryResult Recovery::terminateAll(const DetectionResult& dr,
                                       std::vector<std::vector<int>>& allocation,
                                       std::vector<int>& available,
                                       int numResources)
{
    std::ostringstream oss;
    RecoveryResult result;
    result.strategy = "Terminate All Deadlocked Processes";

    oss << "[Recovery Strategy: TERMINATE ALL]\n\n";
    oss << "Terminating all deadlocked processes and releasing their resources...\n\n";

    for (int pid : dr.deadlockedProcesses) {
        oss << "Terminating P" << pid << " → releasing resources: ";
        for (int j = 0; j < numResources; j++) {
            available[j] += allocation[pid][j];
            oss << allocation[pid][j] << " ";
            allocation[pid][j] = 0;
        }
        oss << "\n";
        result.terminatedProcesses.push_back(pid);
    }

    oss << "\n✅ All deadlocked processes terminated.\n";
    oss << "Updated Available Resources: ";
    for (int v : available) oss << v << " ";
    oss << "\n";
    oss << "System can now continue execution.\n";

    result.log = oss.str();
    return result;
}

RecoveryResult Recovery::terminateOne(const DetectionResult& dr,
                                       std::vector<std::vector<int>>& allocation,
                                       std::vector<int>& available,
                                       int numResources)
{
    std::ostringstream oss;
    RecoveryResult result;
    result.strategy = "Terminate One Process (Least PID)";

    oss << "[Recovery Strategy: TERMINATE ONE PROCESS]\n\n";

    if (dr.deadlockedProcesses.empty()) {
        oss << "No deadlocked processes to terminate.\n";
        result.log = oss.str();
        return result;
    }

    int victim = dr.deadlockedProcesses[0];
    oss << "Selecting victim process: P" << victim << "\n";
    oss << "Releasing resources: ";
    for (int j = 0; j < numResources; j++) {
        available[j] += allocation[victim][j];
        oss << allocation[victim][j] << " ";
        allocation[victim][j] = 0;
    }
    oss << "\n";
    result.terminatedProcesses.push_back(victim);

    oss << "\n✅ P" << victim << " terminated and resources reclaimed.\n";
    oss << "Updated Available Resources: ";
    for (int v : available) oss << v << " ";
    oss << "\n";
    oss << "Run detection again to check if deadlock is fully resolved.\n";

    result.log = oss.str();
    return result;
}
