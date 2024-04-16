cmake_minimum_required(VERSION 3.5)

if(${BUILD_SYSTEM} STREQUAL "openSUSE_TW")
    add_definitions(-DOPENSUSE)
elseif(${BUILD_SYSTEM} STREQUAL "Ubuntu16")
    add_definitions(-DUBUNTU)
endif()

project(cube_istaller VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIred ON)

if(${BUILD_SYSTEM} STREQUAL "Ubuntu16")
    set(CMAKE_CXX_STANDARD 11)
endif()

find_package(QT NAMES Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        mainwindow.ui
        config.ui

        mainwindow.h
        config.h
        parser.h
        worker.h
        loger.h

        main.cpp
        mainwindow.cpp
        config.cpp
        parser.cpp
        worker.cpp
        loger.cpp

        parser.py

        build_Ubuntu16.sh
        deploy.sh
)

add_executable(cube_istaller ${PROJECT_SOURCES})

target_link_libraries(cube_istaller PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

if(${BUILD_SYSTEM} STREQUAL "openSUSE_TW")
    install(TARGETS cube_istaller
        BUNDLE DESTINATION .
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
elseif(${BUILD_SYSTEM} STREQUAL "Ubuntu16")
    install(TARGETS cube_istaller
        RUNTIME DESTINATION .
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
endif()
