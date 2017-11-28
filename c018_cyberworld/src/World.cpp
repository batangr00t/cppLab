//
// Created by cho on 17. 11. 26.
//

#include "World.h"
#include <boost/log/trivial.hpp>

using namespace std;

World &World::getInstance() {
    static World world{};
    return world;
}

World::World() :
	logger( log4cplus::Logger::getInstance( LOG4CPLUS_TEXT("World"))) {
	LOG4CPLUS_TRACE( logger, __PRETTY_FUNCTION__ );
};

World::~World() {
	LOG4CPLUS_TRACE( logger, __PRETTY_FUNCTION__ );
};

uint32_t World::get_point_count() const {
    return _points.size();
}

void World::add_point(unsigned int n) {
    lock_guard<mutex> lg( _m);

    for ( unsigned int i = 0; i<n; ++i ) {
    	_points.emplace(i,i);
    }
}

ostream& operator<<( std::ostream& os, const World& world) {
	os << "World{" << world.get_point_count() << ":";
	for ( const auto& e : world._points ) {
		os << e;
	}
	os << "}";
	return os;
}
