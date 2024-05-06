cmake_minimum_required(VERSION 3.5)

project(cube_installer VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIred ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)



set(CMAKE_PREFIX_PATH "/usr/local/opt/qt6")

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Widgets)
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

        #build_Ubuntu16.sh
        #deploy.sh
)

add_executable(cube_installer ${PROJECT_SOURCES})

target_link_libraries(cube_installer PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

add_custom_command(TARGET cube_installer POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/mac_script.sh ${CMAKE_CURRENT_BINARY_DIR}/mac_script.sh)
add_custom_command(TARGET cube_installer POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/parser.py ${CMAKE_CURRENT_BINARY_DIR}/parser.py)
add_custom_command(TARGET cube_installer POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/venv_python ${CMAKE_CURRENT_BINARY_DIR}/venv_python)

install(TARGETS cube_installer
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib)

#if(${BUILD_SYSTEM} STREQUAL "openSUSE_TW")
#    install(TARGETS cube_istaller
#        BUNDLE DESTINATION .
#        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
#elseif(${BUILD_SYSTEM} STREQUAL "Ubuntu16")
#    install(TARGETS cube_istaller
#        RUNTIME DESTINATION .
#        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
#endif()
