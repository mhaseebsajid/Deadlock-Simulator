QT       += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET   = DeadlockSim
TEMPLATE = app
CONFIG  += c++17

INCLUDEPATH += include

SOURCES += \
    src/main.cpp        \
    src/MainWindow.cpp  \
    src/Banker.cpp      \
    src/Detection.cpp   \
    src/Recovery.cpp    \
    src/RAGWidget.cpp

HEADERS += \
    include/MainWindow.h  \
    include/Banker.h      \
    include/Detection.h   \
    include/Recovery.h    \
    include/RAGWidget.h

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
