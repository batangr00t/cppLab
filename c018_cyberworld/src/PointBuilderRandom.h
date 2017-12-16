//
// Created by cho on 17. 11. 26.
//

#ifndef CPP_POINTBUILDER_H
#define CPP_POINTBUILDER_H

#include <memory>
#include <random>
#include "Point.h"
#include "PointBuilderInterface.h"

class PointBuilderRandom : public PointBuilderInterface {
public:
	PointBuilderRandom();
	PointBuilderRandom(double max_x, double max_y);
	virtual ~PointBuilderRandom();

	PointPtr getNext();

	std::pair<double, double> getRandomCordiante() {
		return std::make_pair( _distribution_x(_gen), _distribution_y(_gen) );
	}

private:
    log4cplus::Logger _logger;

    // point x, y interval
	double _max_x;
	double _max_y;

    // random number generator
    std::mt19937 _gen;
    std::uniform_real_distribution<double> _distribution_x;
    std::uniform_real_distribution<double> _distribution_y;
};


#endif //CPP_POINTBUILDER_H
