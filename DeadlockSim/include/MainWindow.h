#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QSpinBox>
#include <QTableWidget>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QHeaderView>
#include <QMessageBox>
#include <QComboBox>
#include <QLineEdit>
#include <QFrame>
#include <QSplitter>

#include "Banker.h"
#include "Detection.h"
#include "Recovery.h"
#include "RAGWidget.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // Banker's Algorithm
    void onBankerSetup();
    void onBankerCheck();
    void onBankerRequest();
    void onBankerClear();
    void onBankerLoadExample();

    // Detection
    void onDetectionSetup();
    void onDetectionRun();
    void onDetectionClear();
    void onDetectionLoadExample();

    // Recovery
    void onRecoveryTerminateAll();
    void onRecoveryTerminateOne();
    void onRecoveryClear();

private:
    void setupUI();
    void setupBankerTab();
    void setupDetectionTab();
    void setupRecoveryTab();
    void applyStyles();

    void rebuildBankerTables(int processes, int resources);
    void rebuildDetectionTables(int processes, int resources);
    void appendLog(QTextEdit* log, const QString& text, const QString& color = "#00ff88");

    // FIX: helper to refresh RAG after recovery actions
    void refreshRAGAfterRecovery();

    // ── Central ──
    QTabWidget* tabWidget;

    // ══ BANKER TAB ══
    QWidget*      bankerTab;
    QSpinBox*     bankerProcessSpin;
    QSpinBox*     bankerResourceSpin;
    QPushButton*  bankerSetupBtn;
    QPushButton*  bankerCheckBtn;
    QPushButton*  bankerRequestBtn;
    QPushButton*  bankerClearBtn;
    QPushButton*  bankerExampleBtn;

    QTableWidget* bankerAvailTable;
    QTableWidget* bankerMaxTable;
    QTableWidget* bankerAllocTable;
    QTableWidget* bankerNeedTable;

    QSpinBox*     bankerReqPidSpin;
    QTableWidget* bankerReqTable;
    QTextEdit*    bankerLog;

    int bankerP = 0;
    int bankerR = 0;

    // ══ DETECTION TAB ══
    QWidget*      detectionTab;
    QSpinBox*     detectionProcessSpin;
    QSpinBox*     detectionResourceSpin;
    QPushButton*  detectionSetupBtn;
    QPushButton*  detectionRunBtn;
    QPushButton*  detectionClearBtn;
    QPushButton*  detectionExampleBtn;

    QTableWidget* detectionAvailTable;
    QTableWidget* detectionAllocTable;
    QTableWidget* detectionRequestTable;

    QTextEdit*    detectionLog;
    RAGWidget*    ragWidget;

    int detectionP = 0;
    int detectionR = 0;

    // ══ RECOVERY TAB ══
    QWidget*     recoveryTab;
    QPushButton* recoveryTermAllBtn;
    QPushButton* recoveryTermOneBtn;
    QPushButton* recoveryClearBtn;
    QTextEdit*   recoveryLog;
    QLabel*      recoveryStatusLabel;

    // State passed from Detection → Recovery
    DetectionResult               lastDetectionResult;
    std::vector<std::vector<int>> lastAllocation;
    std::vector<std::vector<int>> lastRequest;    // FIX: store request matrix for RAG refresh
    std::vector<int>              lastAvailable;
    int lastDetP = 0;
    int lastDetR = 0;
};

#endif // MAINWINDOW_H
