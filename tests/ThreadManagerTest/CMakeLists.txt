set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

enable_testing()

include_directories(../../)
ADD_EXECUTABLE(ThreadManagerTest ThreadManagerTest.cpp ../../ThreadManager.cpp ../../TaskThread.cpp ../../FirstJob.cpp ../../SecondJob.cpp)
ADD_TEST(ThreadManagerTest ThreadManagerTest)
target_link_libraries(ThreadManagerTest Threads::Threads
GTest::gtest_main
GTest::gmock_main
)

include(GoogleTest)
gtest_discover_tests(ThreadManagerTest)