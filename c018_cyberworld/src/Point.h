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
    Point(const std::pair<double, double>&);
    virtual ~Point();

    // get
    inline double x() const { return _x; };
    inline double y() const { return _y; };

    // start move automatically
    void run();
    void stop();

    // move one step
    void move();

    // operator : <
    friend bool operator<( const Point& lhs, const Point& rhs );

    // operator : <<
    friend std::ostream& operator<<( std::ostream&, const Point& );

private:
    log4cplus::Logger _logger;

    // mass( Kg )
    double _mass;

    // position
    double _x;
    double _y;

    // last seq
    unsigned int _lastTime = 0;
};


#endif //CPP_POINT_H
