//
// Created by cho on 17. 11. 26.
//

#ifndef CPP_WORLD_H
#define CPP_WORLD_H

#include <cstdint>
#include <mutex>
#include <thread>
#include <set>
#include <log4cplus/loggingmacros.h>
#include <ostream>
#include "Point.h"

class World {
public:
    static World& getInstance();
    uint32_t get_point_count() const;
    void add_point(unsigned int n);

    friend std::ostream& operator<<( std::ostream& os, const World& world);

private:
    log4cplus::Logger logger;

    World();
    virtual ~World();

    std::set<Point> _points;
    std::mutex _m;
};


#endif //CPP_WORLD_H
