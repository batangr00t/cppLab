//
// Created by cho on 17. 11. 26.
//

#ifndef CPP_POINT_H
#define CPP_POINT_H

#include <log4cplus/loggingmacros.h>
#include <chrono>
#include "ActiveObject.h"

class Point : public ActiveObject {
public:
    Point();
    Point(double, double);
    Point(const std::pair<double, double>&);
    virtual ~Point();

    // implement
	bool doRun() override;

    // get
    inline double x() const { return _x; };
    inline double y() const { return _y; };

    // operator : <
    friend bool operator<( const Point& lhs, const Point& rhs );

    // operator : <<
    friend std::ostream& operator<<( std::ostream&, const Point& );

private:
    // sequence number
    static int _seq;

    // mass( Kg )
    double _mass;

    // position
    double _x;
    double _y;

    // velocity
    double _vx{0};
    double _vy{0};

    // last time
    std::chrono::time_point<std::chrono::steady_clock> _lastTime;
};


#endif //CPP_POINT_H
