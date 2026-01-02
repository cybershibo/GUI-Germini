cmake_minimum_required(VERSION 3.19)
project(GUI-Germini LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets SerialPort Charts)

qt_standard_project_setup()

qt_add_executable(GUI-Germini
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
)

target_link_libraries(GUI-Germini
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt::SerialPort
        Qt::Charts
)

include(GNUInstallDirs)

install(TARGETS GUI-Germini
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET GUI-Germini
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
