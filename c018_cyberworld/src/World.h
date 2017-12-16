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

	//get points
	const std::set<PointPtr>& getPoints() const;

	// get force
	std::pair<double, double> getForce(const Point&) const;

	// make time fly
	void tictoc();

    friend std::ostream& operator<<( std::ostream& os, const World& world);

private:
    log4cplus::Logger _logger;

    World();
    virtual ~World();

    std::set<PointPtr> _points;
    std::mutex         _points_mutex;
};


#endif //CPP_WORLD_H
