//
// Created by cho on 17. 11. 26.
//

#ifndef CPP_POINT_H
#define CPP_POINT_H

#include <log4cplus/loggingmacros.h>

class Point {
public:
    Point();
    Point(double, double);
    virtual ~Point();

    friend bool operator<( const Point& lhs, const Point& rhs );
    friend std::ostream& operator<<( std::ostream&, const Point& );

private:
    log4cplus::Logger logger;
    double x;
    double y;
};


#endif //CPP_POINT_H
