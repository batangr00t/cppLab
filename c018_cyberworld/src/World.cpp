//
// Created by cho on 17. 11. 26.
//

#include "World.h"

#include "PointBuilderRandom.h"

using namespace std;

World &World::getInstance() {
    static World world{};
    return world;
}

World::World() :
	_logger( log4cplus::Logger::getInstance( LOG4CPLUS_TEXT("World"))) {
	LOG4CPLUS_TRACE( _logger, __PRETTY_FUNCTION__ );

	PointBuilderRandom builder;
};

World::~World() {
	LOG4CPLUS_TRACE( _logger, __PRETTY_FUNCTION__ );
};

size_t World::getSize() const {
    return _points.size();
}

void World::generatePoints(PointBuilderInterface& builder, size_t n ) {
	for ( size_t i = 0; i<n; ++i ) {
		_points.insert( builder.getNext() );
	}
}
// get current seq
unsigned int World::currentTime() const {
	return _currentTime;
}

// get force
pair<double, double> World::F(const Point& point) const {
	double fx = - point.x();
	double fy = - point.y();

	return make_pair( fx, fy );
}

// pulse
void  World::move() {
	++_currentTime;

	for ( const auto& p : _points ) {
		if ( p ) p->move();
	}
}

ostream& operator<<( std::ostream& os, const World& world) {
	os << "World has " << world.getSize() << " points\n";
	os << "[" << world._currentTime << "]\t";
	for ( const auto& e : world._points ) {
		if ( e ) os << *e;
		else os << "(,)";
	}
	return os;
}
