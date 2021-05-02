/*
 * unit_tests.h
 *
 *  Created on: May 2, 2021
 *      Author: ulasy
 */

#ifndef TESTS_UNIT_TESTS_H_
#define TESTS_UNIT_TESTS_H_



// ALEPH_ASSERT_EQUAL From: https://bastian.rieck.me/blog/posts/2017/simple_unit_tests/
// Can be moved to a header.
// Please check "/Testing/Temporary" folder for failing item output

#define ALEPH_ASSERT_EQUAL( x, y )                                  \
{                                                                   \
  if( ( x ) != ( y ) )                                              \
  {                                                                 \
    throw std::runtime_error(   std::string( __FILE__ )             \
                              + std::string( ":" )                  \
                              + std::to_string( __LINE__ )          \
                              + std::string( " in " )               \
                              + std::string( __PRETTY_FUNCTION__ )  \
                              + std::string( ": " )                 \
                              + std::to_string( ( x ) )             \
                              + std::string( " != " )               \
                              + std::to_string( ( y ) )             \
    );                                                              \
  }                                                                 \
}


#endif /* TESTS_UNIT_TESTS_H_ */
