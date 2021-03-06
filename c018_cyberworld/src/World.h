//
// Created by cho on 17. 11. 26.
//

#ifndef CPP_WORLD_H
#define CPP_WORLD_H

#include <log4cplus/logger.h>
#include <stddef.h>
#include <mutex>
#include <ostream>
#include <set>
#include <utility>
#include <valarray>

#include "ActivePoint.h"
#include "BuilderInterface.h"

class World {
public:
    static World& getInstance();
    size_t getSize() const;
    void generatePoints(BuilderInterface& builder, size_t n );

	//get points
	const std::set<ActivePointPtr>& getActivePoints() const;

	// get force
	std::pair<double, double> getForce(const ActivePoint&) const;

	// make time fly
	void tictoc();

    friend std::ostream& operator<<( std::ostream& os, const World& world);

private:
    log4cplus::Logger _logger;

    World();
    virtual ~World();

    std::set<ActivePointPtr> _points;
    std::mutex         _points_mutex;
};


#endif //CPP_WORLD_H
