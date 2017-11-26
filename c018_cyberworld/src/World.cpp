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

World::World() : _point_count(0) {
    BOOST_LOG_TRIVIAL( info ) << __PRETTY_FUNCTION__ ;
};

World::~World() {
    BOOST_LOG_TRIVIAL( info ) << __PRETTY_FUNCTION__ ;
};

uint32_t World::get_point_count() const {
    return _point_count;
}

void World::inc_point_count() {
    lock_guard<mutex> lg( _m);

    _point_count++;
}


