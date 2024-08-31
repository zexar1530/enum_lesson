cmake_minimum_required(VERSION 3.5)

project(SignalSlot VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        widget.cpp
        widget.h
        widget.ui
        Stopwatch.h
)



#target_link_libraries(SignalSlot PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)


if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(SignalSlot)
endif()

add_subdirectory("1")
