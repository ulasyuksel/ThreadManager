/*
 * SecondJob.hpp
 *
 *  Created on: Apr 25, 2021
 *      Author: ulasy
 */

#ifndef SECONDJOB_HPP_
#define SECONDJOB_HPP_

#include "AnyJob.hpp"

class SecondJob: public AnyJob {
public:
    SecondJob();
    virtual ~SecondJob();
    virtual bool run();
};

#endif /* SECONDJOB_HPP_ */
