//
// Created by cho on 17. 11. 26.
//

#ifndef CPP_POINT_H
#define CPP_POINT_H

#include <log4cplus/loggingmacros.h>
#include <chrono>
#include "ActiveObject.h"
#include "Element.h"

class ActivePoint : public ActiveObject {
public:
    ActivePoint();
    ActivePoint(const Element&);
    ActivePoint(const Element& p, const Element& v);
    ActivePoint(const Element& p, const Element& v, double mass);
    virtual ~ActivePoint();

    // implement
	bool doRun() override;

    // get
    inline Element getPoint() const { return _p; };

    // operator : <<
    friend std::ostream& operator<<( std::ostream&, const ActivePoint& );

private:
    // sequence number
    static int _seq;

    // mass( Kg )
    double _mass;

    // position
    Element _p;

    // velocity
    Element _v{0.0,0.0};

    // last time
    std::chrono::time_point<std::chrono::steady_clock> _lastTime;
};


#endif //CPP_POINT_H
