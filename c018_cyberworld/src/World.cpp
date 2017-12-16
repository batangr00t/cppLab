//
// Created by cho on 17. 11. 26.
//

#include "World.h"
#include "PointBuilderRandom.h"
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

void World::generatePoints(PointBuilderInterface& builder, size_t n ) {
	for ( size_t i = 0; i<n; ++i ) {
		auto pPoint = builder.getNext();
		pPoint->start();
		_points.insert( pPoint );
	}
}

const std::set<PointPtr>& World::getPoints() const {
	return _points;
}

// get force
pair<double, double> World::getForce(const Point& point) const {
//	int x_direction = point.x() > 0 ? 1 : -1;
//	int y_direction = point.y() > 0 ? 1 : -1;
//	double fx = - x_direction * 50 / (point.x() * point.x());
//	double fy = - y_direction * 50 / (point.y() * point.y());

//	double fx = - point.x() / 3.0 ;
//	double fy = - point.y() / 3.0 ;

	double norm = sqrt( pow( point.x(), 2) + pow( point.y(), 2) );
	double fx = - point.y() / norm;
	double fy = point.x() / norm;
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
