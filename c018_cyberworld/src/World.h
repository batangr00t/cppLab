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
#include "PointBuilderRandom.h"

class World {
public:
    static World& getInstance();
    size_t getSize() const;
    void generatePoints(PointBuilderInterface& builder, size_t n );

    // get current seq
    unsigned int currentTime() const;

	// get force
	std::pair<double, double> F(const Point&) const;

	// pulse
	void move();

    friend std::ostream& operator<<( std::ostream& os, const World& world);

private:
    log4cplus::Logger _logger;

    World();
    virtual ~World();

    std::set<PointPtr> _points;
    std::mutex         _points_mutex;

    std::atomic<unsigned int> _currentTime;
};


#endif //CPP_WORLD_H
