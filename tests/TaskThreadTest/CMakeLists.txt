set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
#set(CMAKE_CXX_STANDARD 14)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
enable_testing()

include_directories(../../)
ADD_EXECUTABLE( TaskThreadTest TaskThreadTest.cpp ../../TaskThread.cpp ../../FirstJob.cpp)
ADD_TEST(TaskThread TaskThreadTest)
target_link_libraries(TaskThreadTest Threads::Threads
GTest::gtest_main
GTest::gmock_main
)

include(GoogleTest)
gtest_discover_tests(TaskThreadTest)