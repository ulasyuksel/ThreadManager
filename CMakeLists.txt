cmake_minimum_required (VERSION 3.14)

project (ThreadManager)
set(CMAKE_CXX_STANDARD 14)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
add_executable(ThreadManager main.cpp FirstJob.cpp SecondJob.cpp ThreadManager.cpp TaskThread.cpp)
target_link_libraries(ThreadManager Threads::Threads)

ADD_SUBDIRECTORY( tests )