#include "MainWindow.h"
#include <QApplication>
#include <QSizePolicy>
#include <algorithm>

// ─────────────────────────────────────────────────────
//  Constructor / Destructor
// ─────────────────────────────────────────────────────
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle("Deadlock Simulation — OS Project | NASTP IIT Cyber Security");
    setMinimumSize(1100, 750);
    setupUI();
    applyStyles();
}
MainWindow::~MainWindow() {}

// ─────────────────────────────────────────────────────
//  Stylesheet
// ─────────────────────────────────────────────────────
void MainWindow::applyStyles()
{
    setStyleSheet(R"(
        QMainWindow, QWidget {
            background-color: #1e1e2e;
            color: #cdd6f4;
            font-family: 'Segoe UI', Arial, sans-serif;
            font-size: 13px;
        }
        QTabWidget::pane {
            border: 1px solid #45475a;
            background: #1e1e2e;
            border-radius: 6px;
        }
        QTabBar::tab {
            background: #313244;
            color: #cdd6f4;
            padding: 10px 24px;
            margin-right: 3px;
            border-radius: 6px 6px 0 0;
            font-weight: bold;
            font-size: 13px;
        }
        QTabBar::tab:selected { background: #89b4fa; color: #1e1e2e; }
        QTabBar::tab:hover    { background: #585b70; }
        QGroupBox {
            border: 1px solid #45475a;
            border-radius: 8px;
            margin-top: 12px;
            padding: 10px;
            font-weight: bold;
            color: #89b4fa;
        }
        QGroupBox::title { subcontrol-origin: margin; left: 12px; padding: 0 6px; }
        QTableWidget {
            background-color: #181825;
            color: #cdd6f4;
            gridline-color: #45475a;
            border: 1px solid #45475a;
            border-radius: 6px;
            selection-background-color: #89b4fa;
            selection-color: #1e1e2e;
        }
        QHeaderView::section {
            background-color: #313244;
            color: #89b4fa;
            border: 1px solid #45475a;
            padding: 5px;
            font-weight: bold;
        }
        QSpinBox, QLineEdit, QComboBox {
            background-color: #313244;
            color: #cdd6f4;
            border: 1px solid #45475a;
            border-radius: 5px;
            padding: 5px 8px;
            min-height: 26px;
        }
        QSpinBox:focus, QLineEdit:focus { border: 1px solid #89b4fa; }
        QPushButton {
            background-color: #45475a;
            color: #cdd6f4;
            border: none;
            border-radius: 6px;
            padding: 8px 16px;
            font-weight: bold;
            font-size: 13px;
            min-width: 110px;
        }
        QPushButton:hover   { background-color: #585b70; }
        QPushButton:pressed { background-color: #313244; }
        QPushButton#btnPrimary { background-color: #89b4fa; color: #1e1e2e; }
        QPushButton#btnPrimary:hover { background-color: #b4d0fb; }
        QPushButton#btnSuccess { background-color: #a6e3a1; color: #1e1e2e; }
        QPushButton#btnSuccess:hover { background-color: #c3f0bf; }
        QPushButton#btnDanger  { background-color: #f38ba8; color: #1e1e2e; }
        QPushButton#btnDanger:hover  { background-color: #f5a9bc; }
        QPushButton#btnWarning { background-color: #fab387; color: #1e1e2e; }
        QPushButton#btnWarning:hover { background-color: #fbc9a7; }
        QPushButton#btnInfo    { background-color: #94e2d5; color: #1e1e2e; }
        QPushButton#btnInfo:hover    { background-color: #b5ece6; }
        QTextEdit {
            background-color: #11111b;
            color: #a6e3a1;
            border: 1px solid #45475a;
            border-radius: 6px;
            font-family: 'Courier New', monospace;
            font-size: 12px;
            padding: 8px;
        }
        QLabel#titleLabel {
            font-size: 17px;
            font-weight: bold;
            color: #89b4fa;
            padding: 4px 0;
        }
        QLabel#subtitleLabel {
            font-size: 12px;
            color: #6c7086;
        }
        QSplitter::handle { background: #45475a; }
        QScrollBar:vertical {
            background: #181825; width: 10px; border-radius: 5px;
        }
        QScrollBar::handle:vertical {
            background: #45475a; border-radius: 5px; min-height: 20px;
        }
        QScrollBar::handle:vertical:hover { background: #89b4fa; }
        QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical { height: 0; }
    )");
}

// ─────────────────────────────────────────────────────
//  Setup — main layout
// ─────────────────────────────────────────────────────
void MainWindow::setupUI()
{
    QWidget* central = new QWidget(this);
    setCentralWidget(central);
    QVBoxLayout* mainL = new QVBoxLayout(central);
    mainL->setContentsMargins(12, 10, 12, 10);
    mainL->setSpacing(6);

    QLabel* title = new QLabel("Deadlock Avoidance, Detection & Recovery Simulator");
    title->setObjectName("titleLabel");
    title->setAlignment(Qt::AlignCenter);

    QLabel* sub = new QLabel(
        "BS Cyber Security — Operating System Lab  |  NASTP Institute of Information Technology  |  Submitted to: Ms. Iqra Siddique");
    sub->setObjectName("subtitleLabel");
    sub->setAlignment(Qt::AlignCenter);

    mainL->addWidget(title);
    mainL->addWidget(sub);

    QFrame* line = new QFrame();
    line->setFrameShape(QFrame::HLine);
    line->setStyleSheet("color:#45475a;");
    mainL->addWidget(line);

    tabWidget = new QTabWidget();
    mainL->addWidget(tabWidget);

    setupBankerTab();
    setupDetectionTab();
    setupRecoveryTab();
}

// ─────────────────────────────────────────────────────
//  BANKER TAB
// ─────────────────────────────────────────────────────
void MainWindow::setupBankerTab()
{
    bankerTab = new QWidget();
    QVBoxLayout* mainL = new QVBoxLayout(bankerTab);
    mainL->setSpacing(8);

    // Config row
    QGroupBox* cfg = new QGroupBox("Step 1 — Configure");
    QHBoxLayout* cfgL = new QHBoxLayout(cfg);
    cfgL->addWidget(new QLabel("Processes:"));
    bankerProcessSpin = new QSpinBox(); bankerProcessSpin->setRange(1,10); bankerProcessSpin->setValue(5);
    cfgL->addWidget(bankerProcessSpin);
    cfgL->addWidget(new QLabel("Resources:"));
    bankerResourceSpin = new QSpinBox(); bankerResourceSpin->setRange(1,8); bankerResourceSpin->setValue(3);
    cfgL->addWidget(bankerResourceSpin);
    bankerSetupBtn = new QPushButton("⚙  Setup Tables"); bankerSetupBtn->setObjectName("btnPrimary");
    cfgL->addWidget(bankerSetupBtn);
    bankerExampleBtn = new QPushButton("📋  Load Example"); bankerExampleBtn->setObjectName("btnInfo");
    cfgL->addWidget(bankerExampleBtn);
    bankerClearBtn = new QPushButton("🗑  Clear");
    cfgL->addWidget(bankerClearBtn);
    cfgL->addStretch();
    mainL->addWidget(cfg);

    // Tables row
    QHBoxLayout* tablesRow = new QHBoxLayout();

    auto makeBox = [](const QString& title, QTableWidget*& tbl, bool readOnly=false) {
        QGroupBox* box = new QGroupBox(title);
        QVBoxLayout* l = new QVBoxLayout(box);
        tbl = new QTableWidget();
        if (readOnly) tbl->setEditTriggers(QAbstractItemView::NoEditTriggers);
        l->addWidget(tbl);
        return box;
    };

    tablesRow->addWidget(makeBox("Available Resources", bankerAvailTable), 1);
    tablesRow->addWidget(makeBox("Maximum Matrix",      bankerMaxTable),   2);
    tablesRow->addWidget(makeBox("Allocation Matrix",   bankerAllocTable), 2);
    tablesRow->addWidget(makeBox("Need Matrix (auto)",  bankerNeedTable, true), 2);
    mainL->addLayout(tablesRow, 3);

    // Action row
    QHBoxLayout* actRow = new QHBoxLayout();

    QGroupBox* safeBox = new QGroupBox("Step 2 — Safety Check");
    QVBoxLayout* safeL = new QVBoxLayout(safeBox);
    bankerCheckBtn = new QPushButton("🔍  Check Safe State"); bankerCheckBtn->setObjectName("btnSuccess");
    safeL->addWidget(bankerCheckBtn);
    safeL->addWidget(new QLabel("Runs Banker's Algorithm\nto find safe sequence."));
    actRow->addWidget(safeBox, 1);

    QGroupBox* reqBox = new QGroupBox("Step 3 — Resource Request");
    QGridLayout* reqL = new QGridLayout(reqBox);
    reqL->addWidget(new QLabel("Process ID (Pid):"), 0, 0);
    bankerReqPidSpin = new QSpinBox(); bankerReqPidSpin->setRange(0,9);
    reqL->addWidget(bankerReqPidSpin, 0, 1);
    reqL->addWidget(new QLabel("Request vector:"), 1, 0, 1, 3);
    bankerReqTable = new QTableWidget(1, 3);
    bankerReqTable->setMaximumHeight(55);
    reqL->addWidget(bankerReqTable, 2, 0, 1, 3);
    bankerRequestBtn = new QPushButton("📨  Send Request"); bankerRequestBtn->setObjectName("btnWarning");
    reqL->addWidget(bankerRequestBtn, 3, 0, 1, 3);
    actRow->addWidget(reqBox, 2);

    mainL->addLayout(actRow, 1);

    // Log
    QGroupBox* logBox = new QGroupBox("Output Log");
    QVBoxLayout* logL = new QVBoxLayout(logBox);
    bankerLog = new QTextEdit(); bankerLog->setReadOnly(true); bankerLog->setMinimumHeight(140);
    logL->addWidget(bankerLog);
    mainL->addWidget(logBox, 2);

    tabWidget->addTab(bankerTab, "🏦  Banker's Algorithm");

    connect(bankerSetupBtn,   &QPushButton::clicked, this, &MainWindow::onBankerSetup);
    connect(bankerCheckBtn,   &QPushButton::clicked, this, &MainWindow::onBankerCheck);
    connect(bankerRequestBtn, &QPushButton::clicked, this, &MainWindow::onBankerRequest);
    connect(bankerClearBtn,   &QPushButton::clicked, this, &MainWindow::onBankerClear);
    connect(bankerExampleBtn, &QPushButton::clicked, this, &MainWindow::onBankerLoadExample);

    rebuildBankerTables(5, 3);
}

// ─────────────────────────────────────────────────────
//  DETECTION TAB
// ─────────────────────────────────────────────────────
void MainWindow::setupDetectionTab()
{
    detectionTab = new QWidget();
    QVBoxLayout* mainL = new QVBoxLayout(detectionTab);
    mainL->setSpacing(8);

    // Config
    QGroupBox* cfg = new QGroupBox("Step 1 — Configure");
    QHBoxLayout* cfgL = new QHBoxLayout(cfg);
    cfgL->addWidget(new QLabel("Processes:"));
    detectionProcessSpin = new QSpinBox(); detectionProcessSpin->setRange(1,10); detectionProcessSpin->setValue(4);
    cfgL->addWidget(detectionProcessSpin);
    cfgL->addWidget(new QLabel("Resources:"));
    detectionResourceSpin = new QSpinBox(); detectionResourceSpin->setRange(1,8); detectionResourceSpin->setValue(2);
    cfgL->addWidget(detectionResourceSpin);
    detectionSetupBtn = new QPushButton("⚙  Setup Tables"); detectionSetupBtn->setObjectName("btnPrimary");
    cfgL->addWidget(detectionSetupBtn);
    detectionExampleBtn = new QPushButton("📋  Load Example (Deadlock)"); detectionExampleBtn->setObjectName("btnInfo");
    cfgL->addWidget(detectionExampleBtn);
    detectionClearBtn = new QPushButton("🗑  Clear");
    cfgL->addWidget(detectionClearBtn);
    cfgL->addStretch();
    mainL->addWidget(cfg);

    // Splitter: tables left, RAG right
    QSplitter* splitter = new QSplitter(Qt::Horizontal);

    QWidget* tablesPanel = new QWidget();
    QVBoxLayout* tpL = new QVBoxLayout(tablesPanel);
    tpL->setContentsMargins(0,0,0,0);

    QHBoxLayout* tablesRow = new QHBoxLayout();
    QGroupBox* availBox = new QGroupBox("Available");
    QVBoxLayout* availL = new QVBoxLayout(availBox);
    detectionAvailTable = new QTableWidget();
    detectionAvailTable->setMaximumHeight(70);
    availL->addWidget(detectionAvailTable);
    tablesRow->addWidget(availBox,1);

    QGroupBox* allocBox = new QGroupBox("Allocation Matrix");
    QVBoxLayout* allocL = new QVBoxLayout(allocBox);
    detectionAllocTable = new QTableWidget();
    allocL->addWidget(detectionAllocTable);
    tablesRow->addWidget(allocBox,2);

    QGroupBox* reqBox = new QGroupBox("Request Matrix");
    QVBoxLayout* reqL = new QVBoxLayout(reqBox);
    detectionRequestTable = new QTableWidget();
    reqL->addWidget(detectionRequestTable);
    tablesRow->addWidget(reqBox,2);

    tpL->addLayout(tablesRow);

    // Run button
    QGroupBox* runBox = new QGroupBox("Step 2 — Detect Deadlock");
    QHBoxLayout* runL = new QHBoxLayout(runBox);
    detectionRunBtn = new QPushButton("🔎  Run Detection Algorithm"); detectionRunBtn->setObjectName("btnDanger");
    runL->addWidget(detectionRunBtn);
    runL->addWidget(new QLabel("Identifies deadlocked processes using resource-request graph algorithm."));
    runL->addStretch();
    tpL->addWidget(runBox);

    // Log
    QGroupBox* logBox = new QGroupBox("Output Log");
    QVBoxLayout* logL = new QVBoxLayout(logBox);
    detectionLog = new QTextEdit(); detectionLog->setReadOnly(true);
    logL->addWidget(detectionLog);
    tpL->addWidget(logBox);

    splitter->addWidget(tablesPanel);

    // RAG panel
    QGroupBox* ragBox = new QGroupBox("Resource Allocation Graph (RAG)");
    QVBoxLayout* ragL = new QVBoxLayout(ragBox);
    ragWidget = new RAGWidget();
    ragL->addWidget(ragWidget);
    splitter->addWidget(ragBox);

    splitter->setStretchFactor(0, 3);
    splitter->setStretchFactor(1, 2);

    mainL->addWidget(splitter);

    tabWidget->addTab(detectionTab, "🔎  Deadlock Detection");

    connect(detectionSetupBtn,   &QPushButton::clicked, this, &MainWindow::onDetectionSetup);
    connect(detectionRunBtn,     &QPushButton::clicked, this, &MainWindow::onDetectionRun);
    connect(detectionClearBtn,   &QPushButton::clicked, this, &MainWindow::onDetectionClear);
    connect(detectionExampleBtn, &QPushButton::clicked, this, &MainWindow::onDetectionLoadExample);

    rebuildDetectionTables(4, 2);
}

// ─────────────────────────────────────────────────────
//  RECOVERY TAB
// ─────────────────────────────────────────────────────
void MainWindow::setupRecoveryTab()
{
    recoveryTab = new QWidget();
    QVBoxLayout* mainL = new QVBoxLayout(recoveryTab);
    mainL->setSpacing(10);

    QGroupBox* infoBox = new QGroupBox("Recovery Information");
    QVBoxLayout* infoL = new QVBoxLayout(infoBox);
    recoveryStatusLabel = new QLabel(
        "ℹ️  Run Deadlock Detection first.\n"
        "Results will be automatically loaded here for recovery.");
    recoveryStatusLabel->setWordWrap(true);
    recoveryStatusLabel->setStyleSheet("color:#f9e2af; font-size:13px; padding:6px;");
    infoL->addWidget(recoveryStatusLabel);
    mainL->addWidget(infoBox);

    QGroupBox* stratBox = new QGroupBox("Step 1 — Choose Recovery Strategy");
    QHBoxLayout* stratL = new QHBoxLayout(stratBox);

    QVBoxLayout* s1 = new QVBoxLayout();
    recoveryTermAllBtn = new QPushButton("💀  Terminate ALL Deadlocked");
    recoveryTermAllBtn->setObjectName("btnDanger");
    recoveryTermAllBtn->setMinimumHeight(48);
    s1->addWidget(recoveryTermAllBtn);
    QLabel* l1 = new QLabel("Terminates ALL deadlocked processes\nand releases their resources immediately.");
    l1->setStyleSheet("color:#6c7086; font-size:11px;");
    s1->addWidget(l1);

    QVBoxLayout* s2 = new QVBoxLayout();
    recoveryTermOneBtn = new QPushButton("✂️  Terminate ONE Process");
    recoveryTermOneBtn->setObjectName("btnWarning");
    recoveryTermOneBtn->setMinimumHeight(48);
    s2->addWidget(recoveryTermOneBtn);
    QLabel* l2 = new QLabel("Terminates only the lowest-priority\ndeadlocked process. Re-run detection after.");
    l2->setStyleSheet("color:#6c7086; font-size:11px;");
    s2->addWidget(l2);

    QVBoxLayout* s3 = new QVBoxLayout();
    recoveryClearBtn = new QPushButton("🗑  Clear Log");
    s3->addWidget(recoveryClearBtn);
    s3->addStretch();

    stratL->addLayout(s1);
    stratL->addLayout(s2);
    stratL->addLayout(s3);
    mainL->addWidget(stratBox);

    QGroupBox* logBox = new QGroupBox("Recovery Output Log");
    QVBoxLayout* logL = new QVBoxLayout(logBox);
    recoveryLog = new QTextEdit(); recoveryLog->setReadOnly(true);
    logL->addWidget(recoveryLog);
    mainL->addWidget(logBox, 2);

    tabWidget->addTab(recoveryTab, "🔧  Recovery");

    connect(recoveryTermAllBtn, &QPushButton::clicked, this, &MainWindow::onRecoveryTerminateAll);
    connect(recoveryTermOneBtn, &QPushButton::clicked, this, &MainWindow::onRecoveryTerminateOne);
    connect(recoveryClearBtn,   &QPushButton::clicked, this, &MainWindow::onRecoveryClear);
}

// ─────────────────────────────────────────────────────
//  HELPERS
// ─────────────────────────────────────────────────────
void MainWindow::rebuildBankerTables(int p, int r)
{
    bankerP = p; bankerR = r;
    QStringList rH, pH;
    for (int j=0;j<r;j++) rH<<"R"+QString::number(j);
    for (int i=0;i<p;i++) pH<<"P"+QString::number(i);

    // Available 1×r
    bankerAvailTable->setRowCount(1); bankerAvailTable->setColumnCount(r);
    bankerAvailTable->setHorizontalHeaderLabels(rH);
    bankerAvailTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    bankerAvailTable->verticalHeader()->setVisible(false);
    bankerAvailTable->setMaximumHeight(65);
    for (int j=0;j<r;j++){auto* it=new QTableWidgetItem("0");it->setTextAlignment(Qt::AlignCenter);bankerAvailTable->setItem(0,j,it);}

    for (QTableWidget* tbl:{bankerMaxTable,bankerAllocTable,bankerNeedTable}){
        tbl->setRowCount(p); tbl->setColumnCount(r);
        tbl->setHorizontalHeaderLabels(rH); tbl->setVerticalHeaderLabels(pH);
        tbl->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        tbl->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        for(int i=0;i<p;i++) for(int j=0;j<r;j++){auto* it=new QTableWidgetItem("0");it->setTextAlignment(Qt::AlignCenter);tbl->setItem(i,j,it);}
    }

    bankerReqTable->setRowCount(1); bankerReqTable->setColumnCount(r);
    bankerReqTable->setHorizontalHeaderLabels(rH);
    bankerReqTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    bankerReqTable->verticalHeader()->setVisible(false);
    for(int j=0;j<r;j++){auto* it=new QTableWidgetItem("0");it->setTextAlignment(Qt::AlignCenter);bankerReqTable->setItem(0,j,it);}
    bankerReqPidSpin->setRange(0,p-1);
}

void MainWindow::rebuildDetectionTables(int p, int r)
{
    detectionP = p; detectionR = r;
    QStringList rH, pH;
    for(int j=0;j<r;j++) rH<<"R"+QString::number(j);
    for(int i=0;i<p;i++) pH<<"P"+QString::number(i);

    detectionAvailTable->setRowCount(1); detectionAvailTable->setColumnCount(r);
    detectionAvailTable->setHorizontalHeaderLabels(rH);
    detectionAvailTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    detectionAvailTable->verticalHeader()->setVisible(false);
    detectionAvailTable->setMaximumHeight(65);
    for(int j=0;j<r;j++){auto* it=new QTableWidgetItem("0");it->setTextAlignment(Qt::AlignCenter);detectionAvailTable->setItem(0,j,it);}

    for(QTableWidget* tbl:{detectionAllocTable,detectionRequestTable}){
        tbl->setRowCount(p); tbl->setColumnCount(r);
        tbl->setHorizontalHeaderLabels(rH); tbl->setVerticalHeaderLabels(pH);
        tbl->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        tbl->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        for(int i=0;i<p;i++) for(int j=0;j<r;j++){auto* it=new QTableWidgetItem("0");it->setTextAlignment(Qt::AlignCenter);tbl->setItem(i,j,it);}
    }
}

void MainWindow::appendLog(QTextEdit* log, const QString& text, const QString& color)
{
    log->append(QString("<span style='color:%1; white-space:pre; font-family:Courier New;'>%2</span>")
        .arg(color)
        .arg(text.toHtmlEscaped().replace("\n","<br>").replace(" ","&nbsp;")));
}

// ─────────────────────────────────────────────────────
//  BANKER SLOTS
// ─────────────────────────────────────────────────────
void MainWindow::onBankerSetup()
{
    rebuildBankerTables(bankerProcessSpin->value(), bankerResourceSpin->value());
    appendLog(bankerLog,
        QString("Tables ready: %1 processes, %2 resources.\nFill in Available, Maximum, Allocation then click Check Safe State.")
        .arg(bankerP).arg(bankerR), "#89b4fa");
}

void MainWindow::onBankerLoadExample()
{
    // Classic textbook example: 5 processes, 3 resources (A=10, B=5, C=7)
    bankerProcessSpin->setValue(5); bankerResourceSpin->setValue(3);
    rebuildBankerTables(5, 3);

    // Available: 3 3 2
    int avail[]={3,3,2};
    for(int j=0;j<3;j++) bankerAvailTable->item(0,j)->setText(QString::number(avail[j]));

    // Max matrix
    int maxD[5][3]={{7,5,3},{3,2,2},{9,0,2},{2,2,2},{4,3,3}};
    int allocD[5][3]={{0,1,0},{2,0,0},{3,0,2},{2,1,1},{0,0,2}};
    for(int i=0;i<5;i++) for(int j=0;j<3;j++){
        bankerMaxTable->item(i,j)->setText(QString::number(maxD[i][j]));
        bankerAllocTable->item(i,j)->setText(QString::number(allocD[i][j]));
    }
    appendLog(bankerLog, "Example loaded (5 processes, 3 resources A/B/C).\nExpected safe sequence: P1 → P3 → P4 → P0 → P2", "#94e2d5");
}

void MainWindow::onBankerCheck()
{
    if(bankerP==0||bankerR==0){QMessageBox::warning(this,"Setup","Click Setup Tables first.");return;}

    // ── FIX: Input validation ──────────────────────────────────────────────
    for(int i=0;i<bankerP;i++){
        for(int j=0;j<bankerR;j++){
            bool okMax, okAlloc;
            int maxVal  = bankerMaxTable->item(i,j)  ? bankerMaxTable->item(i,j)->text().toInt(&okMax)   : 0;
            int allocVal= bankerAllocTable->item(i,j) ? bankerAllocTable->item(i,j)->text().toInt(&okAlloc): 0;

            if(!okMax || !okAlloc || maxVal < 0 || allocVal < 0){
                QMessageBox::warning(this,"Invalid Input",
                    QString("Invalid value at P%1, R%2. All values must be non-negative integers.").arg(i).arg(j));
                return;
            }
            if(allocVal > maxVal){
                QMessageBox::warning(this,"Invalid Input",
                    QString("P%1: Allocation for R%2 (%3) exceeds Maximum (%4).\nAllocation cannot exceed Maximum demand.")
                    .arg(i).arg(j).arg(allocVal).arg(maxVal));
                return;
            }
        }
    }
    for(int j=0;j<bankerR;j++){
        bool ok;
        int val = bankerAvailTable->item(0,j) ? bankerAvailTable->item(0,j)->text().toInt(&ok) : 0;
        if(!ok || val < 0){
            QMessageBox::warning(this,"Invalid Input",
                QString("Invalid available value for R%1. Must be a non-negative integer.").arg(j));
            return;
        }
    }
    // ── End validation ─────────────────────────────────────────────────────

    std::vector<int> avail(bankerR);
    for(int j=0;j<bankerR;j++) avail[j]=bankerAvailTable->item(0,j)->text().toInt();

    std::vector<std::vector<int>> max(bankerP,std::vector<int>(bankerR));
    std::vector<std::vector<int>> alloc(bankerP,std::vector<int>(bankerR));
    for(int i=0;i<bankerP;i++) for(int j=0;j<bankerR;j++){
        max[i][j]  = bankerMaxTable->item(i,j)->text().toInt();
        alloc[i][j]= bankerAllocTable->item(i,j)->text().toInt();
    }

    Banker banker(bankerP,bankerR);
    banker.setAvailable(avail);
    banker.setMaximum(max);
    banker.setAllocation(alloc);
    banker.computeNeed();

    for(int i=0;i<bankerP;i++) for(int j=0;j<bankerR;j++){
        auto* it=new QTableWidgetItem(QString::number(banker.need[i][j]));
        it->setTextAlignment(Qt::AlignCenter);
        bankerNeedTable->setItem(i,j,it);
    }

    BankerResult res=banker.isSafeState();
    appendLog(bankerLog,"━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━","#45475a");
    appendLog(bankerLog,QString::fromStdString(res.log), res.isSafe?"#a6e3a1":"#f38ba8");
}

void MainWindow::onBankerRequest()
{
    if(bankerP==0||bankerR==0){QMessageBox::warning(this,"Setup","Click Setup Tables first.");return;}

    // ── FIX: Input validation for request vector ───────────────────────────
    for(int j=0;j<bankerR;j++){
        bool ok;
        int val = bankerReqTable->item(0,j) ? bankerReqTable->item(0,j)->text().toInt(&ok) : 0;
        if(!ok || val < 0){
            QMessageBox::warning(this,"Invalid Input",
                QString("Invalid request value for R%1. Must be a non-negative integer.").arg(j));
            return;
        }
    }
    // ── End validation ─────────────────────────────────────────────────────

    int pid=bankerReqPidSpin->value();
    std::vector<int> avail(bankerR);
    for(int j=0;j<bankerR;j++) avail[j]=bankerAvailTable->item(0,j)->text().toInt();

    std::vector<std::vector<int>> max(bankerP,std::vector<int>(bankerR));
    std::vector<std::vector<int>> alloc(bankerP,std::vector<int>(bankerR));
    for(int i=0;i<bankerP;i++) for(int j=0;j<bankerR;j++){
        max[i][j]  = bankerMaxTable->item(i,j)->text().toInt();
        alloc[i][j]= bankerAllocTable->item(i,j)->text().toInt();
    }
    std::vector<int> req(bankerR);
    for(int j=0;j<bankerR;j++) req[j]=bankerReqTable->item(0,j)->text().toInt();

    Banker banker(bankerP,bankerR);
    banker.setAvailable(avail); banker.setMaximum(max); banker.setAllocation(alloc); banker.computeNeed();
    BankerResult res=banker.requestResources(pid,req);

    // ── FIX: Update UI tables if request was granted ───────────────────────
    if(res.isSafe){
        // Update Available row
        for(int j=0;j<bankerR;j++){
            bankerAvailTable->item(0,j)->setText(QString::number(banker.available[j]));
        }
        // Update Allocation row for the requesting process
        for(int j=0;j<bankerR;j++){
            bankerAllocTable->item(pid,j)->setText(QString::number(banker.allocation[pid][j]));
        }
        // Update Need matrix display
        for(int i=0;i<bankerP;i++) for(int j=0;j<bankerR;j++){
            auto* it=new QTableWidgetItem(QString::number(banker.need[i][j]));
            it->setTextAlignment(Qt::AlignCenter);
            bankerNeedTable->setItem(i,j,it);
        }
    }
    // ── End fix ────────────────────────────────────────────────────────────

    appendLog(bankerLog,"━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━","#45475a");
    appendLog(bankerLog,QString::fromStdString(res.log), res.isSafe?"#a6e3a1":"#fab387");
}

void MainWindow::onBankerClear()
{
    bankerLog->clear();
    rebuildBankerTables(bankerProcessSpin->value(), bankerResourceSpin->value());
}

// ─────────────────────────────────────────────────────
//  DETECTION SLOTS
// ─────────────────────────────────────────────────────
void MainWindow::onDetectionSetup()
{
    rebuildDetectionTables(detectionProcessSpin->value(), detectionResourceSpin->value());
    ragWidget->clear();
    appendLog(detectionLog,
        QString("Tables ready: %1 processes, %2 resources.\nFill in Available, Allocation, Request then click Run Detection.")
        .arg(detectionP).arg(detectionR), "#89b4fa");
}

void MainWindow::onDetectionLoadExample()
{
    // Classic deadlock example: 4 processes, 2 resources
    detectionProcessSpin->setValue(4); detectionResourceSpin->setValue(2);
    rebuildDetectionTables(4,2);

    // Available: 0 0  (no free resources → deadlock guaranteed)
    detectionAvailTable->item(0,0)->setText("0");
    detectionAvailTable->item(0,1)->setText("0");

    // Allocation
    int allocD[4][2]={{1,0},{0,1},{0,0},{0,0}};
    // Request (each holds one, wants what other holds)
    int reqD[4][2]={{0,1},{1,0},{0,0},{0,0}};

    for(int i=0;i<4;i++) for(int j=0;j<2;j++){
        detectionAllocTable->item(i,j)->setText(QString::number(allocD[i][j]));
        detectionRequestTable->item(i,j)->setText(QString::number(reqD[i][j]));
    }
    appendLog(detectionLog,"Example loaded: P0 holds R0 & wants R1; P1 holds R1 & wants R0.\nExpected: DEADLOCK between P0 and P1.","#94e2d5");
}

void MainWindow::onDetectionRun()
{
    if(detectionP==0||detectionR==0){QMessageBox::warning(this,"Setup","Click Setup Tables first.");return;}

    // ── FIX: Input validation ──────────────────────────────────────────────
    for(int j=0;j<detectionR;j++){
        bool ok;
        int val = detectionAvailTable->item(0,j) ? detectionAvailTable->item(0,j)->text().toInt(&ok) : 0;
        if(!ok || val < 0){
            QMessageBox::warning(this,"Invalid Input",
                QString("Invalid available value for R%1. Must be a non-negative integer.").arg(j));
            return;
        }
    }
    for(int i=0;i<detectionP;i++){
        for(int j=0;j<detectionR;j++){
            bool okAlloc, okReq;
            int allocVal = detectionAllocTable->item(i,j)   ? detectionAllocTable->item(i,j)->text().toInt(&okAlloc)   : 0;
            int reqVal   = detectionRequestTable->item(i,j) ? detectionRequestTable->item(i,j)->text().toInt(&okReq)   : 0;
            if(!okAlloc || !okReq || allocVal < 0 || reqVal < 0){
                QMessageBox::warning(this,"Invalid Input",
                    QString("Invalid value at P%1, R%2. All values must be non-negative integers.").arg(i).arg(j));
                return;
            }
        }
    }
    // ── End validation ─────────────────────────────────────────────────────

    std::vector<int> avail(detectionR);
    for(int j=0;j<detectionR;j++) avail[j]=detectionAvailTable->item(0,j)->text().toInt();

    std::vector<std::vector<int>> alloc(detectionP,std::vector<int>(detectionR));
    std::vector<std::vector<int>> req(detectionP,std::vector<int>(detectionR));
    for(int i=0;i<detectionP;i++) for(int j=0;j<detectionR;j++){
        alloc[i][j]=detectionAllocTable->item(i,j)->text().toInt();
        req[i][j]  =detectionRequestTable->item(i,j)->text().toInt();
    }

    Detection det(detectionP,detectionR);
    det.setAvailable(avail); det.setAllocation(alloc); det.setRequest(req);
    DetectionResult result=det.detect();

    appendLog(detectionLog,"━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━","#45475a");
    appendLog(detectionLog,QString::fromStdString(result.log), result.deadlockFound?"#f38ba8":"#a6e3a1");

    // Update RAG
    QVector<QVector<int>> qAlloc(detectionP, QVector<int>(detectionR));
    QVector<QVector<int>> qReq(detectionP, QVector<int>(detectionR));
    QVector<int> qDead;
    for(int i=0;i<detectionP;i++) for(int j=0;j<detectionR;j++){qAlloc[i][j]=alloc[i][j];qReq[i][j]=req[i][j];}
    for(int p:result.deadlockedProcesses) qDead.append(p);
    ragWidget->setGraph(detectionP,detectionR,qAlloc,qReq,qDead);

    // Store for recovery
    lastDetectionResult=result;
    lastAllocation=alloc;
    lastRequest=req;           // FIX: store request matrix for RAG refresh after recovery
    lastAvailable=avail;
    lastDetP=detectionP;
    lastDetR=detectionR;

    if(result.deadlockFound){
        QString dProcs;
        for(int p:result.deadlockedProcesses) dProcs+="P"+QString::number(p)+" ";
        recoveryStatusLabel->setText("⚠️  Deadlock detected! Processes: "+dProcs+"\nChoose a recovery strategy below.");
        recoveryStatusLabel->setStyleSheet("color:#f38ba8; font-size:13px; padding:6px;");
        tabWidget->setTabText(2,"🔧  Recovery ⚠️");
    } else {
        recoveryStatusLabel->setText("✅ No deadlock found. System is safe.");
        recoveryStatusLabel->setStyleSheet("color:#a6e3a1; font-size:13px; padding:6px;");
        tabWidget->setTabText(2,"🔧  Recovery");
    }
}

void MainWindow::onDetectionClear()
{
    detectionLog->clear();
    ragWidget->clear();
    rebuildDetectionTables(detectionProcessSpin->value(),detectionResourceSpin->value());
}

// ─────────────────────────────────────────────────────
//  RECOVERY SLOTS
// ─────────────────────────────────────────────────────

// ── Helper: refresh RAG after recovery ────────────────
void MainWindow::refreshRAGAfterRecovery()
{
    QVector<QVector<int>> qAlloc(lastDetP, QVector<int>(lastDetR));
    QVector<QVector<int>> qReq(lastDetP, QVector<int>(lastDetR));

    for(int i=0;i<lastDetP;i++) for(int j=0;j<lastDetR;j++){
        qAlloc[i][j] = lastAllocation[i][j];
        // Zero out request rows for any process that was terminated
        // (their allocation is already 0 from Recovery, so this is consistent)
        qReq[i][j] = lastAllocation[i][j] == 0 ? 0 : lastRequest[i][j];
    }

    // No remaining deadlocked processes — pass empty list
    ragWidget->setGraph(lastDetP, lastDetR, qAlloc, qReq, QVector<int>());
}

void MainWindow::onRecoveryTerminateAll()
{
    if(!lastDetectionResult.deadlockFound||lastDetectionResult.deadlockedProcesses.empty()){
        QMessageBox::information(this,"No Deadlock","No deadlock data.\nRun Deadlock Detection first.");
        return;
    }
    Recovery rec;
    RecoveryResult rr=rec.terminateAll(lastDetectionResult,lastAllocation,lastAvailable,lastDetR);
    appendLog(recoveryLog,"━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━","#45475a");
    appendLog(recoveryLog,QString::fromStdString(rr.log),"#a6e3a1");

    lastDetectionResult.deadlockedProcesses.clear();
    lastDetectionResult.deadlockFound=false;

    // ── FIX: Refresh RAG to reflect recovered state ────────────────────────
    refreshRAGAfterRecovery();
    // ── End fix ────────────────────────────────────────────────────────────

    tabWidget->setTabText(2,"🔧  Recovery");
    recoveryStatusLabel->setText("✅ All deadlocked processes terminated. System recovered.");
    recoveryStatusLabel->setStyleSheet("color:#a6e3a1; font-size:13px; padding:6px;");
}

void MainWindow::onRecoveryTerminateOne()
{
    if(!lastDetectionResult.deadlockFound||lastDetectionResult.deadlockedProcesses.empty()){
        QMessageBox::information(this,"No Deadlock","No deadlock data.\nRun Deadlock Detection first.");
        return;
    }
    Recovery rec;
    RecoveryResult rr=rec.terminateOne(lastDetectionResult,lastAllocation,lastAvailable,lastDetR);
    appendLog(recoveryLog,"━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━","#45475a");
    appendLog(recoveryLog,QString::fromStdString(rr.log),"#fab387");

    if(!rr.terminatedProcesses.empty()){
        int victim=rr.terminatedProcesses[0];

        // ── FIX: Zero out the victim's request row so RAG shows correct state
        if(victim < lastDetP){
            for(int j=0;j<lastDetR;j++) lastRequest[victim][j] = 0;
        }
        // ── End fix ────────────────────────────────────────────────────────

        auto& dl=lastDetectionResult.deadlockedProcesses;
        dl.erase(std::remove(dl.begin(),dl.end(),victim),dl.end());

        if(dl.empty()){
            lastDetectionResult.deadlockFound=false;
            tabWidget->setTabText(2,"🔧  Recovery");
            recoveryStatusLabel->setText("✅ Deadlock resolved. Run detection again to verify.");
            recoveryStatusLabel->setStyleSheet("color:#a6e3a1; font-size:13px; padding:6px;");
        } else {
            QString rem;
            for(int p:dl) rem+="P"+QString::number(p)+" ";
            recoveryStatusLabel->setText("⚠️  Still deadlocked: "+rem+"\nTerminate another process or use Terminate ALL.");
        }

        // ── FIX: Refresh RAG after each single termination ─────────────────
        refreshRAGAfterRecovery();
        // ── End fix ────────────────────────────────────────────────────────
    }
}

void MainWindow::onRecoveryClear() { recoveryLog->clear(); }
