include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(runDecisionTreeTests
        GameMapTest.cpp
        ActionTest.cpp StateTest.cpp)

target_link_libraries(runDecisionTreeTests gtest gtest_main)
target_link_libraries(runDecisionTreeTests decisiontree)