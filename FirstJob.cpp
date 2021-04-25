/*
 * CounterJob.cpp
 *
 *  Created on: Apr 25, 2021
 *      Author: ulasy
 */

#include "FirstJob.hpp"

#include <iostream>
#include <sstream>
#include <string>
#include <thread>


FirstJob::FirstJob() {


}

FirstJob::~FirstJob() {

}


bool
FirstJob::run()
{
    std::cout << "First Job RUNNING" << std::endl;
    std::this_thread::sleep_for (std::chrono::seconds(1));
    return true;
}
