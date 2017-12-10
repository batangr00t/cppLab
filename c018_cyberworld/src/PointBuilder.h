//
// Created by cho on 17. 11. 26.
//

#ifndef CPP_POINTBUILDER_H
#define CPP_POINTBUILDER_H

#include <memory>
#include <random>
#include "Point.h"
#include "PointBuilderInterface.h"

class PointBuilder : public PointBuilderInterface {
public:
	PointBuilder();
	PointBuilder(double start, double end);
	virtual ~PointBuilder();

	PointPtr getNext();

	std::pair<double, double> getRandomCordiante() {
		return std::make_pair( _distribution(_gen), _distribution(_gen) );
	}

private:
    log4cplus::Logger _logger;

    // point x, y interval
	double _start;
	double _end;

    // random number generator
    std::mt19937 _gen;
    std::uniform_real_distribution<double> _distribution;
};


#endif //CPP_POINTBUILDER_H
