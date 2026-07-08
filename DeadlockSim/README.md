# Deadlock Simulation — OS Lab Project
**Department:** BS Cyber Security | **Institute:** NASTP IIT
**Subject:** Operating System Lab | **Submitted To:** Ms. Iqra Siddique
**Date:** May 3, 2026

---

## Group Members
| Name | Roll No |
|---|---|
| Muhammad Haseeb Sajid | F2024CY018 |
| Ali Muhammad | F2024CY027 |
| Hafiz Ahmed Riaz | F2024CY005 |
| Muhammad Ahmed | F2024CY033 |

---

## Project: Simulation of Deadlock Avoidance, Detection, and Recovery using C++ (Qt GUI)

### Features
- **Tab 1 — Banker's Algorithm:** Enter processes/resources, fill matrices, check safe state, send resource requests
- **Tab 2 — Deadlock Detection:** Run detection algorithm, view deadlocked processes + live Resource Allocation Graph (RAG)
- **Tab 3 — Recovery:** Terminate ALL deadlocked processes or ONE at a time with resource release log
- **Load Example** buttons on each tab for quick demo

---

## Project Structure
```
DeadlockSim/
├── DeadlockSim.pro       ← Qt Creator project (use this)
├── CMakeLists.txt        ← Alternative CMake build
├── README.md
├── include/
│   ├── Banker.h          ← Banker's Algorithm
│   ├── Detection.h       ← Deadlock Detection
│   ├── Recovery.h        ← Recovery Strategies
│   ├── RAGWidget.h       ← Resource Allocation Graph widget
│   └── MainWindow.h      ← Qt Main GUI Window
└── src/
    ├── main.cpp
    ├── Banker.cpp
    ├── Detection.cpp
    ├── Recovery.cpp
    ├── RAGWidget.cpp
    └── MainWindow.cpp
```

---

## How to Build & Run

### Option A — Qt Creator (Easiest)
1. Download Qt from https://www.qt.io/download-open-source
   - During install select: **Qt 5.15.x** → **MinGW** (Windows) or **GCC** (Linux)
2. Open **Qt Creator**
3. **File → Open File or Project** → select `DeadlockSim.pro`
4. Click **Configure Project**
5. Press **Ctrl+R** (Run) — it will compile and launch

### Option B — Command Line (qmake)
```bash
# Linux/macOS
qmake DeadlockSim.pro
make
./DeadlockSim

# Windows (MinGW)
qmake DeadlockSim.pro
mingw32-make
DeadlockSim.exe
```

### Option C — CMake
```bash
mkdir build && cd build
cmake .. -DCMAKE_PREFIX_PATH="C:/Qt/5.15.2/mingw81_64"   # adjust path
cmake --build .
```

---

## Algorithms

### Banker's Algorithm (Safety Check)
```
Work ← Available
Finish[i] ← false  for all i
LOOP:
  Find i: Finish[i]=false AND Need[i] ≤ Work
  Work ← Work + Allocation[i]
  Finish[i] ← true
END LOOP
If all Finish[i]=true → SAFE STATE  else UNSAFE
```

### Resource Request (Banker)
```
If Request[i] > Need[i]      → Error
If Request[i] > Available    → Wait
Tentatively allocate; run safety check
If safe → grant;  else → rollback
```

### Deadlock Detection
```
Work ← Available
Finish[i] ← (Allocation[i] == 0)
LOOP:
  Find i: Finish[i]=false AND Request[i] ≤ Work
  Work ← Work + Allocation[i];  Finish[i]=true
END LOOP
Processes with Finish[i]=false → DEADLOCKED
```

### Recovery Strategies
- **Terminate All:** Kill all deadlocked processes, release all their resources
- **Terminate One:** Kill lowest-PID deadlocked process, release its resources, recheck

---

## Sample Test Data (Banker Tab → Load Example)
| | R0 | R1 | R2 |
|--|--|--|--|
| Available | 3 | 3 | 2 |
| Max P0 | 7 | 5 | 3 | Alloc P0: 0 1 0 |
| Max P1 | 3 | 2 | 2 | Alloc P1: 2 0 0 |
| Max P2 | 9 | 0 | 2 | Alloc P2: 3 0 2 |
| Max P3 | 2 | 2 | 2 | Alloc P3: 2 1 1 |
| Max P4 | 4 | 3 | 3 | Alloc P4: 0 0 2 |

**Expected Safe Sequence:** P1 → P3 → P4 → P0 → P2
