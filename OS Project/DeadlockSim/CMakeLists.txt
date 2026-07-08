cmake_minimum_required(VERSION 3.16)
project(DeadlockSim LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 REQUIRED COMPONENTS Core Gui Widgets)

include_directories(include)

add_executable(DeadlockSim
    src/main.cpp
    src/MainWindow.cpp
    src/Banker.cpp
    src/Detection.cpp
    src/Recovery.cpp
    src/RAGWidget.cpp
)

target_link_libraries(DeadlockSim
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
)
