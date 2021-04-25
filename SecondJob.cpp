/*
 * SecondJob.cpp
 *
 *  Created on: Apr 25, 2021
 *      Author: ulasy
 */

#include "SecondJob.hpp"
#include <iostream>
#include <sstream>
#include <string>
#include <thread>

SecondJob::SecondJob() {

}

SecondJob::~SecondJob() {

}

bool
SecondJob::run()
{
    std::cout << "Secong Job RUNNING" << std::endl;
    std::this_thread::sleep_for (std::chrono::seconds(2));
    return true;
}
