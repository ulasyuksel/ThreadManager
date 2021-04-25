set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

ADD_EXECUTABLE( TaskThread_test TaskThread_test.cpp ../TaskThread.cpp ../FirstJob.cpp)
ADD_TEST(            TaskThread TaskThread_test    )
target_link_libraries(TaskThread_test Threads::Threads)
