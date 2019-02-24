cmake_minimum_required (VERSION 2.6)
project (test_datetime)

# Simple
add_executable(test_datetime test_datetime.cpp datetime.cpp)
add_executable(datetime main.cpp datetime.cpp)
add_executable(calendar calendar.cpp datetime.cpp)

# Alt sources
#file(GLOB SOURCES "*date*.cpp")
#set(SOURCES datetime.cpp test_datetime.cpp)
#add_executable(test_datetime ${SOURCES})
set(LIBS gtest gtest_main pthread)
target_link_libraries(test_datetime ${LIBS})


