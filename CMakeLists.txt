cmake_minimum_required(VERSION 3.10)
project(Lab7_NPC_Battle)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Threads REQUIRED)

set(SOURCES
    main.cpp
    src/NPC.cpp
    src/Game.cpp
    src/ThreadManager.cpp
    src/utils.cpp
)

set(HEADERS
    include/NPC.h
    include/Game.h
    include/ThreadManager.h
    include/utils.h
)

add_executable(npc_battle ${SOURCES} ${HEADERS})
target_include_directories(npc_battle PRIVATE include)
target_link_libraries(npc_battle PRIVATE Threads::Threads)

find_package(GTest)
if(GTest_FOUND)
    enable_testing()
    add_executable(npc_tests test/test01.cpp src/NPC.cpp src/utils.cpp)
    target_include_directories(npc_tests PRIVATE include)
    target_link_libraries(npc_tests PRIVATE GTest::gtest GTest::gtest_main)
    add_test(NAME NPC_Tests COMMAND npc_tests)
endif()
