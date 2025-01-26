cmake_minimum_required(VERSION 3.10)
project(MyApp)

set(CMAKE_CXX_STANDARD 17)

set(SFML_DIR "D:/C++/SFML-2.5.1/lib/cmake/SFML")
find_package(SFML 2.5 REQUIRED graphics window system)

include_directories(${CMAKE_SOURCE_DIR})

add_executable(MyApp 
    main.cpp 
    src/Database.cpp 
    src/UIManager.cpp 
    src/App.cpp 
    sqlite3.c)


target_link_libraries(MyApp sfml-graphics sfml-window sfml-system)

target_include_directories(MyApp PRIVATE include)

set_property(TARGET MyApp PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")