/*
 * CounterJob.h
 *
 *  Created on: Apr 25, 2021
 *      Author: ulasy
 */

#ifndef FIRSTJOB_HPP_
#define FIRSTJOB_HPP_

#include "AnyJob.hpp"

class FirstJob: public AnyJob {
public:
    FirstJob();
    virtual ~FirstJob();
    virtual bool run();
};

#endif /* FIRSTJOB_HPP_ */
