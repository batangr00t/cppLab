//
// Created by cho on 17. 11. 26.
//

#include "Point.h"
#include <boost/log/trivial.hpp>


Point::Point() {
    BOOST_LOG_TRIVIAL( info ) << __PRETTY_FUNCTION__;
}

Point::~Point() {
    BOOST_LOG_TRIVIAL( info ) << __PRETTY_FUNCTION__;
}
