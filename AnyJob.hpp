/*
 * AnyJob.hpp
 *
 *  Created on: Apr 25, 2021
 *      Author: ulasy
 */

#ifndef ANYJOB_HPP_
#define ANYJOB_HPP_

class AnyJob
{
public:

    /**
     * @brief Destructor
     */
    virtual ~AnyJob(void) {}

    /**
     * @brief To be implemented by derived classes in order to be executed.
     */
    virtual bool run() = 0;
};



#endif /* ANYJOB_HPP_ */
