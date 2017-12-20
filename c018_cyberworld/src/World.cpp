//
// Created by cho on 17. 11. 26.
//

#include "World.h"
#include "BuilderRandom.h"
#include "Define.h"

using namespace std;

World &World::getInstance() {
    static World world{};
    return world;
}

World::World() :
	_logger{ log4cplus::Logger::getInstance(LOG4CPLUS_TEXT("World")) } {
	LOG4CPLUS_INFO( _logger, __PRETTY_FUNCTION__ );

};

World::~World() {
	LOG4CPLUS_INFO( _logger, __PRETTY_FUNCTION__ );

	for ( const auto& p : _points ) {
		if ( p ) p->stop();
	}
};

void World::generatePoints(BuilderInterface& builder, size_t n ) {
	for ( size_t i = 0; i<n; ++i ) {
		auto pPoint = builder.getNext();
		pPoint->start();
		_points.insert( pPoint );
	}
}

const std::set<ActivePointPtr>& World::getActivePoints() const {
	return _points;
}

// get force
std::pair<double, double> World::getForce(const ActivePoint& ap) const {
	double fx = - ap.getPoint().x;
	double fy = - ap.getPoint().y;

	return make_pair( fx, fy );
}

ostream& operator<<( std::ostream& os, const World& world) {
	static unsigned int seq;
	os << "[" << ++seq << "]\t";
	for ( const auto& e : world._points ) {
		if ( e ) os << *e;
		else os << "(,)";
	}
	return os;
}
